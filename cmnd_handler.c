#include "shell.h"

/**
 * input_parser - Buidls an array of strings as arguments
 * @str_input: Command input given by the user
 * @delimiter: String od chars indicating the delimiters
 *
 * Return: Array of strings
*/
char **input_parser(char *str_input, char *delimiter)
{
	int i, args_count = 0;
	char **args;
	char *token, *tkn_ptr;
	char *str_copy;

	if (str_input == NULL)
		dispatch_error("Error while parsing the command\n");

	args_count = count_args(str_input, delimiter);

	args =  alloc_memry(sizeof(char *) * (args_count + 1));

	str_copy = strdup(str_input);
	tkn_ptr = str_copy;
	for (i = 0; i < args_count; i++)
	{
		token = strtok(tkn_ptr, delimiter);
		if (token == NULL)
			break;
		tkn_ptr = NULL;
		args[i] = duplicate_string(token);
	}

	args[i] = NULL;

	free(str_copy);

	return (args);
}

/**
 * args_counter - Counts the number of arguments in a command string
 * @str_input: Command as a string
 * @delimiter: Delimiter by wich to separate the args
 *
 * Return: Number of arguments present in str_input
*/
int args_counter(char *str_input, char *delimiter)
{
	char *tkn, *tkn_ptr;
	int count = 0;
	char *str_copy = duplicate_string(str_input);

	tkn_ptr = str_copy;
	while ((tkn = strtok(tkn_ptr, delimiter)) != NULL)
	{
		count++;
		tkn_ptr = NULL;
	}

	free(str_copy);

	return (count);
}

/**
 * PATH_Handler - Checks if the command to execute could be found in PATH's dirs
 * @commands: Array of strings containing the command and args
 * Return: flag 0 if is succes; -1 if is error
*/

int PATH_Handler(char **commands)
{
	char *path_dirs, *path;
	char *tkn, *tkn_ptr;
	char *str_copy;
	int flag = 127;

	if (
		commands == NULL || commands[0] == NULL ||
		commands[0][0] == '\0' || commands[0][0] == '/'
	)
		return (127);

	if (access(commands[0], F_OK) == 0)
		return (0);

	path_dirs = env_get("PATH");
	if (path_dirs == NULL)
		return (127);

	str_copy = strdup(path_dirs);
	tkn_ptr = str_copy;
	while (1)
	{
		tkn = strtok(tkn_ptr, ":");
		if (tkn == NULL)
			break;
		tkn_ptr = NULL;
		path = path_finder(tkn, commands[0]);
		if (access(path, F_OK) != -1)
		{
			free(commands[0]);
			commands[0] = path;
			flag = 0;
			break;
		}
		free(path);
	}
	free(str_copy);
	return (flag);
}

/**
 * path_finder - Creates a string representing a full path to file
 * @dir: String representing a directory path
 * @filename: Name of the file we are looking for
 *
 * Return: String as a full path to "filename"
*/
char *path_finder(char *dir, char *filename)
{
	int dir_len = strlen(dir);
	int filename_len = strlen(filename);
	char *path;

	path = alloc_memry(sizeof(char *) * (dir_len + filename_len + 2));

	strcpy(path, dir);
	strcat(path, "/");
	strncat(path, filename, filename_len + 1);

	return (path);
}
