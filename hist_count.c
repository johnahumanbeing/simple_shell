#include "shell.h"

static int LINE_CNT;

/**
 * line_cnt_updt - Counts the lines in the prev
*/

void line_cnt_updt(void)
{
	char current_dir[512];
	char buff_rd[1024];
	int i, fd, char_rd;
	char *Home;

	LINE_CNT = 0;

	if (getcwd(current_dir, 512) == NULL)
		return;

	Home = _getenv("HOME");
	if (Home == NULL)
		Home = "";

	if (chdir(Home) == -1)
		return;

	fd = open(".hist_shell", O_RDONLY);
	if (fd == -1)
		return;

	while ((char_rd = read(fd, buff_rd, 1024)) != -1)
	{
		if (char_rd == 0)
			break;

		for (i = 0; i < char_rd; i++)
			if (buff_rd[i] == '\n')
				LINE_CNT++;
	}

	chdir(current_dir);
}

/**
 * hist_count - Returns the lines count of history
 *
 * Return: line count ponter
*/

int *hist_count()
{
	return (&LINE_CNT);
}
