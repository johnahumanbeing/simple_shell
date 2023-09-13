#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_ARGS 64
#define MAX_PATH 1024

char *get_path(char *cmd);
void exec_command(char *cmd, char *cmd_path, char *args[]);

/**
 * main - the entry point
 * Return: zero
 */
int main(void)
{
    char *line = NULL;
    size_t line_size = 0;
    char *args[MAX_ARGS];
    int num_args;
    char *arg;
    char *cmd;

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
        char *cmd_path = get_path(cmd);

        if (cmd_path == NULL)
        {
            printf("%s: command not found\n", cmd);
            continue;
        }

        exec_command(cmd, cmd_path, args);
        free(cmd_path);
    }

    free(line);
    return (0);
}

/**
 * get_path - function that finds the full path of a command
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
 * exec_command - function that executes a command
 * @cmd: the command
 * @cmd_path: the path of the command
 * @args: the arguments
 */
void exec_command(char *cmd, char *cmd_path, char *args[])
{
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
        int status;
        wait(&status);
    }
}
