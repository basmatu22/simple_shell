#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define PROMPT "#cisfun$ "

/**
 * execute_command - Executes a command using execve
 * @command: The command to execute
 */
void execute_command(char *command)
{
char *argv[] = {command, NULL};
if (execve(command, argv, NULL) == -1)
{
perror("./shell");
}
}
/**
 * read_input - Reads a line of input from the user
 * @line: Pointer to the buffer where the line will be stored
 * @len: Pointer to the size of the buffer
 *
 * Return: The number of characters read, or -1 on error
 */
ssize_t read_input(char **line, size_t *len)
{
ssize_t nread;

printf(PROMPT);
nread = getline(line, len, stdin);
if (nread == -1)
{
if (feof(stdin))
{
printf("\n");
return (-1);
}
else
{
perror("getline");
}
}

return (nread);
}
/**
 * fork_and_execute - Forks a process and executes the command
 * @line: The command to execute
 */
void fork_and_execute(char *line)
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
/**
 * main - The entry point for the shell program
 *
 * Return: 0 on success, or another value on error
 */
int main(void)
{
char *line = NULL;
size_t len = 0;
ssize_t nread;

while (1)
{
nread = read_input(&line, &len);
if (nread == -1)
{
break;
}
line[strcspn(line, "\n")] = '\0';
if (line[0] == '\0')
{
continue;
}
fork_and_execute(line);
}
free(line);
return (0);
}
