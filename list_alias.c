#include "shell.h"

static int head_alias_init = 1;
static list_t *alias_head;

/**
 * head_alias_get - Returns alias_head pointer
 *
 * Return: Pointer to alias head var
*/
list_t **head_alias_get()
{
	if (head_alias_init == 1)
	{
		alias_head = NULL;
		head_alias_init = 0;
	}
	return (&alias_head);
}

/**
 * alias_set - Checks if the alias input is meant to set an alias
 * @alias_pair: String as alias arg input
 *
 * Return: 1 for true, 0 otherwise
*/
int alias_set(char *alias_pair)
{
	int i;

	for (i = 1; alias_pair[i] != '\0'; i++)
		if (alias_pair[i] == '=')
			return (1);

	return (0);
}

/**
 * st_alias - adds or updates aliases
 * @alias_pair: String in the form name=value
*/
void st_alias(char *alias_pair)
{
	char tmp_buff[250];
	int first_eq, last_eq;
	list_t *curr;
	list_t **alias_addrs = head_alias_get();

	for (first_eq = 1; alias_pair[first_eq] != '\0'; first_eq++)
		if (alias_pair[first_eq] == '=')
			break;

	strncpy(tmp_buff, alias_pair, first_eq);
	tmp_buff[first_eq] = '\0';
	strcat(tmp_buff, "='");

	for (last_eq = first_eq; alias_pair[last_eq] != '\0'; last_eq++)
		if (alias_pair[last_eq] != '=')
			break;

	strcat(tmp_buff, &alias_pair[last_eq]);
	strcat(tmp_buff, "'");

	for (curr = *alias_addrs; curr != NULL; curr = curr->next)
		if (strncmp(curr->str, alias_pair, first_eq) == 0 &&
				(curr->str)[first_eq] == '=')
		{
			free(curr->str);
			curr->str = str_dup(tmp_buff);
			return;
		}

	end_node_add(alias_addrs, tmp_buff);
}

/**
 * args_alias_handle - Evaluates alias input command and decides what to do
 * @commands: Arrays of commands
 * @out_addrs: Pointer to out's head node
 *
 * Return: -1 if error happens, 0 otherwise
*/
int args_alias_handle(char **commands, list_t **out_addrs)
{
	int i, len, was_alias;
	int status = 0;
	list_t *curr;
	list_t **alias_addrs = head_alias_get();

	code_exit_set(0);
	for (i = 1; commands[i] != NULL; i++)
	{
		was_alias = 0;
		len = strlen(commands[i]);
		for (curr = *alias_addrs; curr != NULL; curr = curr->next)
		{
			if (strncmp(curr->str, commands[i], len) == 0 && (curr->str)[len] == '=')
			{ /* Means to list an alias */
				was_alias = 1;
				end_node_add(out_addrs, curr->str);
				break;
			}
		}
		if (was_alias)
			continue;
		if (alias_set(commands[i]))
			st_alias(commands[i]);
		else
		{
			status = -1;
			code_exit_set(1);
			_puts("alias: ");
			_puts(commands[i]);
			_puts(" not found\n");
		}
	}

	return (status);
}

/**
 * aliases_handler - Handle alias replacement
 * @commands: Arrays of commands
*/
void aliases_handler(char **commands)
{
	list_t *curr;
	list_t **alias_addrs = head_alias_get();
	int cmd_len = strlen(commands[0]);
	char *str;
	char tmp_buff[250];
	int i, alias_len = 0;

	if (commands[0] == NULL)
		return;

	for (i = 0; i < 250; i++)
		tmp_buff[i] = '\0';

	for (curr = *alias_addrs; curr != NULL; curr = curr->next)
	{
		str = curr->str;
		if (strncmp(commands[0], str, cmd_len) == 0 && str[cmd_len] == '=')
		{
			alias_len = strlen(&str[cmd_len + 2]);
			strncpy(tmp_buff, &str[cmd_len + 2], alias_len - 1);
			tmp_buff[alias_len] = '\0';
			free(commands[0]);
			commands[0] = duplicate_string(tmp_buff);
			break;
		}
	}
}
