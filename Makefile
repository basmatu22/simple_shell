CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
OBJ = shell.o getline.o env_builtin.o
TARGET = shell

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

shell.o: shell.c shell.h
	$(CC) $(CFLAGS) -c shell.c

getline.o: getline.c getline.h
	$(CC) $(CFLAGS) -c getline.c

env_builtin.o: env_builtin.c shell.h
	$(CC) $(CFLAGS) -c env_builtin.c

clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: all clean

