#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t my_pid;
	pid_t child_pid = 1;
	int i = 0;
	int status;
	char *argv[] = {"/bin/ls","-l","tmp/", NULL};

	my_pid = getpid();

	while (i <= 4 && (child_pid !=0))
	{
		child_pid = fork();
		if(child_pid == -1)
		{
			printf("error");
			return (1);
		}
		wait(&status);
		i ++;
	}
	if (child_pid == 0)
	{
		printf("PID : %u\n\nID PPID: %u\n\n", getpid(), getppid());
	}
	else
	{
		printf("%u PPID: %u\n", my_pid, child_pid);
	}
	if (execve(argv[0], argv, NULL) == -1)
	{
		printf("error");
	}
	return (0);
}
