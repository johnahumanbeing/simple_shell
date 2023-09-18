#include "shell.h"

/**
 * dispatch_error - Dispatches an error
 * @msg: Message to print as error
*/
void dispatch_error(char *msg)
{
	perror(msg);
	exit(errno);
}

/**
 * print_builtin_error - Prints error for builtin function
 * @msg: Error message
 * @arg: Argument passed to builtin function
*/
void print_builtin_error(char *msg, char *arg)
{
	int len = strlen(msg);
	char *first_av = get_av_1();

	write(STDERR_FILENO, first_av, strlen(first_av));
	write(STDERR_FILENO, ": 1: ", 5);
	write(STDERR_FILENO, msg, len);
	write(STDERR_FILENO, arg, strlen(arg));
	write(STDERR_FILENO, "\n", 1);
	code_exit_set(2);
}
