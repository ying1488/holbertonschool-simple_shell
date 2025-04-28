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

/**
 * _strlen - Computes the length of a string
 * @s: Pointer to the string
 *
 * Return: Length of the string (number of characters before null terminator)
 */

int _strlen(const char *s)
{
	int len = 0;

	while (s && s[len])
		len++;
	return (len);
}

/**
 * _strchr - Locates the first occurrence of a character in a string
 * @s: Pointer to the string to search
 * @c: Character to locate
 *
 * Return: Pointer to the first occurrence of character c in string s,
 * or NULL if not found
 */

char *_strchr(const char *s, char c)
{
	while (s && *s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

/**
 * _strdup - Duplicates a string
 * @s: Pointer to the string to duplicate
 *
 * Return: Pointer to the newly allocated duplicated string,
 * or NULL if memory allocation fails
 */

char *_strdup(const char *s)
{
	char *copy;
	int len = _strlen(s);
	int i;

	copy = malloc(len + 1);
	if (!copy)
		return (NULL);
	for (i = 0; i < len; i++)
		copy[i] = s[i];
	copy[i] = '\0';
	return (copy);
}

/**
 * _strcmp - Compares two strings
 * @s1: First string
 * @s2: Second string
 *
 * Return: An integer less than, equal to, or greater than 0 depending on
 * whether s1 is found to be less than, to match, or be greater than s2
 */

int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
