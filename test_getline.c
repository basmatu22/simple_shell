#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "getline.h"

int main() {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while ((nread = custom_getline(&line, &len, STDIN_FILENO)) != -1) {
        printf("Retrieved line of length %zu: %s", nread, line);
    }

    free(line);
    return 0;
}

