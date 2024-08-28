#include "main.h"
/**
 * find_path - finds path
 * @envp: Environment variable
 *
 * Return: path
 */
char *find_path(char **envp)
{
	char *path;
	int i = 0;

	for (i = 0; envp[i] != NULL; i++)
	{
		if (_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = _strdup(envp[i] + 5);
			if (path == NULL)
				return (NULL);
			return (path);
		}
	}
	return (NULL);
}
/**
 * free_path - free path and copy of path
 * @path: Path
 * @path_copy: Copy of path
 */
void free_path(char *path, char *path_copy)
{
	free(path);
	free(path_copy);
}
/**
 * file_path_handle - free path and copy of path
 * @path: Path
 * @path_copy: Copy of path
 */
void file_path_handle(char *path, char *path_copy)
{
	free_path(path, path_copy);
	exit(EXIT_FAILURE);
}
/**
 * _locate - locates a command in PATH
 * @cmd: Command to locate
 * @env: Environment
 * Return: Pointer to the full path
 */
char *_locate(char *cmd, char **env)
{
	char *path, *path_copy, *token, *file_path;
	struct stat buffer;

	path = find_path(env);
	if (path)
	{
		path_copy = strdup(path);
		token = strtok(path_copy, ":");
		while (token != NULL)
		{
			file_path = malloc(_strlen(cmd) + _strlen(token) + 2);
			if (file_path == NULL)
				file_path_handle(path, path_copy);
			_strcpy(file_path, token);
			_strcat(file_path, "/");
			_strcat(file_path, cmd);
			if (stat(file_path, &buffer) == 0)
			{
				free_path(path, path_copy);
				return (file_path);
			}
			else
			{
				free(file_path);
				token = strtok(NULL, ":");
			}
		}
		free(path_copy);
		if (stat(cmd, &buffer) == 0)
		{
			file_path = malloc(_strlen(cmd) + 1);
			_strcpy(file_path, cmd);
			free(path);
			return (file_path);
		}
		free(path);
	}
	return (NULL);
}
