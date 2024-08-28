#include "main.h"
/**
 * space_handler - handles spaces
 * @input: Command entered by user
 *
 * Return: 1 if string contains all spaces
 *
 */
int space_handler(char *input)
{
	int i = 0;

	while (input[i] != '\0')
	{
		if (input[i] != ' ' && input[i] != '\t')
			return (0);
		i++;
	}
	free(input);
	return (1);
}
/**
 * main - gets command from prompt and performs series of operations on it
 * @ac: Argument count
 * @argv: Argument vector
 * @env: Environment variable
 *
 * Return: 1 on success
 */
int main(int ac, char **argv, char **env)
{
	char **av;
	char *input = NULL, *input_new;
	ssize_t bytes_read;
	size_t n = 0;
	int counter = 0;
	(void) ac;

	while (1)
	{
		input = NULL;
		bytes_read = 0;
		counter++;
		if (isatty(STDIN_FILENO))
			prompt();
		signal(SIGINT, handle_ctrlc);
		bytes_read = getline(&input, &n, stdin);
		if (bytes_read == -1 || bytes_read == EOF)
			return (handle_ctrld(input));
		if (input[0] == '\n')
		{
			free(input);
			continue;
		}
		input_new = _realloc(input);
		if (space_handler(input_new))
			continue;
		if (input_new == NULL)
			return (0);
		av = string_parse(input_new);
		if (av == NULL)
		{
			free(input_new);
			return (-1);
		}
		if (_execute(argv, av, env, counter, input_new) == 0)
			continue;
		_free(input_new, av);
	}
	return (1);
}
