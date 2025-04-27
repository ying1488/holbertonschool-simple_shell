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

char *get_path(char *command) {
    char *path = getenv("PATH");
    char *path_copy = strdup(path);
    char *dir = strtok(path_copy, ":");
    char *full_path = NULL;
    
    while (dir) {
        full_path = malloc(strlen(dir) + strlen(command) + 2);
        sprintf(full_path, "%s/%s", dir, command);
        
        if (access(full_path, X_OK) == 0) {
            free(path_copy);
            return full_path;
        }
        
        free(full_path);
        dir = strtok(NULL, ":");
    }
    
    free(path_copy);
    return NULL;
}

void execute_command(char **args) {
    char *command = args[0];
    char *full_path = NULL;
	pid_t pid = fork();
    if (strchr(command, '/')) {
        if (access(command, X_OK) == 0) {
            full_path = strdup(command);
        }
    } else {
        full_path = get_path(command);
    }
    
    if (!full_path) {
        fprintf(stderr, "./shell: No such file or directory\n");
        return;
    }
    
    if (pid == 0) {
        execve(full_path, args, environ);
        perror("execve");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("fork");
    }
    
    free(full_path);
}
