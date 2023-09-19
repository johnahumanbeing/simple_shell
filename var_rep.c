#include "shell.h"

/**
 * var_rep - Handles '$'
 * @cmd: the commands
*/

void var_rep(char **cmd)
{
	int i;
	char *value_env;

	if (cmd[0] == NULL)
		return;

	for (i = 1; cmd[i] != NULL; i++)
	{
		if (cmd[i][0] != '$')
			continue;

		if (strcmp(&cmd[i][1], "?") == 0)
		{
			free(cmd[i]);
			cmd[i] = str_num(*code_exiter());
			return;
		}

		if (strcmp(&cmd[i][1], "$") == 0)
		{
			free(cmd[i]);
			cmd[i] = str_num(getpid());
			return;
		}

		value_env = env_get(&cmd[i][1]);
		if (value_env != NULL)
		{
			free(cmd[i]);
			cmd[i] = str_dup(value_env);
		}
	}
}
