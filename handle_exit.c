#include "shell.h"

/**
 * _atoi - Converts a string to an integer
 * @s: String to convert
 * Return: The integer, or -1 on error
 */
int _atoi(const char *s)
{
    int i = 0, result = 0;

    if (!s)
        return -1;

    while (s[i])
    {
        if (s[i] < '0' || s[i] > '9')
            return -1; /* Not a valid number */
        result = result * 10 + (s[i] - '0');
        i++;
    }

    return result;
}

/**
 * handle_exit - Handles the "exit" built-in command
 * @args: Command arguments
 */
void handle_exit(char **args)
{
    int exit_status = 0;

    if (args[1]) /* If there is an argument */
    {
        exit_status = _atoi(args[1]);
        if (exit_status == -1)
        {
            write(STDERR_FILENO, "./hsh: 1: exit: Illegal number: ", 31);
            write(STDERR_FILENO, args[1], _strlen(args[1]));
            write(STDERR_FILENO, "\n", 1);
            return;
        }
    }

    free_args(args);
    exit(exit_status);
}
