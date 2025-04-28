#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * get_path_env - Retrieve the value of the
 * PATH environment variable
 * Return: value of the PATH environment variable
 * (without the "PATH=" prefix),
 * or NULL if the "PATH" entry is not found.
 */
char *get_path_env(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			/* Skip "PATH=" and return the value */
			return (environ[i] + 5);
		}
	}
	return (NULL); /* PATH not found */
}

/**
 * find_path - Search for a command in directories listed
 * in the PATH environment variable
 * @command: The command name to search for.
 * Return: The full path of the executable,
 * NULL if the command is not found or is not executable.
 */
char *find_path(char *command)
{
	char *path_env, *path_copy, *dir;
	char *full_path;
	size_t full_len;

	if (!command)
		return (NULL);
	/* Get PATH from the environment */
	path_env = get_path_env();
	if (!path_env)
		return (NULL);
	/* Make a copy because strtok modifies the string */
	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{/* Build full path string: dir + "/" + command + null */
		full_len = strlen(dir) + 1 + strlen(command) + 1;
		full_path = malloc(full_len);
		if (!full_path)
		{free(path_copy);
		return (NULL);}
	strcpy(full_path, dir);
	strcat(full_path, "/");
	strcat(full_path, command);
	/* Check if this file exists and is executable */
	if (access(full_path, X_OK) == 0)
	{	free(path_copy);
		return (full_path);
	} /* SUCCESS: Return this path */
	/* Otherwise try next directory */
	free(full_path);
	dir = strtok(NULL, ":");
	} /* Not found */
	free(path_copy);
	return (NULL);
}

/**
 * get_command_path - Find the full path of a command
 * @args: Null-terminated array of arguments passed to the shell
 * Return: A string containing the full path to the command
**/
char *get_command_path(char **args)
{
	char *path = NULL;

	if (_strchr(args[0], '/'))
	{
		path = _strdup(args[0]);
	}
	else
	{
		path = find_path(args[0]);
	}
	return (path);
}
