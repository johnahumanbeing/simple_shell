#include "shell.h"

/**
 * exit_handler - Checks if user entered the exit command
 * @buff: input
 * @list_cmd: list of commands
 * @cmd: input parsed as array of commands
 *
 * Return: 0 if the commad is NOT exit, -1 if the exit status was Illegal
*/
int exit_handler(char *buff, char **list_cmd, char **cmd)
{
	int status;

	if (cmd[0] == NULL || strcmp(cmd[0], "exit") != 0)
		return (0);

	if (cmd[1] == NULL)
	{
		write_hist();
	    allc_free(buff, list_cmd, cmd, FL_BUFF | FL_CMDS);
		if (*code_exiter() == 127)
			exit(2);
		exit(0);
	}

	status = check_exit(cmd[1]);

	if (status >= 0)
	{
		write_hist();
		allc_free(buff, list_cmd, cmd, FL_BUFF | FL_CMDS);
		exit(status);
	}

	print_builtin_error("exit: Illegal number: ", cmd[1]);
	return (-1);
}

/**
 * check_exit - Calculates the exit status
 * @buff: input
 *
 * Return: Exist status as number, -1 on error
*/
int check_exit(char *buff)
{
	int i;
	int status = 0;

	for (i = 0; buff[i] != '\0'; i++)
	{
		if (buff[i] == '\n')
			return (status);

		if (buff[i] < '0' || buff[i] > '9')
			return (-1);

		status *= 10;
		status += buff[i] - '0';
	}

	return (status);
}
