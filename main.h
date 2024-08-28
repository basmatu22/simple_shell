#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

void prompt(void);

int _strlen(char *str);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
int _strncmp(char *s1, char *s2, int n);
int _putchar(char *c, int n);
int space_handler(char *input);

char **string_parse(char *input);
void handle_ctrlc(int signum);
int handle_ctrld(char *input);
char *_locate(char *command, char **env);
void print_error(char **argv, char **av, int counter, char *input);
int _execute(char **argv, char **av, char **env, int counter, char *input);

char *_realloc(char *ptr);
void _free(char *input, char **av);

#endif
