#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

/**
 * main - the entry point
 * Return: nothing
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
		printf("$ ");
		chars = getline(&buffer, &bufsize, stdin);

		if (chars == -1)
		{
			printf("\n");
			break;
		}

		buffer[chars - 1] = '\0';
		char *token = strtok(buffer, " ");

		while (token != NULL)
		{
			printf("%s\n", token);
			token = strtok(NULL, " ");
		}
	}

	free(buffer);
	return (0);
}
