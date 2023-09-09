#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * this is a dummy code i got from chatgpt
 * we will create ours
 * this one is just to get and idea
 * you can compile and test it
 * don't worry about the other code that was on UNX.C 
 * nimeisave somewhere
 * don't worry about betty for now hiyo tunaeza fix later after code
 * yote inawork
 * i will explain the concept then we will split the work
*/

#define MAX_INPUT_LENGTH 1024

int main() {
    char input[MAX_INPUT_LENGTH];
    
    while (1) {
        // Print a prompt
        printf("SimpleShell> ");
        fflush(stdout);
        
        // Read user input
        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
            break;
        }

        // Remove the trailing newline character
        input[strlen(input) - 1] = '\0';

        // Fork a new process
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { // Child process
            // Parse the command
            char *args[100];
            int argCount = 0;
            char *token = strtok(input, " ");
            
            while (token != NULL) {
                args[argCount] = token;
                argCount++;
                token = strtok(NULL, " ");
            }
            args[argCount] = NULL;

            // Execute the command
            if (execvp(args[0], args) == -1) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        } else { // Parent process
            // Wait for the child to finish
            wait(NULL);
        }
    }

    return 0;
}
