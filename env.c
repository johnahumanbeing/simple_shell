#include "shell.h"

/**
 * env_get - Returns a pointer to the env
 * @name: name of environment variable
 *
 * Return: Pointer to environment variable
*/
char *env_get(char *name)
{
	int i;

	for (i = 0; __environ[i] != NULL; i++)
		if (strncmp(__environ[i], name, strlen(name)) == 0)
			return (&__environ[i][strlen(name) + 1]);

	return (NULL);
}
