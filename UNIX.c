#include "shell.h"

#define BUFFER_SIZE 1024

void exec_command(char *command);
void handle_input(char *buffer);

/**
 * main - the entry point
 * Return: zero
 */

int main(void)
{
	char *buffer;
	size_t bufsize = BUFFER_SIZE;
	int chars;

	buffer = (char *)malloc(bufsize * sizeof(char));

	if (buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}

	while (1)
	{
		printf("$");

		chars = getline(&buffer, &bufsize, stdin);

		if (chars == -1)
		{
			printf("\n");
			break;
		}

		buffer[chars - 1] = '\0';
		handle_input(buffer);
	}

	free(buffer);
	return (0);
}
