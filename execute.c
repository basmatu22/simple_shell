#include "main.h"
/**
 * _execute - executes a command
 * @argv: Arrays of strings
 * @av: Array of inputted commands
 * @env: Environment variable
 * @counter: Variable to keep count
 * @input: Command user entered(newline removed)
 *
 * Return: 0 on success
 */
int _execute(char **argv, char **av, char **env, int counter, char *input)
{
	struct stat buffer;
	pid_t pid;
	int status;
	char *path;

	if (argv == NULL || av == NULL)
		return (-1);
	path = _locate(av[0], env);
	if (path == NULL)
	{
		print_error(argv, av, counter, input);
		return (0);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error forking");
		return (-1);
	}
	if (pid == 0)
	{
		if (stat(path, &buffer) == -1)
		{
			print_error(argv, av, counter, input);
			return (0);
		}
		else
			execve(path, av, env);
	}
	else
	{
		wait(&status);
		free(path);
	}
	return (1);
}
