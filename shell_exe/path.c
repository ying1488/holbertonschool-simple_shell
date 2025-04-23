#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_PATH 1024

int main(int ac, char **av)
{
	char *path_env, *path_copy, *dir;
	char full_path[1024];
	struct stat st;
	int i;

	if (ac < 2)
    {
        printf("Usage: %s filename ...\n", av[0]);
        return (1);
}
	path_env = getenv("PATH");
	if (!path_env)
	{
		perror("getenv");
		return (1);
	}
	path_copy = strdup(path_env);
	if (!path_copy)
	{
		perror("strdup");
		return (1);
	}
	for (i =1; av[i]; i++)
	{
		int found = 0;
		dir = strtok(path_copy, ":");
		while(dir)
		{
			snprintf(full_path, sizeof(full_path), "%s/%s", dir, av[i]);
			if (stat(full_path, &st) == 0)
			{
				printf("%s: %s\n", av[i], full_path);
                found = 1;
                break;
			}
			dir = strtok(NULL, ":");
		}
		if (!found)
			printf("%s: not found\n", av[i]);
		strcpy(path_copy, path_env);
	}
	free(path_copy);
	return (0);
}
