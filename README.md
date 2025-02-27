Project Name: ReCloudify

ReCloudify enables users to repurpose old laptops as remote storage devices, creating a personal cloud. Using a client-server model with socket programming, data can be seamlessly stored and accessed over a network. This decentralized approach offers cost-effective, private, and expandable storage without relying on third-party cloud providers.

Remote File Access Management System :

This C program implements a simple file management system that allows users to upload, list, rename, and delete files in a designated directory (`./uploads`). The system ensures thread-safe operations using mutex locks, making it suitable for concurrent use.  

Features :
- List Files: View all files stored in the `uploads` directory.  
- Upload Files: Create new files and store content provided by the user.  
- Rename Files: Change the name of an existing file.  
- Delete Files: Remove unwanted files from the directory.  
- Thread-Safe Operations: Uses mutex locks to prevent data corruption when multiple users access files simultaneously.  

How It Works
1. The program ensures that the `uploads` directory exists before performing any operations.  
2. Users interact with the **menu-driven interface** to manage files.  
3. All file operations are wrapped in **pthread mutex locks** to ensure safe access in multi-threaded environments.  
4. The program continues running until the user chooses to exit.  

Usage : 

Compilation and Execution 
To compile and run the program, use:  
```bash
gcc file_manager.c -o file_manager -lpthread
./file_manager
```  

Menu Options 
1️⃣ List Files – Displays all files in the `uploads` directory.  
2️⃣ Upload File – Creates a new file and saves user input as content.  
3️⃣ Rename File – Renames an existing file to a new name.  
4️⃣ Delete File – Deletes a file from the directory.  
5️⃣ Exit – Closes the program safely.  

Example Usage 
```
=== File Operations Menu ===  
1. List Files  
2. Upload File  
3. Rename File  
4. Delete File  
5. Exit  
Choose an option: 2  

Enter the filename to upload: notes.txt  
Enter content for the file: This is a sample note.  
File 'notes.txt' uploaded successfully.  
```  

Why Use This Program? 
✔ Efficient File Handling – Quickly manages files without using a GUI.  
✔ Thread-Safe – Ensures safe access to files using mutex locks.  
✔ Lightweight & Fast – Runs efficiently on low-resource systems.  
✔ No Dependencies – Requires only standard C libraries and POSIX threading.  

Future Enhancements
- Add network-based file upload using sockets.  
- Implement encryption for secure file storage.  
- Provide user authentication to restrict access.  

---

I. Valgrind Helgrind: Detecting Threading Issues

What is Valgrind?
Valgrind is a powerful debugging and profiling tool that helps detect memory leaks, threading issues, and performance bottlenecks in C and C++ programs. One of its tools, Helgrind, is specifically designed for detecting threading errors in multi-threaded programs.

How Helgrind Helps
Helgrind is used to find common threading issues such as:  

1. Data Races: Occur when two or more threads access the same memory location without proper synchronization, leading to unpredictable behavior.  
2. Locking Issues: Detects incorrect use of mutexes (locks), such as deadlocks and double-locking.  
3. Thread Synchronization Problems: Helps identify missing or incorrect use of thread synchronization primitives like `pthread_mutex_lock()` and `pthread_mutex_unlock()`.  
4. Potential Undefined Behavior: Warns about situations where one thread might modify data while another is reading it.  

Example of Using Helgrind 
If you compile and run a multi-threaded C program with:  
```bash
gcc -o myprog myprog.c -lpthread
valgrind --tool=helgrind ./myprog
```  
Helgrind will analyze the program’s execution and report any potential race conditions or threading issues.  

Why Use Helgrind?
- Ensures thread safety in concurrent applications.  
- Helps detect hard-to-find race conditions that can cause intermittent failures.  
- Improves the reliability of multi-threaded software.  

---

II. Telent :

What is Telnet? 
Telnet is a network protocol used to establish remote connections to servers over a command-line interface. It allows users to control and interact with remote machines as if they were using them locally.

How Telnet Helps
1. Remote Administration: Telnet can be used to log into remote servers and execute commands.  
2. Testing Network Services: It helps check if specific network ports are open and responding.  
3. Debugging Client-Server Applications: Developers use Telnet to manually send commands to a server and analyze responses.  
4. Legacy System Access: Older systems without modern remote access protocols still use Telnet.  

Example of Using Telnet
To connect to a remote server (e.g., `example.com`) on port 23:  
```bash
telnet <ip addr> 8080
```  
The above command allows you to connect with the nearby device, provided both are connected to the same network. To check if a web server is running on port 80:  
```bash
telnet localhost 8080
```  
The above command allows to open multiple terminals, one being the server and the rest acting as clients. If the connection succeeds, it means the server is listening on that port.  

Telnet : 
You can use Telnet to manually test your server, check connectivity, and debug responses. It provides a simple way to interact with your application without needing a dedicated client interface.
