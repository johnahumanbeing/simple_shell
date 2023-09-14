#include "shell.h"

static int PROC_EXIT;
static int code_init = 1;

/**
 * code_exiter - Returns the address of proc_exit
 *
 * Return: Address of proc_exit
*/
int *code_exiter()
{
	if (code_init)
	{
		PROC_EXIT = 0;
		code_init = 0;
	}

	return (&PROC_EXIT);
}

/**
 * code_exit_set - Sets the value for proc_exit
 * @code: proc_exit rep
*/

void code_exit_set(int code)
{
	PROC_EXIT = code;
}
