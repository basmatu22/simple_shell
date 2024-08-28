#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * _setenv - Initializes or modifies an environment variable.
 * @variable: The name of the environment variable.
 * @value: The value to set for the environment variable.
 *
 * Return: 0 on success, -1 on failure.
 */
int _setenv(const char *variable, const char *value)
{
    if (variable == NULL || value == NULL)
    {
        fprintf(stderr, "setenv: missing arguments\n");
        return (-1);
    }

    if (setenv(variable, value, 1) != 0)
    {
        perror("setenv");
        return (-1);
    }

    return (0);
}

/**
 * _unsetenv - Removes an environment variable.
 * @variable: The name of the environment variable to remove.
 *
 * Return: 0 on success, -1 on failure.
 */
int _unsetenv(const char *variable)
{
    if (variable == NULL)
    {
        fprintf(stderr, "unsetenv: missing argument\n");
        return (-1);
    }

    if (unsetenv(variable) != 0)
    {
        perror("unsetenv");
        return (-1);
    }

    return (0);
}
