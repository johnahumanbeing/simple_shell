#include "shell.h"

/**
 * env - Prints the environment variables to STDOUT
*/

void env(void)
{
	int i;
	char **env = __environ;

	for (i = 0; env[i]; i++)
	{
		write(STDOUT_FILENO, env[i], strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
	}

	code_exit_set(0);
}

/**
 * _setenv - Sets or adds an environment variable
 * @name: Name for the new env variable
 * @value: Value for the new env variable
 *
 * Return: 1 on success, -1 on error
 */
int _setenv(char *name, char *value)
{
	int env_index, new_var_len;

	if (env_name_verify(name) == -1)
		return (-1);

	env_index = env_get_postn(name);
	if (env_index == -1)
	{
		int env_count = 0;
		int old_sz, new_sz;

		while (__environ[env_count] != NULL)
			env_count++;

		old_sz = sizeof(char *) * (env_count);
		new_sz = sizeof(char *) * (env_count + 2);
		__environ = _realloc(__environ, old_sz, new_sz);
		if (__environ == NULL)
			dispatch_error("Error while _reallocating memory for new env var");

		env_index = env_count;
		__environ[env_count + 1] = NULL;
	}
	else
	{
		free(__environ[env_index]);
	}

	new_var_len = strlen(name) + strlen(value) + 2;
	__environ[env_index] = alloc_memry(sizeof(char) * new_var_len);
	strcpy(__environ[env_index], name);
	strcat(__environ[env_index], "=");
	strcat(__environ[env_index], value);

	code_exit_set(0);
	return (1);
}

/**
 * _unsetenv - Removes an evironment variable
 * @name: Name for the new env variable
 *
 * Return: 1 on success, -1 on error
 */
int _unsetenv(char *name)
{
	int env_index, i;

	env_index = get_env_postn(name);
	if (env_index >= 0)
	{
		free(__environ[env_index]);

		for (i = env_index; __environ[i] != NULL; i++)
			__environ[i] = __environ[i + 1];

		code_exit_set(0);
		return (1);
	}

	code_exit_set(0);

	return (1);
}

/**
 * _cd - Changes the current directory of the process
 * @path: Path to wich change the working directory
 *
 * Return: 1 on success, -1 on error
*/
int _cd(char *path)
{
	char buff[1024];
	char *oldpwd;
	char *_path = path;

	if (strcmp(path, "-") == 0)
		path = env_get("OLDPWD");

	if (path == NULL)
	{
		print_builtin_error("cd: OLDPWD not set", "");
		return (-1);
	}
	path = duplicate_string(path);

	oldpwd = getcwd(buff, 1024);
	if (oldpwd == NULL)
	{
		free(path);
		print_builtin_error("cd: couldn't get current dir", "");
		return (-1);
	}

	if (chdir(path) == -1)
	{
		free(path);
		print_builtin_error("cd: can't change cd to ", _path);
		code_exit_set(1);
		return (-1);
	}
	_setenv("OLDPWD", oldpwd);
	_setenv("PWD", path);
	free(path);
	code_exit_set(0);
	return (1);
}

/**
 * _alias - Sets an alias command
 * @commands: List of commands
 *
 * Return: -1 on error, 0 otherwise
*/
int _alias(char **commands)
{
	int status = 0;
	list_t *curr;
	list_t *out_head = NULL;
	list_t **alias_addrs = get_alias_head();

	/* the alias args starts from position 1 */
	if (commands[1] == NULL)
	{ /* This means to list all the aliases */
		for (curr = *alias_addrs; curr != NULL; curr = curr->next)
		{
			_puts(curr->str);
			_puts("\n");
		}
		code_exit_set(0);
		return (1);
	}

	status = handle_alias_args(commands, &out_head);

	for (curr = out_head; curr != NULL; curr = curr->next)
	{
		_puts(curr->str);
		_puts("\n");
	}
	free_list(out_head);
	return (status);
}
