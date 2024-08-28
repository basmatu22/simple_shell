#include "main.h"
/**
 * string_parse - parses a string into elements of an array
 * @input: string to parse
 *
 * Return: Tokenized array
 */
char **string_parse(char *input)
{
	char **av;
	char *input_copy = NULL;
	char *delim = " \n";
	char *token;
	int count = 0, i = 0;

	if (input == NULL)
		return (NULL);
	input_copy = _strdup(input);
	if (input_copy == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	token = strtok(input, delim);
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, delim);
	}
	count++;
	av = malloc(sizeof(char *) * count);
	token = strtok(input_copy, delim);
	while (token != NULL)
	{
		av[i] = _strdup(token);
		token = strtok(NULL, delim);
		i++;
	}
	av[i] = NULL;
	free(input_copy);
	return (av);
}
