#include "shell.h"

/**
 * env_name_verify - Validates a env var name
 * @name: String to be validated
 *
 * Return: 0, on success, -1 on error
*/
int env_name_verify(char *name)
{
	if (name == NULL)
	{
		print_builtin_error("setenv: Needs 2 args", "");
		return (-1);
	}

	if (!var_name_is_valid(name))
	{
		print_builtin_error("setenv: Invalid name ", name);
		return (-1);
	}

	return (0);
}

/**
 * var_name_is_valid - Checks if the env name is valid
 * @name: String to be checked
 *
 * Return: 1 if is valid, 0 otherwise
*/
int var_name_is_valid(char *name)
{
	int i;
	for (i = 0; name[i] != '\0'; i++)
		if (name[i] == '=')
			return (0);

	return (1);
}

/**
 *get_env_postn - Check if a env variable exists and returns the index
 * @name: Name to be searched
 *
 * Return: Index of the env var, -1 on error
*/
int get_env_postn(char *name)
{
	int i;
	int len = strlen(name);

	for (i = 0; __environ[i] != NULL; i++)
		if (strncmp(__environ[i], name, len) == 0)
			return (i);

	return (-1);
}
