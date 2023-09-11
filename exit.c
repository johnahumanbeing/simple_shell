#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_ARGS 64
#define MAX_PATH 1024

/**
 * get_path - gets the path of the command
 * @cmd: the command
 * Return: zero
 */
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

/**
 * exec_command - forks and executes a command
 * @cmd_path: the path of the command
 * @args: the arguments
 * Return: zero
 */
int exec_command(char *cmd_path, char *args[])
{
	int status;
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
	return (0);
}

/**
 * parse_line - function that parses the user input
 *  into commands and arguments
 *  @line: the input line
 *  @args: the arguments
 *  Return: number of arguments
 */
int parse_line(char *line, char *args[])
{
	int num_args = 0;
	char *arg = strtok(line, " \n");

	while (arg != NULL && num_args < MAX_ARGS - 1)
	{
		args[num_args++] arg;
		arg = strtok(NULL, " \n");
	}

	args[num_args] = NULL;
	return (num_args);
}

/**
 * main - the entry point
 * Return: zero
 */
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

		int num_args = parse_line(line, args);

		if (num_args == 0)
		{
			continue;
		}

		char *cmd = args[0];
		char *cmd_path = get_path(cmd);

		if (cmd_path == NULL)
		{
			printf("%s: command not found\n", cmd);
			continue;
		}

		exec_command(cmd_path, args);
		free(cmd_path);
	}
	free(line);
	return (0);
}
