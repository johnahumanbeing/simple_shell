#include "shell.h"


/**
 * tokenize - function that tokenizes the command
 * @s: sting to tokenize
 * return: tokenized command
*/

void _printer(const char *characters)
{
    write(STDOUT_FILENO, characters, strlen(characters));
}
