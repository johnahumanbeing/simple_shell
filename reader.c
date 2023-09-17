#include "shell.h"
#define BUFF_SIZE 32

/**
 * line_rd - print a line of fd
 * @fd: file descriptor
 * @line: line of text
 * Return: execution of read_line: 1 if success
 */

int line_rd(const int fd, char **line)
{
	int rdr;
	char *tmp;
	char buffer[BUFF_SIZE + 1];
	static char	*str[4864];

	if (fd < 0 || BUFF_SIZE <= 0 || line == NULL || read(fd, buffer, 0) < 0)
		return (-1);
	while ((rdr = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[rdr] = '\0';
		if (!str[fd])
			str[fd] = str_dup(buffer);
		else
		{
			tmp = join_str(str[fd], buffer);
			free(str[fd]);
			str[fd] = tmp;
		}
		if (strchr(str[fd], '\n'))
			break;
	}
	if (str[fd] == NULL && rdr == 0)
		return (-1);
	return (line_rd_f(str, line, fd));
}

/**
 * line_rd_f - read a line from fd
 * @str: grip of documment
 * @fd: file descriptor
 * @line: line of text
 * Return: 1 if success
 */
int	line_rd_f(char **str, char **line, int fd)
{
	char *tmp;
	int	count;

	count = 0;
	while (str[fd][count] != '\0' && str[fd][count] != '\n')
		count++;
	*line = strsub_f(str[fd], 0, count);
	if (str[fd][count] == '\n')
	{
		tmp = str_dup(&str[fd][count + 1]);
		free(str[fd]);
		str[fd] = tmp;
		if (str[fd][0] == '\0')
			strdel_f(&str[fd]);
	}
	else
		strdel_f(&str[fd]);
	return (1);
}

/**
 * _help - functions that simulate help command
 * @cmd: array of strings to execute
 * Return: 0 if is positive (1 is true min.); -1 if is error
 */
int _help(char **cmd)
{

	int fd, i = 1, result = -1;
	char *line = NULL;

	while (cmd[i])
	{
		fd = open(cmd[i], O_RDONLY);
		if (fd != -1)
		{
			result = 0;
			while (line_rd(fd, &line) == 1)
			{
				puts(line);
				free(line);
			}
			close(fd);
		}
		i++;
	}

	return (result);
}
