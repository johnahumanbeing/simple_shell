#include "shell.h"

static char *MAIN_ARG;

/**
 * main - entry point
 * @ac: argument count
 * @av: argument vector
 * Return: 0 for success
*/

int main(int ac, char *av)
{
	int rd, execute_file = 0;
	char *buff = NULL;
	size_t buff_l = 0;
	int fd;

	MAIN_ARG = av[0];

	sign(SINGINT, singintHandle);
	fd = handle_args(ac, av, &execute_file);

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1 && execute_file == 0)
		{
			write(STDOUT_FILENO, "$ ", 2);
		}
		rd = getline(&buff, &buff_l, stdin);

		if (rd == EOF)
		{
			free(buff);
			exit(*code_exiter());
		}
		buff = cmnt_handle(buff);
		strtok_(buff, "\n");
		opp_handler(buff, rd, av[0]);
	}

	free(buff);

	if (execute_file)
	{
		close(fd);
	}
	return (*code_exiter());

}
