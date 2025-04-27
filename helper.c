#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * free_args - Free an array of arguments
 * @args: Null-terminated array of strings
 */
void free_args(char **args)
{
    int i;

    if (!args)
        return;

    for (i = 0; args[i]; i++)
        free(args[i]);
    free(args);
}

/* _strlen */
int _strlen(const char *s)
{
    int len = 0;
    while (s && s[len])
        len++;
    return len;
}

/* _strchr */
char *_strchr(const char *s, char c)
{
    while (s && *s)
    {
        if (*s == c)
            return ((char *)s);
        s++;
    }
    return NULL;
}

/* _strdup */
char *_strdup(const char *s)
{
    char *copy;
    int len = _strlen(s);
    int i;

    copy = malloc(len + 1);
    if (!copy)
        return NULL;
    for (i = 0; i < len; i++)
        copy[i] = s[i];
    copy[i] = '\0';
    return copy;
}


int _strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
