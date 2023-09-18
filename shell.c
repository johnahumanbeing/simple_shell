#include "shell.h"

static char *MAIN_ARG;

/**
 * main - entry point
 * @ac: argument count
 * @av: argument vector
 * Return: 0 for success
*/

int main(int ac, char **av)
{
	int rd, execute_file = 0;
	char *buff = NULL;
	size_t buff_l = 0;
	int fd;

	MAIN_ARG = av[0];

	signal(SIGINT, sigintHandler);
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
		buff = comment_handler(buff);
		strtok(buff, "\n");
		opp_handler(buff, rd, av[0]);
	}

	free(buff);

	if (execute_file)
	{
		close(fd);
	}
	return (*code_exiter());

}

/**
 * handle_args - check the number of arguments passed
 * @ac: argument count
 * @av: argument vector
 * @execute_file: int to check if user wants to run command from file
 * Return: file descriptor
*/

int handle_args(int ac, char **av, int *execute_file)
{
	int fd = STDIN_FILENO;
	char *msg_err = "Error: more than one argument\n";

	if (ac > 2)
	{
		write(STDERR_FILENO, msg_err, strlen(msg_err));
		exit(1);
	}

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		*execute_file = 1;
	}

	if (fd == -1)
	{
		perror(av[-0]);
		exit(1);
	}
	return (fd);
}

/**
 * singintHandle - Avoids current process to finish
 * @sig_num: Signal num
 * @sigintHandler: handles the signals
 * Return: is void
*/

void sigintHandler(int __attribute__((unused))sig_num)
{
	write(STDIN_FILENO, "\n$ ", 3);
}

/**
 * get_av_1- Returns the first argument passed to main
 *
 * Return: Pointer to first argument passed to main
*/
char *get_av_1(void)
{
	return (MAIN_ARG);
}
