#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

int _unsetenv(const char *name)
{
	int i, j;
	size_t len;

	if (name == NULL || *name == '\0' || strchr(name, '=') != NULL)
		return -1;
	len = strlen(name);
	for (i =0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len]=='=')
		{
			for (j = i; environ[j] != NULL; j++)
            {
                environ[j] = environ[j + 1];
            }
            return 0;
		}
	}
	return 0;
}
int main(void)
{
    printf("Before unset:\n");
    printf("HOME = %s\n", getenv("HOME"));

    _unsetenv("HOME");

    printf("After unset:\n");
    printf("HOME = %s\n", getenv("HOME")); // Should print (null) or empty

    return 0;
}
