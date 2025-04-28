#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

/**
 * search_in_path - Search for a command in the PATH directories.
 * @command: Command to find.
 *
 * Return: Pointer to a string with the full path if found, NULL otherwise.
 */
char *search_in_path(char *command)
{
	char *path_env, *path_copy, *token, *full_path;

	if (command == NULL)
		return (NULL);
	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			{ return (strdup(command)); }
		else
			{ return (NULL);}
	}

	path_env = getenv("PATH");
	if (path_env == NULL)
		return (NULL);
	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return (NULL);
	
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		full_path = malloc(strlen(token) + strlen(command) + 2);
		if (full_path == NULL)
			{free(path_copy);
			return (NULL);}
		sprintf(full_path, "%s/%s", token, command);
		if (access(full_path, X_OK) == 0)
			{free(path_copy);
			return (full_path);}
		free(full_path);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
