#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "env.h"

#define MAX_ARGS 64
#define MAX_PATH 1024

char *get_path(char *cmd);
void print_env(void);
void exec_command(char *cmd_path, char *args[]);

/**
 * main - the entry point
 * Return: nothing
 */
int main(void)
{
	char *line = NULL;
	size_t line_size = 0;
	char *args[MAX_ARGS];

	int num_args;
	char *cmd;
	char *cmd_path;
	char *arg;

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		if (getline(&line, &line_size, stdin) == -1)
		{
			break;
		}

		num_args = 0;
		arg = strtok(line, " \n");

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

		cmd = args[0];

		if (strcmp(cmd, "exit") == 0)
		{
			print_env();
			continue;
		}

		cmd_path = get_path(cmd);

		if (cmd_path == NULL)
		{
			printf("%s: command not found\n", cmd);
			continue;
		}

		exec_command(cmd_path, args);
	}

	free(line);
	return (0);
}

/**
 * get_path - function that gets the full path of a command
 * @cmd: the command
 * Return: null
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
 * print_env - function that prints the environment variables
 */
void print_env(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}

/**
 * exec_command - function that execues a command
 * @cmd_path: the path of the command
 * @args: the arguments
 */
void exec_command(char *cmd_path, char *args[])
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
	free(cmd_path);
}
