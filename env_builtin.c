#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int builtin_setenv(char **args)
{
    if (args[1] == NULL || args[2] == NULL)
    {
        fprintf(stderr, "setenv: Missing argument(s)\n");
        return -1;
    }

    if (setenv(args[1], args[2], 1) != 0)
    {
        perror("setenv");
        return -1;
    }

    return 0;
}

int builtin_unsetenv(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "unsetenv: Missing argument\n");
        return -1;
    }

    if (unsetenv(args[1]) != 0)
    {
        perror("unsetenv");
        return -1;
    }

    return 0;
}

