#include "main.h"
/**
 * print_error - Prints an error to STDERR
 * @argv: Array of Strings
 * @av: Arrays of commands to be execute
 * @counter: Keeps count of command run
 * @input: Command user entered
 */
void print_error(char **argv, char **av, int counter, char *input)
{
	char num = counter + '0';

	write(STDERR_FILENO, argv[0], _strlen(argv[0]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, &num, 1);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, av[0], _strlen(av[0]));
	write(STDERR_FILENO, ": not found\n", 12);
	_free(input, av);
}
