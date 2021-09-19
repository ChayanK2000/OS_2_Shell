#include "sys_commands.h"

void sys_commands(char **inside_token, int k)
{
    int fork_return;
    fork_return = fork();

    if(fork_return == 0)// We enter in child process.
    {
        if(execvp(inside_token[0], inside_token)==-1)
            perror("Execvp");

        exit(0); // if we dont add exit(0) here then say a wrong command is pressed like "bfjbeu"...
        // then the no f times we have entered wrong command for execvp, same no of times "q" wont be 
        // affected. as for "q" we are returning -1 and prolly it is returning to the child process not 
        // to the take_input fucntion in main.c.

        //even if we are not returing -1 as stated above, its a good practice to exit here
    }
    else //we are in parent process.
    {
        wait(NULL);
    }
}