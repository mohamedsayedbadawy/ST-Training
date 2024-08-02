#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "command.h"

#define STDIN 0
#define STDOUT 1
#define STDERR 2

// Main function
int main() {
    char shellMsg[] = "myshell> ";
    char command[1024];
    char **operands;
    int operandCounter;

    while (1) {
        operandCounter = parse_input(shellMsg, command, &operands);

        if (operandCounter == -1) {
            break;
        }

        // Execute command based on the first operand
        if (operandCounter > 0) {
            if (strcmp(operands[0], "mypwd") == 0) {
                char cwd[1024];
                if (getcwd(cwd, sizeof(cwd)) != NULL) {
                    printf("%s\n", cwd);
                } else {
                    perror("Error getting current directory");
                }
            } else if (strcmp(operands[0], "myecho") == 0) {
                if (operandCounter < 2) {
                    fprintf(stderr, "Usage: echo <message>\n");
                } else {
                    echo_command(&operands[1], operandCounter - 1);
                }
            } else if (strcmp(operands[0], "mycp") == 0) {
                if (operandCounter != 3) {
                    fprintf(stderr, "Usage: cp <source> <target>\n");
                } else {
                    cp_command(operands[1], operands[2]);
                }
            } else if (strcmp(operands[0], "mymv") == 0) {
                if (operandCounter != 3) {
                    fprintf(stderr, "Usage: mv <source> <target>\n");
                } else {
                    mv_command(operands[1], operands[2]);
                }
            } else if (strcmp(operands[0], "mycd") == 0) {
                if (operandCounter != 2) {
                    fprintf(stderr, "Usage: cd <directory>\n");
                } else {
                    cd_command(operands[1]);
                }
            } else if (strcmp(operands[0], "myhelp") == 0) {
                supported_commands();
            } else if (strcmp(operands[0], "myexit") == 0) {
                for (int i = 0; i < operandCounter; i++) {
                    free(operands[i]);
                }
                free(operands);
                exit(0);
            } else if (strcmp(operands[0], "myenv") == 0) {
                if (environ == NULL) {
                    fprintf(stderr, "error in usage env command\n");
                } else {
                    env_command(environ);
                }
            } else if (strcmp(operands[0], "type") == 0) {
                if (operandCounter < 2) {
                    fprintf(stderr, "error in usage type command\n");
                } else {
                    type_command(operands[1]);
                }
            } else {
                external_command(operands);
	
            }
        }

        // Free dynamically allocated memory for operands
        for (int i = 0; i < operandCounter; i++) {
            free(operands[i]);
        }
        free(operands);
    }

    return 0;
}
