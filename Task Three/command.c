#include "command.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

// Function to check if a path is a directory or file
int checkPath(char *path) {
    struct stat path_stat;
    if (stat(path, &path_stat) != 0) {
        perror("Error");
        return 0;
    }
    if (S_ISDIR(path_stat.st_mode)) {
        return 1; // Directory
    } else if (S_ISREG(path_stat.st_mode)) {
        return 2; // File
    } else {
        printf("Not a valid path\n");
        return 0;
    }
}

// Function to handle the cp command
void cp_command(char *source_path, char *target_path) {
    char buffer[1024];

    if (checkPath(target_path) == 1) {
        char *fileName = basename(source_path);
        strcat(target_path, "/");
        strcat(target_path, fileName);
    }

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

    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
        if (fwrite(buffer, 1, bytesRead, targetFile) != bytesRead) {
            perror("Error writing to target file");
            fclose(sourceFile);
            fclose(targetFile);
            return;
        }
    }

    fclose(sourceFile);
    fclose(targetFile);
}

// Function to handle the mv command
void mv_command(char *source_path, char *target_path) {
    cp_command(source_path, target_path);
    if (remove(source_path) != 0) {
        perror("Error removing source file");
    }
}

// Function to handle the cd command
void cd_command(char *path) {
    if (chdir(path) != 0) {
        perror("Error changing directory");
    }
}

// Function to handle the echo command
void echo_command(char **message, int count) {
    for (int i = 0; i < count; i++) {
        printf("%s ", message[i]);
    }
    printf("\n");
}

// Function to print supported commands
void supported_commands() {
    printf("Supported commands are:\n");
    printf("mypwd  : Print current working directory\n");
    printf("myecho : Print a certain sentence\n");
    printf("mycp   : Copy files\n");
    printf("mymv   : Move or rename a file\n");
    printf("myhelp : Print this help message\n");
    printf("myexit : Exit the shell program\n");
    printf("myenv  : Print all environment variables\n");
}

// Function to execute env command
void env_command(char **env_variable) {
    int i = 0;
    while (env_variable[i] != NULL) {
        printf("%s\n", env_variable[i++]);
    }
}

// Function to check type of command
void type_command(char *command_name) {
    // Array of internal commands
    char *internal_commands[] = {"myecho", "mypwd", "myhelp", "mycp", "mymv", "myenv", "myexit", NULL};

    // Check if the command is one of the internal commands
    for (int i = 0; internal_commands[i] != NULL; i++) {
        if (strcmp(internal_commands[i], command_name) == 0) {
            printf("This is an internal command\n");
            return;
        }
    }

    // Check if the command is an external command
    char *path_env = getenv("PATH");
    if (path_env == NULL) {
        printf("PATH environment variable not set\n");
        return;
    }

    // Make a copy of the PATH environment variable
    char path_env_copy[200];
    strncpy(path_env_copy, path_env, sizeof(path_env_copy));
    path_env_copy[sizeof(path_env_copy) - 1] = '\0';

    char path[1024];
    char *path_token = strtok(path_env_copy, ":");
    while (path_token != NULL) {
        // Reset the path buffer for each directory
        snprintf(path, sizeof(path), "%s/%s", path_token, command_name);

        // Check if the path is executable
        if (access(path, X_OK) == 0) {
            printf("This is an external command\n");
            return;
        }
        path_token = strtok(NULL, ":");
    }
    printf("Command not found\n");
}


// Function to execute external command
void external_command(char **ex_command,int counter) {
     
  

  char **copy_arg=malloc(counter*sizeof( char *));
        //copy arguments  to another  array to avoid overwrite

          for (int i=0;i<counter;i++)
{
copy_arg[i]=malloc((strlen(ex_command[i])+1)*sizeof(char));
strcpy(copy_arg[i],ex_command[i]); // copy arguments in another array  to avoid overwrite 
}
    
    int forkid = fork(); // Create child process using fork

if (forkid==0)
  {


     execvp(copy_arg[0],copy_arg);
exit(EXIT_FAILURE);
perror("fail in execvp process");
  }
if(forkid>0)
{
int satuts=0;
int childid =wait(&satuts);
} 
// free dynamic allocation of copied array 
          for (int i=0;i<counter;i++)
{
free(copy_arg[i]);
}
free(copy_arg);
return ;
}

// Function to parse input and split into operands
int parse_input(char *shellMsg, char *command, char ***operands) {
    ssize_t readSize;

    // Prompt for user input
    write(STDOUT, shellMsg, strlen(shellMsg));
    readSize = read(STDIN, command, 1024 - 1);

    if (readSize <= 0) {
        return -1;
    }

    command[readSize - 1] = '\0'; // Null-terminate the command string

    // Allocate memory for the array of operands
    *operands = malloc(1024 * sizeof(char * ));
    if (*operands == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    int operandCounter = 0;
    char *token = strtok(command, " ");
    while (token != NULL) {
        (*operands)[operandCounter] = malloc(strlen(token) + 1);
        if ((*operands)[operandCounter] == NULL) {
            perror("Memory allocation failed");
            exit(1);
        }
        strcpy((*operands)[operandCounter], token);
        operandCounter++;
        token = strtok(NULL, " ");
    }

    return operandCounter;
}
