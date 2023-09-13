#ifndef _SHELL_H_
#define _SHELL_H_

#define MAX_ARGS 64
#define MAX_PATH 1024
#define BUFFER_SIZE 1024

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

void _printer(const char *characters);

void prompt_usr(void);

void execute_prompt(const char *comnd);

char *get_path(char *cmd);

void exec_command(char *cmd, char *cmd_path, char *args[]);

void exec_command(char *command);

void handle_input(char *buffer);

void print_env(void);

int exec_command(char *cmd_path, char *args[]);

#endif
