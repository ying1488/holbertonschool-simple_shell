#include <stdio.h>

extern char **environ;

int main (int argc, char **argv, char **env_from_main)
{
	(void) argc;
	(void) argv;

	printf("Address of env: %p\n", (void *)env_from_main);
	printf("Address of environ: %p\n", (void *)environ);

	return (0);

}
