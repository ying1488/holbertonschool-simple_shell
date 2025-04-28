#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * main - Entry point for the simple shell program
 * Return: Always returns 0 on successful execution.
 */

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **args;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		args = split_line(line);
		if (args[0] != NULL)
			execute_command(args);
		free(args);
	}
	free(line);
	return (0);
}
