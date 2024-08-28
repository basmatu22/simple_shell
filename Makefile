CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89
OBJ = shell.o getline.o env_builtin.o

shell: $(OBJ)
	$(CC) $(CFLAGS) -o shell $(OBJ)

shell.o: shell.c shell.h
	$(CC) $(CFLAGS) -c shell.c

getline.o: getline.c getline.h
	$(CC) $(CFLAGS) -c getline.c

env_builtin.o: env_builtin.c shell.h
	$(CC) $(CFLAGS) -c env_builtin.c

clean:
	rm -f $(OBJ) shell

