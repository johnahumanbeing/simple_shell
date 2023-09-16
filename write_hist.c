#include "shell.h"

/**
 * write_hist - Writes the history to a file in home dir
*/
void write_hist(void)
{
	list_t *curr_;
	int fd;
	char *home;

	home = env_get("HOME");
	if (home == NULL)
		home = "/";

	if (chdir(home) == -1)
		return;

	fd = open(".hist_shell", O_CREAT | O_RDWR | O_APPEND, 0666);
	if (fd == -1)
		return;

	for (curr_ = *get_hist_addr(); curr_ != NULL; curr_ = curr_->next)
	{
		write(fd, curr_->str, curr_->len);
		write(fd, "\n", 1);
	}

	close(fd);
}
