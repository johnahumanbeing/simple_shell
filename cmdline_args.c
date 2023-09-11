#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
/**
 * hii hapa ndioo number 2 hio shell 0.1+
 * hii utamake sum adjustments na umake comments
 * pia prototypes uta add kwa shell.h
 * sijui kama kuna anything else
 */

int main(void)
{
	char *buffer;
	size_t bufsize = BUFFER_SIZE;
	int chars;

	buffer = (char *)mallloc(bufsize * sizeof(char));

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
