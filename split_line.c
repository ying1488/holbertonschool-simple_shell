#include "shell.h"

char **split_line(char *line)
{
    int bufsize = 64;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;
    int position = 0;

    if (!tokens)
    {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\n");
    while (token != NULL)
    {
        tokens[position++] = token;
        if (position >= bufsize)
        {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                perror("Error reallocating memory");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, " \t\n");
    }
    tokens[position] = NULL;
    return tokens;
}
