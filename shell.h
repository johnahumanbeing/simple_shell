#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024

int prompt_read(const char *prompt, char *command, size_t max_length);
void terminator(void);
void parse_command(const char *command, char **args, size_t max_args);
void executer(char **args);

#endif
