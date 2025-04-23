#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int _setenv(const char *name, const char *value, int overwrite)
{
	char *env_string;
	size_t name_len, value_len;
	char *existing_value;

	/*input validation*/
	if (name == NULL || value == NULL || strchr(name, '=') !=NULL)
	{
		return (-1);
	}
	/*Check for existing Variable & overwite logic*/
	existing_value = getenv(name);
	if (existing_value && !overwrite)
	{
		return (0);
	}
	/*prerp "NAME = VALUE" string*/
	name_len = strlen(name);
	value_len = strlen(value);
	env_string = malloc(name_len + value_len + 2);
	if(env_string == NULL)
		return(-1); /*Malloc failed*/
	sprintf(env_string, "%s=%s", name, value); /*format the string*/

	/*Call putenv: putenv takes a string pointer (env_string) of the form "NAME=VALUE". 
	 * It adds this specific string pointer to the environment.*/
	if (putenv(env_string) != 0 )
	{
		free(env_string); /*Free memory ONLY if putenv fails*/
		return(-1); /*putenv failed*/
	}
	return (0);
}

int main(void)
{
	_setenv("INDIGO_VAR", "c_is_fun", 1);
	printf("INDOGO_VAR = %s\n", getenv("INDIGO_VAR"));

	_setenv("INDIGO_VAR", "overwrite_test", 0);
	printf("INDIGO_VAR (no overwrite) = %s\n", getenv("INDIGO_VAR"));

	_setenv("INDIGO_VAR", "overwrite_test", 1);
	 printf("INDIGO_VAR (no overwrite) = %s\n", getenv("INDIGO_VAR"));
}
