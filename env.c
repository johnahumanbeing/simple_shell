#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_ARGS 64
#define MAX_PATH 1024

extern char **environ;

char *get_path(char *cmd)
{
	char *path = getenv("PATH");
	char *dir = strtok(path, ":");
	char *full_path = malloc(MAX_PATH);

	while (dir != NULL)
	{
		snprintf(full_path, MAX_PATH, "%s/%s", dir, cmd);

		if (access(full_path, X_OK) == 0)
		{
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}
	free(full_path);
	return (NULL);
}

print_env() void
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}

int main(void)
{
	char *line = NULL;
	size_t line_size = 0;
	char *args[MAX_ARGS];
	int status;

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		if (getline(&line, &line_size, stdin) == -1)
		{
			break;
		}

		int num_args = 0;
		char *arg = strtok(line, " \n");

		while (arg != NULL && num_args < MAX_ARGS - 1)
		{
			args[num_args++] = arg;
			arg = strtok(NULL, " \n");
		}
		args[num_args] = NULL;

		if (num_args == 0)
		{
			continue;
		}

		char *cmd = args[0];

		if (strcmp(cmd, "exit") == 0)
		{
			print_env();
			continue;
		}

		char *cmd_path = get_path(cmd);

		if (cmd_path == NULL)
		{
			printf("%s: command not found\n", cmd);
			continue;
		}

		pid_t pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			execv(cmd_path, args);
			perror("execv");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
		}
		free(cmd_path);
	}

	free(line);
	return (0);
}
