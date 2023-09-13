#include "shell.h"

/**
 * main - entry point
 * Return: 0 for success
*/

int main(void)
{
	int i;
	char command[MAX_COMMAND_LENGTH];
	char *args[MAX_COMMAND_LENGTH];

	while (1)
	{
		int length = prompt_read("$", command, sizeof(command));

		if (length == -1)
		{
			terminator();
		}

		if (strcmp(command, "exit") == 0)
		{
			terminator();
		}

	parse_command(command, args,sizeof(args) / sizeof(args[0]));

	if (args[0] != NULL)
	{
		for (i = 0; args[i] != NULL; i++)
		{
			printf("Argument %d: %s\n", i, args[i]);
		}
		
	}
	
	}
	return (0);
}
