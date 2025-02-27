#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>

#define UPLOAD_DIR "./uploads"
#define MAX_FILENAME_LEN 256
#define MAX_CONTENT_LEN 1024

// Mutex for thread-safe file operations
pthread_mutex_t file_mutex = PTHREAD_MUTEX_INITIALIZER;

// Utility function to ensure the upload directory exists
void ensure_upload_dir() {
    struct stat st;
    if (stat(UPLOAD_DIR, &st) == -1) {
        mkdir(UPLOAD_DIR, 0700);
    }
}

// Function to list all files in the upload directory
void list_files() {
    pthread_mutex_lock(&file_mutex);  // Lock mutex

    DIR *dir = opendir(UPLOAD_DIR);
    if (!dir) {
        perror("Failed to open upload directory");
        pthread_mutex_unlock(&file_mutex);  // Unlock mutex
        return;
    }

    printf("\nFiles in '%s':\n", UPLOAD_DIR);
    struct dirent *entry;
    int file_count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // Only regular files
            printf(" - %s\n", entry->d_name);
            file_count++;
        }
    }

    if (file_count == 0) {
        printf("No files found.\n");
    }

    closedir(dir);

    pthread_mutex_unlock(&file_mutex);  // Unlock mutex
}

// Function to upload a file with content
void upload_file(const char *filename, const char *content) {
    pthread_mutex_lock(&file_mutex);  // Lock mutex

    char filepath[MAX_FILENAME_LEN];
    snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);

    FILE *file = fopen(filepath, "w");
    if (!file) {
        perror("Failed to create file");
    } else {
        fprintf(file, "%s", content);
        fclose(file);
        printf("File '%s' uploaded successfully.\n", filename);
    }

    pthread_mutex_unlock(&file_mutex);  // Unlock mutex
}

// Function to rename a file
void rename_file(const char *old_name, const char *new_name) {
    pthread_mutex_lock(&file_mutex);  // Lock mutex

    char old_filepath[MAX_FILENAME_LEN], new_filepath[MAX_FILENAME_LEN];
    snprintf(old_filepath, sizeof(old_filepath), "%s/%s", UPLOAD_DIR, old_name);
    snprintf(new_filepath, sizeof(new_filepath), "%s/%s", UPLOAD_DIR, new_name);

    if (rename(old_filepath, new_filepath) == 0) {
        printf("File '%s' renamed to '%s'.\n", old_name, new_name);
    } else {
        perror("Failed to rename file");
    }

    pthread_mutex_unlock(&file_mutex);  // Unlock mutex
}

// Function to delete a file
void delete_file(const char *filename) {
    pthread_mutex_lock(&file_mutex);  // Lock mutex

    char filepath[MAX_FILENAME_LEN];
    snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);

    if (remove(filepath) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        perror("Failed to delete file");
    }

    pthread_mutex_unlock(&file_mutex);  // Unlock mutex
}

// Main function with menu-driven interface
int main() {
    ensure_upload_dir();

    int choice;
    char filename[MAX_FILENAME_LEN];
    char new_filename[MAX_FILENAME_LEN];
    char content[MAX_CONTENT_LEN];

    while (1) {
        printf("\n=== File Operations Menu ===\n");
        printf("1. List Files\n");
        printf("2. Upload File\n");
        printf("3. Rename File\n");
        printf("4. Delete File\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                list_files();
                break;

            case 2:
                printf("Enter the filename to upload: ");
                scanf("%s", filename);
                printf("Enter content for the file: ");
                getchar(); // Consume the newline character left by scanf
                fgets(content, sizeof(content), stdin);
                content[strcspn(content, "\n")] = 0; // Remove trailing newline
                upload_file(filename, content);
                break;

            case 3:
                printf("Enter the current filename: ");
                scanf("%s", filename);
                printf("Enter the new filename: ");
                scanf("%s", new_filename);
                rename_file(filename, new_filename);
                break;

            case 4:
                printf("Enter the filename to delete: ");
                scanf("%s", filename);
                delete_file(filename);
                break;

            case 5:
                printf("Exiting the program. Goodbye!\n");
                pthread_mutex_destroy(&file_mutex);
                exit(0);

            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    }

    return 0;
}
