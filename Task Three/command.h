#ifndef COMMAND_H
#define COMMAND_H
extern char **environ ;
void env_command(char ** env_variable);
void cp_command(char *source_path, char *target_path);
void external_command(char **ex_command,int counter);

void mv_command(char *source_path, char *target_path);
void cd_command(char *path);
void echo_command(char **message, int count);
void supported_commands();
int parse_input(char *shellMsg, char *command, char ***operands);
void type_command(char *command_name);
#endif // COMMAND_H
