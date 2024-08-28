#include <unistd.h>
/**
 * _putchar - prints a character
 * @c: Character to print
 *
 * Return: number of characters printed
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
