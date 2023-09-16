#include "shell.h"

/**
 * enter_handler - Check if no command was entered
 * @commands: String of commnands
 *
 * Return: 1 if no command was entered(just spaces and ENTER), 0 otherwise
*/
int enter_hander(char **commands)
{
	if (commands[0] == NULL || strcmp(commands[0], "\n") == 0)
		return (1);

	return (0);
}
