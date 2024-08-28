#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "getline.h"
#include "shell.h"

/* Function declarations */
int handle_builtin_commands(char *line);
void handle_exit(char *line);
void handle_command(char *line);
void execute_command(char *command);
void print_env(void);

/* Definitions */
#define BUFFER_SIZE 1024
#define PROMPT "#cisfun$ "

extern char **environ;

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while (1)
    {
        printf(PROMPT);
        nread = custom_getline(&line, &len, STDIN_FILENO);
        if (nread == -1)
        {
            if (feof(stdin))
            {
                printf("\n");
                break;
            }
            else
            {
                perror("getline");
                continue;
            }
        }

        line[strcspn(line, "\n")] = '\0';

        if (line[0] == '\0')
            continue;

        if (handle_builtin_commands(line))
            continue;

        handle_command(line);
    }

    free(line);
    return (0);
}

int handle_builtin_commands(char *line)
{
    if (strncmp(line, "setenv", 6) == 0)
    {
        char *args[] = {strtok(line, " "), strtok(NULL, " "), strtok(NULL, " "), NULL};
        return builtin_setenv(args);
    }

    if (strncmp(line, "unsetenv", 8) == 0)
    {
        char *args[] = {strtok(line, " "), strtok(NULL, " "), NULL};
        return builtin_unsetenv(args);
    }

    return (0);
}

void handle_exit(char *line)
{
    char *status_str = line + 5;  // Point to the argument after "exit "
    int status = 0;

    if (*status_str != '\0')
    {
        char *endptr;
        status = strtol(status_str, &endptr, 10);

        if (*endptr != '\0')
        {
            fprintf(stderr, "exit: %s: numeric argument required\n",
                    status_str);
            return;
        }
    }

    free(line);
    exit(status);
}

void handle_command(char *line)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        execute_command(line);
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
}

void execute_command(char *command)
{
    char *argv[] = {command, NULL};
    if (execve(command, argv, NULL) == -1)
    {
        perror("./shell");
    }
}

void print_env(void)
{
    char **env = environ;
    while (*env)
    {
        printf("%s\n", *env);
        env++;
    }
}

