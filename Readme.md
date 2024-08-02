# MyShell

MyShell is a basic shell implementation written in C. It supports various internal commands and can execute external commands. This shell allows for file operations, directory changes, and provides basic help and environment variable functionalities.

## Features

- **Internal Commands**:
  - `mypwd`: Prints the current working directory.
  - `myecho <message>`: Prints the specified message.
  - `mycp <source> <target>`: Copies a file from the source path to the target path.
  - `mymv <source> <target>`: Moves or renames a file from the source path to the target path.
  - `mycd <directory>`: Changes the current working directory.
  - `myhelp`: Displays a list of supported commands.
  - `myexit`: Exits the shell program.
  - `myenv`: Prints all environment variables.
  - `type <command>`: Determines if a command is internal or external.

- **External Commands**:
  - Executes commands found in directories listed in the `PATH` environment variable.

## Files

- `command.c`: Implements command handling functions and utilities.
- `command.h`: Header file containing function declarations and macro definitions used in `command.c`.
- `newshell.c`: Contains the main program logic, including user interaction and command execution.

## `command.h`

This header file defines the function prototypes and macro constants used in `command.c`. It includes:

- Function prototypes for:
  - `checkPath()`
  - `cp_command()`
  - `mv_command()`
  - `cd_command()`
  - `echo_command()`
  - `supported_commands()`
  - `env_command()`
  - `type_command()`
  - `external_command()`
  - `parse_input()`
- Macro definitions for standard file descriptors:
  - `STDIN`
  - `STDOUT`
  - `STDERR`

## Compilation

To compile the shell program, use the following command:

```sh
gcc -o myshell newshell.c command.c
