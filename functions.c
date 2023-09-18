#include "shell.h"

static char *MAIN_ARG;

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

void singintHandler(int __attribute__((unused))sig_num)
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
