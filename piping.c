#include "piping.h"
#include "input.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

void pipe_func(char *token)
{
    char **pipe_args = (char **)malloc(40 * sizeof(char *));
    for (int i = 0; i < 40; i++)
    {
        pipe_args[i] = (char *)calloc(1000, sizeof(char));
    }
    int pipe_num = -1;

    while ((pipe_args[++pipe_num] = strtok_r(token, "|", &token))) //this will also give the output even if '|' is not present.
    //For example: -> ls....here pipe_args[0] will be 'ls' .Hence we enter this whole function only when '|' is present. This is checked in the input.c file itself.
    {
    }
    
    // would be using two pipes and alternatively using them
    int fd_1[2];
    int fd_2[2];
    if (pipe(fd_1) < 0)
    {
        perror("pipe for first fd");
    }
    if (pipe(fd_2) < 0)
    {
        perror("pipe for second fd");
    }

    //the following usage of 'original not required, though i though it is necessary. 
    //I thought not doing this will never allow anything to be printed on stdout, as was also shown in the tutorial : Tutrial3/1_dup.c
    int original;
    dup2(STDOUT_FILENO, original);
    for (int i = 0; i < pipe_num; i++) //because no_of_arg = pipe_num(as pipe_num starts from 0)
    {
        int fork_pid = fork();
        if (fork_pid == 0)
        {
            if ((i % 2) == 0)
            {
                if ((i == 0) || (i == (pipe_num - 1)))
                {

                    if (i == 0)
                    {
                        // printf("i==0 : %s\n", pipe_args[i]);
                        dup2(fd_1[1], STDOUT_FILENO);
                    }
                    if (i == (pipe_num - 1))
                    {
                        dup2(original, STDOUT_FILENO);
                        dup2(fd_2[0], STDIN_FILENO);
                    }
                }
                else
                {
                    dup2(fd_2[0], STDIN_FILENO);
                    dup2(fd_1[1], STDOUT_FILENO);
                }
                // close(fd_1[0]);
                // close(fd_1[1]);
                // close(fd_2[0]);
                // close(fd_2[1]);
            }
            else
            {
                if (i == (pipe_num - 1))
                {
                    // printf("i == pipenum-1: %s\n", pipe_args[i]);
                    dup2(original, STDOUT_FILENO);
                    dup2(fd_1[0], STDIN_FILENO);
                }
                else
                {
                    // printf("i==pipenum-1 else: %s\n", pipe_args[i]);

                    dup2(fd_1[0], STDIN_FILENO);
                    dup2(fd_2[1], STDOUT_FILENO);
                }
                // close(fd_1[0]);
                // close(fd_1[1]);
                // close(fd_2[0]);
                // close(fd_2[1]);
            }
            tok_by_delim_and_execute(pipe_args[i]);
            exit(0);
        }
        else
        {

            if (i % 2 == 0)
            {
                if (i != 0)
                {
                    close(fd_2[0]);
                }
                if (i != pipe_num - 1)
                {
                    close(fd_1[1]);
                }
            }
            else
            {
                close(fd_1[0]);
                if (i != pipe_num - 1)
                {
                    close(fd_2[1]);
                }
            }

            //idk but the following doesnt work. it shud as c.osing the fds doesnt affect the stdin/out going to the respective fds, 
            //thats why i thought of closing all always, but seems that it is not working. thus the above written.
            // close(fd_1[0]);
            // close(fd_1[1]);
            // close(fd_2[0]);
            // close(fd_2[1]);
            wait(NULL);
        }
    }
}