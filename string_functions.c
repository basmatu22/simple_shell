#include "main.h"
/**
 * _strlen - Calculates length of a string
 * @str: String
 *
 * Return: length of string
 */
int _strlen(char *str)
{
	int len = 0;

	if (str == NULL)
		return (0);
	while (*str++)
		len++;
	return (len);
}
/**
 * _strcpy - copied string
 * @dest: to be copied to
 * @src: to be copied frmo
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int src_len, i;

	src_len = _strlen(src);
	if (dest == NULL)
		return (NULL);
	for (i = 0; i < src_len; i++)
		dest[i] = src[i];
	dest[src_len] = '\0';
	return (dest);
}
/**
 * _strdup - copies a string
 * @str: string to be copied
 *
 * Return: pointer to allocated space
 */
char *_strdup(char *str)
{
	int i = 0;
	int length = 0;
	char *string;

	if (str == NULL)
		return (NULL);

	while (*(str + i) != '\0')
	{
		length++;
		i++;
	}

	i = 0;
	string = malloc(sizeof(char) * length + 1);

	if (string == NULL)
		return (NULL);

	while (*(str + i) != '\0')
	{
		*(string + i) = *(str + i);
		i++;
	}
	*(string + i) = '\0';
	return (string);
}
/**
 * _strcat - concatenates two strings
 * @dest: destination string
 * @src: source string
 * Return: destinateion string
 */
char *_strcat(char *dest, char *src)
{
	int dest_len, src_len, i;

	dest_len = _strlen(dest);
	src_len = _strlen(src);

	for (i = 0; i < src_len; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + src_len] = '\0';
	return (dest);
}
/**
 * _strncmp - compares two strings
 * @s1: first string
 * @s2: second string
 * @n: number of characters to compare
 *
 * Return: 0 if successful
 */
int _strncmp(char *s1, char *s2, int n)
{
	int i, len1;

	len1 = _strlen(s1);
	if (len1 < n)
		return (1);
	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
			return (1);
	}
	return (0);
}
