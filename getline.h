#ifndef GETLINE_H
#define GETLINE_H

#include <stddef.h>
#include <unistd.h>

ssize_t custom_getline(char **lineptr, size_t *n, int fd);

#endif 

