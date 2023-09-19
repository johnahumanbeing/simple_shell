#include "shell.h"

/**
 * opp_handler - Handle semicolon and logical op
 * @buff: first buffer that functions read
 * @read: return of read (open with getline)
 * @first_av: av[0]
 * Return: 0 on success
*/
void opp_handler(char *buff, int read, char *first_av)
{
	char **cmds_list = NULL;

	execute_commands(buff, cmds_list, buff, read, first_av);
}

/**
 * or_handler - Handle || logical part
 * @buff_semicolon: first buffer that functions read
 * @read: return of read (open with getline)
 * @first_av: av[0]
 * Return: 0 on success
*/
void or_handler(char *buff_semicolon, int read, char *first_av)
{
	int i, flag, prev_flag = -1;
	char **cmds_list_2 = input_parser(buff_semicolon, "||");

	for (i = 0; cmds_list_2[i] != NULL; i++)
	{
		flag = and_handler(cmds_list_2[i], read, first_av, prev_flag);
		prev_flag = flag;
	}
	free_dbl_ptr(cmds_list_2);
}

/**
 * and_handler - Handle && logical part and executes inside of it
 * @buff_or: first buffer that functions read
 * @read: return of read (open with getline)
 * @first_av: av[0]
 * @prev_flag: last flag of ||, it is important to print or not
 * Return: 0 on success
*/
int and_handler(char *buff_or, int read, char *first_av, int prev_flag)
{
	int j = 0, flag = 1;
	char **cmds_list_3 = input_parser(buff_or, "&&");

	if (prev_flag == 0)
	{
		j++;
		if (cmds_list_3[j] == NULL)
			return (-1);
	}

	for (; cmds_list_3[j] != NULL; j++)
	{
		flag = execute_commands(buff_or, cmds_list_3,
									cmds_list_3[j], read, first_av);
		prev_flag = flag;
	}
	free_dbl_ptr(cmds_list_3);
	return (flag);
}

/**
 * execute_commands - Fork and create commands, child process and executed
 * @buff: first buffer that function read
 * @cmds_list: List of commands
 * @cmd: Single command as a string
 * @read: return of read (open with getline)
 * @first_av: av[0]
 * Return: 0 on success
*/

int execute_commands(char *buff, char **cmds_list,
	char *cmd, int __attribute__((unused))read, char *first_av)
{
	char **commands;
	int child_pid, _err = 0, flag = 0, *status = code_exiter();

	commands = input_parser(cmd, " ");
	var_rep(commands);
	aliases_handler(commands);
	/* Exit error, ENTER, and builtins */
	if (exit_handler(buff, cmds_list, commands) == -1 ||
			enter_handler(commands) == 1	||
			inbuilt_handler(commands) == 1)
	{
		free_dbl_ptr(commands);
		return (-1);
	}

	child_pid = fork();/* Fork parent process to execute the command */
	if (child_pid == -1)
	{
		allc_free(buff, cmds_list, commands, FL_BUFF | F_CMD_L | FL_CMDS);
		dispatch_error(first_av);
	}
	else if (child_pid == 0)
	{
		_err = PATH_Handler(commands);
		execve(commands[0], commands, __environ);
		if (_err != 0)
			handle_cmnd_not_found(buff, cmds_list, commands, first_av);
		allc_free(buff, cmds_list, commands, FL_BUFF | F_CMD_L | FL_CMDS);
		dispatch_error(first_av);
	}
	wait(status);
	*status = WEXITSTATUS(*status);
	if (*status == 2)
		code_exit_set(127);
	free_dbl_ptr(commands);
	return (flag);
}

/**
 * handle_cmnd_not_found - Print a message to stderr
 * @buff: User's input
 * @cmds_list: Array of commands
 * @commands: Array of strings
 * @first_av: First argument passed to the executable
*/
void handle_cmnd_not_found(char *buff, char **cmds_list,
							char **commands, char *first_av)
{
	code_exit_set(127);
	write(2, first_av, strlen(first_av));
	write(2, ": 1: ", 5);
	write(2, commands[0], strlen(commands[0]));
	write(2, ": not found\n", 12);
	allc_free(buff, cmds_list, commands, FL_BUFF | F_CMD_L | FL_CMDS);
	exit(127);
}
