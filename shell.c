#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <sys/stat.h>
#include <fcntl.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

// Function to check if a path is a directory
int isDirectory(char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0) {
        return 0; // Error or path does not exist
    }
    return S_ISDIR(statbuf.st_mode);
}

// Function to check if a path is a file
int isFile(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0) {
        return 0; // Error or path does not exist
    }
    return S_ISREG(statbuf.st_mode);
}

// Function to handle the cp command
void cp_command(char *source_path, char *target_path) {
    char buffer[1024];

    if (isDirectory(target_path)) {
        char *fileName = basename(source_path);
        strcat(target_path, "/");
        strcat(target_path, fileName);

        FILE *sourceFile = fopen(source_path, "rb");
        if (sourceFile == NULL) {
            perror("Error opening source file");
            return;
        }

        FILE *targetFile = fopen(target_path, "wb");
        if (targetFile == NULL) {
            perror("Error creating target file");
            fclose(sourceFile);
            return;
        }

        size_t readbytes = 0;
        while ((readbytes = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
            if (fwrite(buffer, 1, readbytes, targetFile) != readbytes) {
                perror("Error writing to target file");
                fclose(sourceFile);
                fclose(targetFile);
                return;
            }
        }

        fclose(sourceFile);
        fclose(targetFile);
    } else {
        fprintf(stderr, "Target path is not a directory\n");
    }
}

// Function to print supported commands
void supported_commands() {
    printf("Supported commands are:\n");
    printf("pwd  : Print current working directory\n");
    printf("echo : Print a certain sentence\n");
    printf("cp   : Copy files\n");
    printf("mv   : Move or rename a file\n");
    printf("help : Print this help message\n");
    printf("exit : Exit the shell program\n");
}

int main(int argc, char *argv[]) {
    while (1) {
        ssize_t readSize = 0;
        char command[100];
        char *shellMsg = "Ana Gahez ya Basha";
        int wordcount = 1;

        // Prompt for user input
        write(STDOUT, shellMsg, strlen(shellMsg));
        readSize = read(STDIN, command, 100);
        
        // Replace spaces with newlines for splitting
        for (int i = 0; i < readSize; i++) {
            if (command[i] == ' ') {
                command[i] = '\n';
                wordcount++;
            }
        }

        // Null-terminate the command string
        command[readSize - 1] = '\0';

        // Allocate memory for the array of operands
        char *operands[wordcount];
        int operandCounter = 0;
        int previousPos = 0;

        // Split the command into operands
        for (int i = 0; i <= readSize; i++) {
            if (command[i] == '\n' || command[i] == '\0') {
                int length = i - previousPos;
                operands[operandCounter] = (char *)malloc((length + 1) * sizeof(char));
                memcpy(operands[operandCounter], command + previousPos, length);
                operands[operandCounter][length] = '\0'; // Null-terminate the operand
                operandCounter++;
                previousPos = i + 1;
            }
        }

        // Determine operation
        if (strcmp(operands[0], "pwd") == 0) {
            char PathName[100];
            if (getcwd(PathName, sizeof(PathName)) != NULL) {
                printf("Current Path is: %s\n", PathName);
            } else {
                perror("getcwd error:");
            }
        } else if (strcmp(operands[0], "echo") == 0) {
            if (wordcount == 1) {
                perror("Not enough arguments");
            } else {
                for (int i = 1; i < wordcount; i++) {
                    printf("%s ", operands[i]);
                }
                printf("\n");
            }
        } else if (strcmp(operands[0], "cp") == 0) {
            // Ensure that source and target paths are provided
            if (operandCounter < 3) {
                fprintf(stderr, "Usage: cp <source> <target>\n");
            } else {
                cp_command(operands[1], operands[2]);
            }
        } else if (strcmp(operands[0], "mv") == 0) {
            // Ensure that source and target paths are provided
            if (operandCounter < 3) {
                fprintf(stderr, "Usage: mv <source> <target>\n");
            } else {
                // Copy the file
                cp_command(operands[1], operands[2]);
                
                // Remove the source file
                if (remove(operands[1]) != 0) {
                    perror("Error removing source file");
                }
            }
        } else if (strcmp(operands[0], "help") == 0) {
            supported_commands();
        } else if (strcmp(operands[0], "exit") == 0) {
            break; // Exit the loop and terminate the program
        } else {
            fprintf(stderr, "Unknown command: %s\n", operands[0]);
        }

        // Free allocated memory for operands
        for (int i = 0; i < operandCounter; i++) {
            free(operands[i]);
        }
    }

    return 0;
}
