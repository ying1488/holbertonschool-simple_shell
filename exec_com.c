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
 * get_path_env - Gets the PATH environment variable
 * Return: PATH value or NULL if not found
 */
char *get_path_env(void)
{
    char *path = getenv("PATH");
    return path ? path : NULL;
}

/**
 * find_command_path - Finds the full path of a command
 * @command: The command to find
 * Return: Full path if found, NULL otherwise
 */
char *find_command_path(char *command)
{
    char *path_env, *path_copy, *dir;
    char *full_path = NULL;
    struct stat st;

    if (!command)
        return NULL;

    /* Check if command is already a full path */
    if (command[0] == '/' || command[0] == '.') {
        if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
            return strdup(command);
        return NULL;
    }

    /* Get PATH environment variable */
    path_env = get_path_env();

    /* Handle empty PATH case - check current directory only */
    if (path_env == NULL || *path_env == '\0') {
        char *cwd = getcwd(NULL, 0);
        if (!cwd) return NULL;
        
        full_path = malloc(strlen(cwd) + strlen(command) + 2);
        if (!full_path) {
            free(cwd);
            return NULL;
        }
        sprintf(full_path, "%s/%s", cwd, command);
        free(cwd);

        if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
            return full_path;

        free(full_path);
        return NULL;
    }

    /* Normal PATH lookup */
    path_copy = strdup(path_env);
    if (!path_copy) return NULL;

    dir = strtok(path_copy, ":");
    while (dir != NULL) {
        full_path = malloc(strlen(dir) + strlen(command) + 2);
        if (!full_path) {
            free(path_copy);
            return NULL;
        }
        sprintf(full_path, "%s/%s", dir, command);

        if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR)) {
            free(path_copy);
            return full_path;
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}

/**
 * execute_command - Executes a command with arguments
 * @args: NULL terminated array of arguments
 */
void execute_command(char **args)
{
    char *full_path = NULL;
    pid_t pid;
    int status;

    if (!args || !args[0])
        return;

    /* Handle builtins first */
    if (strcmp(args[0], "exit") == 0) {
        shell_exit(args);
        return;
    }
    else if (strcmp(args[0], "env") == 0) {
        print_environment();
        return;
    }
    else if (strcmp(args[0], "cd") == 0) {
        change_directory(args);
        return;
    }

    /* Find command path */
    full_path = find_command_path(args[0]);
    if (!full_path) {
        fprintf(stderr, "%s: command not found\n", args[0]);
        exit(127); /* Exit with status 127 when command not found */
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        free(full_path);
        return;
    }

    if (pid == 0) {
        /* Child process */
        if (execve(full_path, args, environ) == -1) {
            perror(args[0]);
            free(full_path);
            exit(EXIT_FAILURE);
        }
    } else {
        /* Parent process */
        waitpid(pid, &status, 0);
        free(full_path);
    }
}
