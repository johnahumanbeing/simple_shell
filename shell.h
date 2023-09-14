#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int handle_args(int ac, char **av, int *execute_file);
void singintHandler(int __attribute__((unused))sig_num);
char *get_av_1(void);
int exit_handler(char *buff, char **list_cmd, char **cmd);
int check_exit(char *buff);
int *code_exiter();
void code_exit_set(int code);
int *hist_count();
void line_cnt_updt(void);


#endif
