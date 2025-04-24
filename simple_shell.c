#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

/**
 * main - Entry point of the simple shell program
 *
 * Return: Always 0 (Success)
 */

int main(void)
{
    char input[MAX_INPUT_SIZE];
    char *command;
    pid_t pid;

    while (1)
    {
        printf("#cisfun$ "); /*Display prompt*/
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("\n");
            break; /*Handle Ctrl+D (EOF)*/
        }

        /* Remove the trailing newline character from input*/
        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0)
            continue; /*Ignore empty input*/

        command = input; /*Command is a single word*/

        pid = fork(); /*Create a child process*/
        if (pid == -1)
        {
            perror("Error: fork failed");
            continue;
        }

        if (pid == 0)
        {
            /*Child process*/
            if (execlp(command, command, NULL) == -1)
            {
                perror("./shell"); /*Handle invalid executable*/
	    }
            exit(EXIT_FAILURE);
        }
        else
        {
            /*Parent process waits for the child to finish*/
            wait(NULL);
        }
    }

    return 0;
}
