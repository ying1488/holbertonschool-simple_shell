#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main (int ac, char **av[])
{
	Starting by validating input, 
	then retrieving and duplicating PATH to avoid modifying the original string (strcpy alters the original so you need to strdup) during tokenization. 
	You split PATH by colons, build a full path for each directory and filename using sprintf, and 
	check for the files existence with stat (like the exmaple above this q). 
	If found,  print the location i
	if not, it notifies the user. 
	Then free.
	
	/*Get the Path Variable*/
	char *path , *path_copy, *dir;
	char full_path[1024];
	struct stat st;
	int i ;

	if (argc < 2)
	{
		printf("Usage: %s filename ...\n", argv[0]);
		return (1);
	}


	path_env = get_env("PATH");
	/* error for path not found */
	if (!path_copy)
	{
		perror("getenv");
		return (1);
	}
	/* copy PATH because strok modifies string */
	path_copy = strdup(path_env);
	if (!path_copy)
	{
		perror("strdup");
		return (1);
	}

	/*loop through the filenames,*/
	for (i = 1; av[i]; i++)
	{
		int found = 0;
		/*Iterating through PATH directories*/
		/* Split PATH by ':' */
		dir = strtok(path_copy, ":");
		/*Loop as long as strtok finds more directories*/
		while (dir)
		{
			/*Construct full PATH*/
			snprint(full_path, sizeof(full_path), "%s/%s", dir, av[i]);
			/*check if file exists, stat tries to get file status information */
			if (stat(full_path, &st) == 0)
			{
				/*File found*/
				printf("%s: %s\n", av[i], full_path);
				found = 1;
				break;
			}
			/*Get next dir, NULL (cont tokenizing same string)*/
			dir = strtok(NULL, ":");
		}

		if (!found)
		{
			printf("%s :not found\n", av[i]);
			/*Reset path_copy for next filename*/
			strcpy(path_copy, path_env);
		}
		/*Cleanup*/
		free (path_copy);
		return (0);

	}

}
