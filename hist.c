#include "shell.h"

static int no_init_hist;
static list_t *hist_head;
static list_t *cmd_ls;

/**
 * get_hist_addr - Return the address oof history head
 * Return: Address of history head
*/
list_t **get_hist_addr()
{
	if (no_init_hist == 1)
	{
		hist_head = NULL;
		cmd_ls = NULL;
		no_init_hist = 0;
	}

	return (&hist_head);
}

/**
 * last_cmd_addr - Return the address oof history head
 *
 * Return: Address of last entered command
*/
list_t **last_cmd_addr()
{
	if (no_init_hist == 1)
	{
		hist_head = NULL;
		cmd_ls = NULL;
		no_init_hist = 0;
	}

	return (&cmd_ls);
}

/**
 * _hist - Prints the all the commands entered
 *
 * Return: 1 on success
*/
int _hist(void)
{
	list_t *curr_;
	char *num_str;
	int i, len;
	int count = *hist_count() % 4096;

	for (curr_ = *get_hist_addr(); curr_ != NULL; curr_ = curr_->next)
	{
		num_str = str_num(count++);
		len = _puts(num_str);
		for (i = len; i < 7; i++)
			_puts(" ");
		_puts(curr_->str);
		_puts("\n");
		free(num_str);
	}

	return (1);
}

/**
 * hist_handler - Adds a command to the history
 * @buff: User's input
*/
void hist_handler(char *buff)
{
	if (cmd_ls == NULL || buff[0] != ' ' || strcmp(cmd_ls->str, buff) != 0)
		cmd_ls = end_node_add(get_hist_addr(), buff);
}

/**
 * free_hist - Frees the memory used by history lists
*/
void free_hist(void)
{
	free_list(*get_hist_addr());
}
