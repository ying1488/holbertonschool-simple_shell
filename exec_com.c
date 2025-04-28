#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

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
	{
		/* Build full path string: dir + "/" + command + null */
		full_len = strlen(dir) + 1 + strlen(command) + 1;
		full_path = malloc(full_len);
		if (!full_path)
			free(path_copy);
			return (NULL);
		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, command);

		/* Check if this file exists and is executable */
		if (access(full_path, X_OK) == 0)
			free(path_copy);
			return (full_path); /* SUCCESS: Return this path */
		/* Otherwise try next directory */
		free(full_path);
		dir = strtok(NULL, ":");
	}
	/* Not found */
	free(path_copy);
	return (NULL);
}



/**
 * handle_builtin_exit - Handle the 'exit' built-in command
 * @args: Null-terminated array of arguments passed to the shell
* Return: 1 if 'exit' command is executed, 0 otherwise
 */
int handle_builtin_exit(char **args)
{
	if (_strcmp(args[0], "exit") == 0)
	{
		if (isatty(STDIN_FILENO))  /* Check if shell is interactive */
		{
			free_args(args);
			exit(EXIT_SUCCESS);
		}
		return (1); /* Exit command is handled */
	}
	return (0);  /* Command is not exit */
}

/**
 * get_command_path - Find the full path of a command
 * @args: Null-terminated array of arguments passed to the shell
 * Return: A string containing the full path to the command if found,
 */
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
/**
 * execute_fork - Fork the process and execute a command
 * @path: Full path to the command to be executed
 * @args: Null-terminated array of arguments passed to the shell
 * Return: The status code of the executed command.
 */
int execute_fork(char *path, char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);  /* Fork failed */
	}

	if (pid == 0)
	{
		if (execve(path, args, environ) == -1)
		{
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	return (status);
}

/**
 * execute_command - Execute a command in a new process
 * @args: Null-terminated array of arguments passed to the shell
  */
void execute_command(char **args)
{
	static int last_status;  /* Store the last exit status */
	char *path = NULL;

	if (!args || !args[0])
		return;
	/* Handle built-in command: exit */
	if (handle_builtin_exit(args)
		return;
	/* Find command path */
	path = get_command_path(args);
	if (!path)
	{
		write(STDERR_FILENO, "./hsh: 1: ", 10);
		write(STDERR_FILENO, args[0], _strlen(args[0]));
		write(STDERR_FILENO, ": not found\n", 12);
		last_status = 127;  /* Set last_status to indicate command not found */
		if (!isatty(STDIN_FILENO))
		{
			free_args(args);
			exit(last_status);  /* Exit with the appropriate status */
		}
		return;
		}
	    /* Fork and execute the command */
	    last_status = execute_fork(path, args);
	    free(path);
}
