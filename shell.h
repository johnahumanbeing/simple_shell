#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for Holberton project
 */
typedef struct list_s
{
	char *str;
	unsigned int len;
	struct list_s *next;
} list_t;

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
int _puts(char *str);
int get_env_postn(char *name);
int var_name_is_valid(char *name);
int env_name_verify(char *name);
char *path_finder(char *dir, char *filename);
int PATH_Handler(char **commands);
int args_counter(char *str_input, char *delimiter);
char **input_parser(char *str_input, char *delimiter);
void print_builtin_error(char *msg, char *arg);
void dispatch_error(char *msg);
int other_set_inbuilts(char **commands);
int inbuilt_envar(char **commands);
int inbuilt_handler(char **commands);
char *comment_handler(char *str_input);

#endif
