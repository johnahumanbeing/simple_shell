#include "shell.h"


/**
 * _printer - function that prints the characters
 * @characters: sting to tokenize
 * return: is void
*/

void _printer(const char *characters)
{
    write(STDOUT_FILENO, characters, strlen(characters));
}

/**
 * prompt_usr - displays a prompt
 * Return: is void
*/

void prompt_usr(void)
{
        _printer("$");
        fflush(stdout);
}

/**
 * execute_propt - function that executes the prompt
 * 
*/

void execute_prompt(const char *comnd)
{
    pid_t child_pid = fork();

    if (child_pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    else if (child_pid == 0)
    {
        execlp(comnd, comnd, (char *)NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(NULL);
    }
    
}
