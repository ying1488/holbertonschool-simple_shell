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

typedef struct {
    int exit_status;
    char *input_line;
} shell_ctx_t;

/* Function prototypes */
void execute_command(char **args);
char *get_command_path(char **args);
char *find_path(char *command);
char **split_line(char *line);
void free_args(char **args);
void prompt(void); /* if you have a function to print your shell prompt */
int shell_exit(char **args);
void check_exit_builtin(char *input, shell_ctx_t *ctx);
char *_strdup(const char *s);
char *_strchr(const char *s, char c);
int _strlen(const char *s);
int _strcmp(const char *s1, const char *s2);

#endif /* SHELL_H */
