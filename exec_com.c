#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

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

char *find_path(char *command)
{
    char *path_env, *path_copy, *dir;
    char *full_path;
    size_t full_len;

    if (!command)
        return NULL;

    /* Get PATH from the environment */
    path_env = get_path_env();
    if (!path_env)
        return NULL;

    /* Make a copy because strtok modifies the string */
    path_copy = strdup(path_env);
    if (!path_copy)
        return NULL;

    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        /* Build full path string: dir + "/" + command + null */
        full_len = strlen(dir) + 1 + strlen(command) + 1;
        full_path = malloc(full_len);
        if (!full_path)
        {
            free(path_copy);
            return NULL;
        }

        strcpy(full_path, dir);
        strcat(full_path, "/");
        strcat(full_path, command);

        /* Check if this file exists and is executable */
        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return full_path; /* SUCCESS: Return this path */
        }

        /* Otherwise try next directory */
        free(full_path);
        dir = strtok(NULL, ":");
    }

    /* Not found */
    free(path_copy);
    return NULL;
}
/**
 * execute_command - Execute a command
 * @args: Null-terminated array of arguments
 */
void execute_command(char **args)
{
  static int last_status = 0;  /*To store the last exit status*/
    pid_t pid;
    int status;
    char *path = NULL;

    if (!args || !args[0])
        return;

    /* Handle built-in command: exit */
    if (_strcmp(args[0], "exit") == 0)
    {
        if (isatty(STDIN_FILENO))  /* Check if shell is interactive */
        {
            free_args(args);
            exit(EXIT_SUCCESS);
        }
        else
        {
            return;  /* Ignore 'exit' in non-interactive mode */
        }
    }

    if (_strchr(args[0], '/'))
        path = _strdup(args[0]);
    else
        path = find_path(args[0]);

    if (!path)
    {
        write(STDERR_FILENO, "./hsh: 1: ", 10);
        write(STDERR_FILENO, args[0], _strlen(args[0]));
        write(STDERR_FILENO, ": not found\n", 12);

        last_status = 127;  /*Set last_status to indicate command not found*/

        if (!isatty(STDIN_FILENO))
        {
            free_args(args);
            exit(last_status);  /*Exit with the appropriate status*/
        }
        return;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free(path);
        return;
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
        last_status = status;  /*Store the last command's status*/
    }

    free(path);
}
