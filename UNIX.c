#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

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

		if (access(buffer, F_OK) == 0)
		{
			pid_t pid = fork();

			if (pid == 0)
			{
				char *args[] = {buffer, NULL};

				execve(args[0], args, NULL);
			}
			else
			{
				wait(NULL);
			}
		}
		else
		{
			printf(":
					command not found\n", buffer);
		}
	}

	free(buffer);
	return (0);
}
