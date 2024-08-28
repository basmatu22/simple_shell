#include "main.h"
/**
 * handle_ctrlc - Ctrl+C handler
 * @signum: Signal number
 *
 */
void handle_ctrlc(int signum)
{
	(void) signum;

	write(STDOUT_FILENO, "\n$ ", 3);
}
/**
 * handle_ctrld - Ctrl+D handler
 * @input: command to free
 *
 * Return: 0 if success
 */
int handle_ctrld(char *input)
{
	free(input);
	if (isatty(STDIN_FILENO) == 1)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
