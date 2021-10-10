#include "sys_commands.h"

void sys_commands(char **inside_token, int k)
{
    // printf("3. %s\n", inside_token[k]); // alreaduy null due to tokenizing...mentioned in input.c
    

    int background = 0;
    char **inside_token_amp;
    if (strcmp(inside_token[k - 1], "&") == 0) // so here the execvp would execute say : gedit & (null)...
    //but instead we should make execvp run gedit (null). We have to remove the & here.
    //Though it is not making any differnce as of now. Curious if it leads to some problem.
    // can tokenize again here wrt & or strsep.
    {
        background = 1;
        inside_token_amp = (char **)malloc(40 * sizeof(char *));
        for (int i = 0; i < 40; i++)
        {
            inside_token_amp[i] = (char *)calloc(1000, sizeof(char));
        }
        int jj = 0;
        while(jj<(k-1))
        {
            inside_token_amp[jj] = inside_token[jj];
            jj++;
        }
        inside_token_amp[jj] = NULL;
    }
    // inside_token[k] = NULL;//no need

    
    int fork_return;
    fork_return = fork();

    if(fork_return == 0)// We enter in child process.
    {
    
        if (background == 1)
        {

            // setpgid(0, 0);
            // // close(STDIN_FILENO);
            // // close(STDOUT_FILENO);
            // close(STDERR_FILENO);
            // printf("yo\n");
            if (execvp(inside_token_amp[0], inside_token_amp) == -1)
                perror("Execvp_amp");
        }
        else
        {
            // printf("entered ehrwe\n");
            if (execvp(inside_token[0], inside_token) == -1)
                perror("Execvp");
        }
        

        exit(0); // if we dont add exit(0) here then say a wrong command is pressed like "bfjbeu"...
        // then the no f times we have entered wrong command for execvp, same no of times "q" wont be 
        // affected. as for "q" we are returning -1 and prolly it is returning to the child process not 
        // to the take_input fucntion in main.c.

        //even if we are not returing -1 as stated above, its a good practice to exit here
    }
    else //we are in parent process.
    {   
        if (background == 0)
        {
            // printf("hi there\n");
            // wait(NULL); //simply writing led to huge consequences. 
            // Example:
            //> ls -s(via execvp)...shows correct as intended
            //any back process like sleep 1 &
            // again after (or while running) if we run any command whch again uses execvp say agian ls -s
            // the it will give the desired output, but there will be <username@hostname> in betweenn out of nowheere and will be an infinite loop after the desired output for ls -s
            if(fg_pid == 0)
                fg_pid = fork_return;
            int status;
            waitpid(fork_return, &status, WUNTRACED);
        }

        else
        {
            
            printf("%d\n", fork_return);
            background_pids[no_of_backgroundprocess] = fork_return;
            no_of_backgroundprocess++;
        }
    }
}