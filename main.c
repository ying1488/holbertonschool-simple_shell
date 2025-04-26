#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"
/**
 *
 */
char *trim_whitespace(char *str) 
{
    char *end;

    while (*str == ' ') str++;
    if (*str == 0) return str;
    end = str + strlen(str) - 1;
    while (end > str && *end == ' ') end--;
    *(end + 1) = '\0';
    return str;
}
/**
 *
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *command;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "#cisfun$ ", 9);

        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            free(line);
            exit(EXIT_SUCCESS);
        }
        command = strtok(line, "\n");
        while (command)
        {
            command = trim_whitespace(command);
            if (*command != '\0')
            {
                char **args = split_line(command);
                if (args[0] != NULL)
                {
                    execute_command(args);
                }
                free(args);
            }
            command = strtok(NULL, "\n");
        }
    }

    free(line);
    return 0;
}
