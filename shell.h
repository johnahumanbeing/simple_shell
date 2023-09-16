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
char *env_get(char *name);
int exit_handler(char *buff, char **list_cmd, char **cmd);
int check_exit(char *buff);
int *code_exiter();
void code_exit_set(int code);
int *hist_count();
void line_cnt_updt(void);
void var_rep(char **cmd);
int line_rd(const int fd, char **line);
int	line_rd_f(char **str, char **line, int fd);
int _help(char **commands);
void free_hist(void);
void hist_handler(char *buff);
int _hist(void);
list_t **last_cmd_addr();
list_t **get_hist_addr();
void *_realloc(void *ptr, unsigned int old_sz, unsigned int new_sz);
void write_hist(void);
int _alias(char **commands);
int _cd(char *path);
int _unsetenv(char *name);
int _setenv(char *name, char *value);
void env(void);

#endif
