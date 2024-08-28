#include "main.h"
/**
 * prompt - Prints prompt to STDOUT
 */
void prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}
