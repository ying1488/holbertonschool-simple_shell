#ifndef SHELL_H
#define SHELL_H

/* Standard libraries */
#include <stdio.h>    /* printf, perror */
#include <stdlib.h>   /* malloc, free, exit */
#include <unistd.h>   /* fork, execve, access */
#include <string.h>   /* strtok, strdup, strchr */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h> /* wait */

/* Global environment */
extern char **environ;

/* Function prototypes */
void execute_command(char **args);
char *find_path(char *command);
char **split_line(char *line);
void free_args(char **args);
void prompt(void); /* if you have a function to print your shell prompt */

#endif /* SHELL_H */
