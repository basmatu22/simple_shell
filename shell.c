#include "shell.h"

#define BUFFER_SIZE 1024
#define PROMPT "#cisfun$ "

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while (1)
    {
        printf(PROMPT);
        nread = getline(&line, &len, stdin);
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
        char *args[4];
        args[0] = strtok(line, " ");
        args[1] = strtok(NULL, " ");
        args[2] = strtok(NULL, " ");
        args[3] = NULL;
        return builtin_setenv(args);
    }

    if (strncmp(line, "unsetenv", 8) == 0)
    {
        char *args[3];
        args[0] = strtok(line, " ");
        args[1] = strtok(NULL, " ");
        args[2] = NULL;
        return builtin_unsetenv(args);
    }

    return (0);
}

void handle_exit(char *line)
{
    char *status_str = line + 5;  /* Point to the argument after "exit " */
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
    }
    else
    {
        wait(NULL);
    }
}

void execute_command(char *command)
{
    char *argv[2];
    argv[0] = command;
    argv[1] = NULL;

    if (execvp(command, argv) == -1)
    {
        perror("execvp");
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

