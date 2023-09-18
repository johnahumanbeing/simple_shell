#include "shell.h"

/**
 * enter_handler - Check if command was not entered
 * @commands: String of commnands
 *
 * Return: 1 if no command was entered(spaces and ENTER), 0 otherwise
*/
int enter_handler(char **commands)
{
	if (commands[0] == NULL || strcmp(commands[0], "\n") == 0)
		return (1);

	return (0);
}
