#include "main.h"
#include <unistd.h>
void built_in_commands_cd(char **inside_token, int i);
char curr_working_dir[1000];
char last_working_dir[1000];
// void built_in_commands_echo(char *text);
// void built_in_commands_pwd();