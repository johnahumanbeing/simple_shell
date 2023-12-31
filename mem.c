#include "shell.h"

/**
 * allc_memry - Manages the allocation of memory
 * @bytes: Number representing the size in bytes to allocate
 *
 * Return: Pointer to the newly allocated memory
*/
void *allc_memry(unsigned int bytes)
{
	char *new_mem = malloc(bytes);

	if (new_mem == NULL)
		dispatch_error("Error while allocating memory\n");

	return (new_mem);
}

/**
 * str_dup - Duplicates a given string
 * @str: String to dulicate
 *
 * Return: Pointer to the address of the newly duplicated string
*/
char *str_dup(char *str)
{
	char *str_copy = strdup(str);

	if (str_copy == NULL)
		dispatch_error("Error while making copy of string");

	return (str_copy);
}

/**
 * free_dbl_ptr - Frees the memory pointed to by a double pointer
 * @dbl_ptr: Double pointer
*/
void free_dbl_ptr(char **dbl_ptr)
{
	int i;

	if (dbl_ptr == NULL)
		return;

	for (i = 0; dbl_ptr[i]; i++)
		free(dbl_ptr[i]);

	free(dbl_ptr);
}

/**
 * allc_free - Frees allocated memory
 * @buff: Main buffer
 * @cmds_list: List of commands
 * @commands: Command as an array of arguments
 * @flags: Number indicating which memory to free
*/
void allc_free(char *buff, char **cmds_list, char **commands, int flags)
{
	if (flags & FL_BUFF)
		free(buff);
	if (flags & F_CMD_L)
		free_dbl_ptr(cmds_list);
	if (flags & FL_CMDS)
		free_dbl_ptr(commands);

	free_list(*(head_alias_get()));
	free_hist();
}
