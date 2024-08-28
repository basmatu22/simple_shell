#include "main.h"
/**
 * _realloc - Reallocates memory
 * @ptr: pointer to string
 *
 * Return: pointer to new memory block
 */
char *_realloc(char *ptr)
{
	char *newptr;
	int i = 0;

	if (ptr == NULL)
		return (NULL);
	while (*(ptr + i) != '\n')
		i++;
	newptr = malloc(sizeof(char) * i + 1);
	if (newptr == NULL)
		return (NULL);
	i = 0;
	while (*(ptr + i) != '\n')
	{
		*(newptr + i) = *(ptr + i);
		i++;
	}
	*(newptr + i) = '\0';
	free(ptr);
	return (newptr);
}
/**
 * _free - frees memory allocated
 * @input: Command entered
 * @av: Array of tokens
 *
 */
void _free(char *input, char **av)
{
	int count = 0;

	while (av[count] != NULL)
	{
		free(av[count]);
		count++;
	}
	free(av[count]);
	free(input);
	free(av);
}
