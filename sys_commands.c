#include "sys_commands.h"

void sys_commands(char **inside_token, int k)
{
    
    int background = 0;
    if (strcmp(inside_token[k - 1], "&") == 0)
    {
        background = 1;
        // inside_token[k-1]
    }

    int fork_return;
    fork_return = fork();

    if(fork_return == 0)// We enter in child process.
    {   
        if (background == 1)
        {
            setpgid(0, 0);
            // close(STDIN_FILENO);
            // close(STDOUT_FILENO);
            close(STDERR_FILENO);
        }
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
        if (background == 0)
            wait(NULL);

        else
        {
            // this prevents making of zombie process which  is very important
            //https: //www.geeksforgeeks.org/zombie-processes-prevention/
            //signal(SIGCHLD, SIG_IGN);
            // sighandler(SIGCHLD, put function here???);
            // signal(SIGCHLD, func);
            printf("%d\n", fork_return);
            background_pids[no_of_backgroundprocess] = fork_return;
            // background_name[no_of_backgroundprocess] = args[0];
            // printf("%d\n", no_of_backgroundprocess);
            // printf("%s\n", background_name[no_of_backgroundprocess]);
            no_of_backgroundprocess++;
        }
    }
}