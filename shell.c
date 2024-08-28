#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "getline.h"
#include "shell.h"

/* Function declarations */
int handle_builtin_commands(char **args);
void handle_exit(char *line);
void handle_command(char **args);
void execute_command(char *command);
void print_env(void);
char **parse_line(char *line);
int _setenv(const char *name, const char *value); /* Custom declaration */
int _unsetenv(const char *name); /* Custom declaration */

/* Definitions */
#define BUFFER_SIZE 1024
#define PROMPT "#cisfun$ "

extern char **environ;

/**
 * main - Entry point of the shell.
 *
 * Return: Always 0.
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char **args;

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

        line[strcspn(line, "\n")] = '\0'; /* Remove the newline character */

        if (line[0] == '\0')
            continue;

        args = parse_line(line);

        if (args[0] == NULL)
        {
            free(args);
            continue;
        }

        if (handle_builtin_commands(args))
        {
            free(args);
            continue;
        }

        handle_command(args);

        free(args);
    }

    free(line);
    return (0);
}

/**
 * handle_builtin_commands - Handles built-in commands.
 * @args: Array of arguments.
 *
 * Return: 1 if command was handled, 0 otherwise.
 */
int handle_builtin_commands(char **args)
{
    if (strcmp(args[0], "exit") == 0)
    {
        handle_exit(args[1]);
        return (1);
    }
    else if (strcmp(args[0], "setenv") == 0)
    {
        if (args[1] == NULL || args[2] == NULL)
        {
            fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
        }
        else
        {
            _setenv(args[1], args[2]);
        }
        return (1);
    }
    else if (strcmp(args[0], "unsetenv") == 0)
    {
        if (args[1] == NULL)
        {
            fprintf(stderr, "Usage: unsetenv VARIABLE\n");
        }
        else
        {
            _unsetenv(args[1]);
        }
        return (1);
    }
    else if (strcmp(args[0], "env") == 0)
    {
        print_env();
        return (1);
    }

    return (0);
}

/**
 * handle_exit - Handles the exit command.
 * @line: Argument after "exit ".
 */
void handle_exit(char *line)
{
    int status = 0;

    if (line != NULL)
    {
        char *endptr;

        status = strtol(line, &endptr, 10);

        if (*endptr != '\0')
        {
            fprintf(stderr, "exit: %s: numeric argument required\n", line);
            return;
        }
    }

    exit(status);
}

/**
 * handle_command - Executes a command.
 * @args: Array of arguments.
 */
void handle_command(char **args)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        execvp(args[0], args);
        perror("./shell");
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;

        waitpid(pid, &status, 0);
    }
}

/**
 * execute_command - Executes a command directly.
 * @command: Command to execute.
 */
void execute_command(char *command)
{
    char *argv[2];

    argv[0] = command;
    argv[1] = NULL;

    if (execve(command, argv, environ) == -1)
    {
        perror("./shell");
    }
}

/**
 * print_env - Prints the environment variables.
 */
void print_env(void)
{
    char **env = environ;

    while (*env)
    {
        printf("%s\n", *env);
        env++;
    }
}

/**
 * parse_line - Parses a line into an array of arguments.
 * @line: Input line to parse.
 *
 * Return: Array of arguments.
 */
char **parse_line(char *line)
{
    int bufsize = 64, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\r\n\a");
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[position] = NULL;
    return (tokens);
}

