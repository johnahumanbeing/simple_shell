#include "shell.h"

/**
 * prompt_read - prompt the user and read their command
 * @prompt: prompt to display to the user
 * @comnd: A buffer to store the user's command
 * @max_length: maximum length of the command buffer
 * Return: no of charecters read, or -1 on error
*/

int prompt_read(const char *prompt, char *comnd, size_t max_length)
{
	size_t len;

	printf("%s", prompt);

	if (fgets(comnd, max_length, stdin) == NULL)
	{
		perror("fgets");
		return (-1);
	}

	len = strlen(comnd);

	if (len > 0 && comnd[len - 1] == '\n')
	{
		comnd[len - 1] = '\0';
		len--;
	}

	return (len);
}

/**
 * terminator - closes the shell
 * Return: is void
*/

void terminator(void)
{
	exit(EXIT_SUCCESS);
}

/**
 * parser - splits a command into arguments
 * @command: command given
 * @
 * @
 * Return:
*/

void parse_command(const char *command, char **args, size_t max_args)
{
	size_t arg_count = 0;
	char * token;

	token = strtok((char*)command, " \t\n");

	while (token != NULL && arg_count <max_args - 1)
	{
		args[arg_count++] = token;
		token = strtok(NULL, " \t\n");
	}

	args[arg_count] = NULL;
}
