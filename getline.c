#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

ssize_t custom_getline(char **lineptr, size_t *n, int fd) {
    static char buffer[BUFFER_SIZE];
    static size_t buffer_pos;
    static size_t buffer_end;

    ssize_t total_read = 0;
    size_t line_len = 0;

    if (*lineptr == NULL || *n == 0) {
        *n = BUFFER_SIZE;
        *lineptr = malloc(*n);
        if (*lineptr == NULL) {
            return -1;
        }
    }

    while (1) {
        if (buffer_pos >= buffer_end) {
            ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE);
            if (bytes_read == 0) { /* EOF */
                if (total_read == 0) {
                    return -1;
                }
                break;
            } else if (bytes_read < 0) { /* Error */
                return -1;
            }
            buffer_pos = 0;
            buffer_end = bytes_read;
        }

        while (buffer_pos < buffer_end) {
            (*lineptr)[line_len++] = buffer[buffer_pos++];
            total_read++;

            if ((*lineptr)[line_len - 1] == '\n') {
                (*lineptr)[line_len] = '\0';
                return total_read;
            }

            if (line_len >= *n - 1) {
                char *new_lineptr;

                *n *= 2;
                new_lineptr = realloc(*lineptr, *n);
                if (new_lineptr == NULL) {
                    return -1;
                }
                *lineptr = new_lineptr;
            }
        }
    }

    (*lineptr)[line_len] = '\0';
    return total_read;
}

