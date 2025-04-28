#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

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
	if (handle_builtin_exit(args))
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
