#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>

void execute_command(char *command);
void print_env(void);
int builtin_setenv(char **args);
int builtin_unsetenv(char **args);

#endif 

