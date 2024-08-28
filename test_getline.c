#include <stdio.h>
#include <stdlib.h>
#include "getline.h"

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    printf("Enter a line: ");
    nread = custom_getline(&line, &len, STDIN_FILENO);

    if (nread != -1)
    {
        printf("Retrieved line of length %lu: %s\n", (unsigned long)nread, line);
    }
    else
    {
        printf("Error or end of file encountered.\n");
    }

    free(line);
    return (0);
}

