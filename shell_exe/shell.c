#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
int main(void)
{
        char *line = NULL;
        size_t len = 0;
        ssize_t nread;
        pid_t pid;
        int status;

        while (1)
        {
                /*print the prompt*/
		printf("cisfun# ");
		/*read input*/
                nread = getline(&line, &len, stdin);
                /*Handle end of file or error */
		if (nread == -1)
                {
                        printf("\n");
                        break;
                }
		/*Remove trailing newline character*/
                line[strcspn(line, "\n")] = '\0';
		/*create a child process*/
                pid = fork();
		/*Handle fprk failure*/
                if (pid == -1)
                {
                        perror("Error: ");
                        return (1);
                }
		/*child process execution*/
                if (pid == 0)
                {
                        char *argv[] = {line, NULL};
                        execve(line, argv, NULL);
                        return (0);
                }
                /*Parent Process Execution*/
		else
                {
                        wait(&status);
                }
        }
	/*Cleanup before exiting*/
        free(line);
        return (0);
}
