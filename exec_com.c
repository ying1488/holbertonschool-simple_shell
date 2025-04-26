
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "shell.h"
/**
 *
*/

extern char **environ; /* Declare the global environment variable */

char *find_path(char *command)
{
    char *path = NULL, *dir, *full_path;
    struct stat st;
    int i = 0;

    /* Search for PATH in the environ array */
    while (environ[i])
    {
        if (strncmp(environ[i], "PATH=", 5) == 0)
        {
            path = environ[i] + 5; /* Skip "PATH=" */
            break;
        }
        i++;
    }

    if (!path || strcmp(path, "") == 0)
    {
        /* Fallback to /bin if PATH is empty */
        path = "/bin";
    }

    dir = strtok(path, ":");
    while (dir)
    {
        full_path = malloc(strlen(dir) + strlen(command) + 2);
        if (!full_path)
        {
            perror("Error allocating memory");
            return NULL;
        }

        sprintf(full_path, "%s/%s", dir, command);

        if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
        {
            return full_path; /* Command found */
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    return NULL; /* Command not found */
}
/**
 *
 */
void execute_command(char **args)
{
    char *path;
    pid_t pid;
    int status;

    if (args[0] == NULL)
        return; /* Ignore empty input */

    /* Trim leading and trailing spaces here if needed */

    if (args[0][0] == '/' || args[0][0] == '.')
        path = args[0];
    else
        path = find_path(args[0]);

    if (!path)
    {
        write(STDERR_FILENO, args[0], strlen(args[0]));
        write(STDERR_FILENO, ": Command not found\n", 20);
        return;
    }

    pid = fork();
    if (pid == -1)
    {
        perror(args[0]);
        if (path != args[0])
            free(path);
        return;
    }

    if (pid == 0)
    {
        /* Execute the command */
        if (execve(path, args, environ) == -1)
        {
            perror(args[0]);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        /* Parent process waits */
        wait(&status);
    }

    if (path != args[0])
        free(path);
}

