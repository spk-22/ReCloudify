from flask import Flask, request, jsonify, render_template, send_from_directory
import os
from datetime import datetime

app = Flask(__name__)

UPLOAD_FOLDER = './uploads'
os.makedirs(UPLOAD_FOLDER, exist_ok=True)
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

# Route to list files with sorting
@app.route('/')
def list_files():
    files = os.listdir(app.config['UPLOAD_FOLDER'])
    # Add sorting: Sort files alphabetically
    files.sort()
    file_info = [
        {
            'name': f,
            'size': os.path.getsize(os.path.join(app.config['UPLOAD_FOLDER'], f)),
            'modified': datetime.fromtimestamp(
                os.path.getmtime(os.path.join(app.config['UPLOAD_FOLDER'], f))
            ).strftime('%Y-%m-%d %H:%M:%S')
        }
        for f in files
    ]
    return render_template('files.html', files=file_info)

# Route to upload files
@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return jsonify({'error': 'No file part'}), 400

    file = request.files['file']
    if file.filename == '':
        return jsonify({'error': 'No selected file'}), 400

    filepath = os.path.join(app.config['UPLOAD_FOLDER'], file.filename)
    file.save(filepath)
    return jsonify({'message': f"File '{file.filename}' uploaded successfully!"}), 200

# Route to delete files
@app.route('/delete/<filename>', methods=['POST'])
def delete_file(filename):
    filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
    if os.path.exists(filepath):
        os.remove(filepath)
        return jsonify({'message': f"File '{filename}' deleted successfully!"}), 200
    else:
        return jsonify({'error': f"File '{filename}' not found!"}), 404

# Route to download a file
@app.route('/download/<filename>')
def download_file(filename):
    return send_from_directory(app.config['UPLOAD_FOLDER'], filename)

# Route to rename a file
@app.route('/rename', methods=['POST'])
def rename_file():
    data = request.json
    old_name = data.get('old_name')
    new_name = data.get('new_name')

    old_filepath = os.path.join(app.config['UPLOAD_FOLDER'], old_name)
    new_filepath = os.path.join(app.config['UPLOAD_FOLDER'], new_name)

    if os.path.exists(old_filepath):
        os.rename(old_filepath, new_filepath)
        return jsonify({'message': f"File renamed from '{old_name}' to '{new_name}'!"}), 200
    else:
        return jsonify({'error': f"File '{old_name}' not found!"}), 404

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)