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

/**
 * struct shell_ctx -  Represents the context/state
 * of the shell session.
 * @exit_status: The exit status code of the last executed command or
 * the exit code the shell should return upon exiting.
 * @input_line: A dynamically allocated string
 * containing the most recent line of user input.
 */
typedef struct shell_ctx
{
	int exit_status;
	char *input_line;
} shell_ctx_t;

/* Function prototypes */
void execute_command(char **args);
char *get_command_path(char **args);
char *find_path(char *command);
char *get_path_env(void);
char **split_line(char *line);
void free_args(char **args);
void prompt(void);
int shell_exit(char **args);
void check_exit_builtin(char *input, shell_ctx_t *ctx);
char *_strdup(const char *s);
char *_strchr(const char *s, char c);
int _strlen(const char *s);
int _strcmp(const char *s1, const char *s2);

#endif /* SHELL_H */
