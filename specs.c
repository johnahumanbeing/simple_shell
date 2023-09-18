#include "shell.h"

/**
 * build_dynamic_environ - Builds the "env vars" array using dynamic memory
*/
void build_dynamic_environ(void)
{
	int count_envs = 0;
	char **new_environ;

	while (__environ[count_envs] != NULL)
		count_envs++;

	new_environ = allc_memry(sizeof(char *) * (count_envs + 1));
	for (count_envs = 0;  __environ[count_envs] != NULL; count_envs++)
		new_environ[count_envs] = str_dup(__environ[count_envs]);

	new_environ[count_envs] = NULL;

	__environ = new_environ;
}

/**
 * free_dynamic_environ - Frees the memory allocated to hold "env vars"
 */
void free_dynamic_environ(void)
{
	free_dbl_ptr(__environ);
}
