#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "getline.h"

#define BUFFER_SIZE 1024
#define PROMPT "#cisfun$ "

extern char **environ;

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

        // Remove the newline character from the input
        line[strcspn(line, "\n")] = '\0';

        // Check for empty command
        if (line[0] == '\0')
        {
            continue;
        }

        // Handle the exit command with or without status argument
        if (strncmp(line, "exit", 4) == 0)
        {
            char *status_str = line + 5; // Point to the argument after "exit "
            int status = 0;

            if (*status_str != '\0') // Check if there is an argument
            {
                // Convert the status argument to an integer
                char *endptr;
                status = strtol(status_str, &endptr, 10);

                // Check for invalid integer input
                if (*endptr != '\0') 
                {
                    fprintf(stderr, "exit: %s: numeric argument required\n", status_str);
                    continue;
                }
            }

            free(line);
            exit(status);
        }

        // Handle the env command
        if (strcmp(line, "env") == 0)
        {
            print_env();
            continue; // Display environment and continue loop
        }

        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            continue;
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

    free(line);
    return 0;
}

