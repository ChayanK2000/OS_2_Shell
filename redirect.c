#include "redirect.h"
#include "input.h"

void redirect_func(char *token, int no_of_redirect_inp, int no_of_redirect_out, int no_of_redirect_out_append)
{
    char *output_file = (char *)malloc(100);
    char *input_file = (char *)malloc(100);
    char *token1 = (char *)malloc(100);//future use while tokenizing using '<'
    char *token2 = (char *)malloc(100);//future use while tokenizing using '>'
    strcpy(token1, token);
    strcpy(token2, token);
    
    // the below code may be redundant as we can retrieve the first arg by redir_in_args as well as redir_out_args
    //still doing for cases when command start like: <>hfhnln or ><beufbbjbu etc etc. 
    char **redir_args = (char **)malloc(40 * sizeof(char *));
    for (int i = 0; i < 40; i++)
    {
        redir_args[i] = (char *)calloc(1000, sizeof(char));
    }
    
    int ii = -1;
    char temp[] = "<>";
    while ((redir_args[++ii] = strtok_r(token, temp, &token)))
    {
    }

    // printf("%s\n", redir_args[0]);
    if ((no_of_redirect_out_append > 0) || (no_of_redirect_out > 0))
    {
        char **redir_out_args = (char **)malloc(40 * sizeof(char *));
        for (int i = 0; i < 40; i++)
        {
            redir_out_args[i] = (char *)calloc(1000, sizeof(char));
        }
        int i = -1;
        while ((redir_out_args[++i] = strtok_r(token1, ">", &token1)))
        {
        }
        char delimit[] = " \t\r\n\v\f"; //possible whitespace chars
        // printf("(%s)\n", redir_out_args[i - 1]);
        output_file = strtok(redir_out_args[i - 1], delimit);
    }
    if (no_of_redirect_inp > 0)
    {
    
        char **redir_in_args = (char **)malloc(40 * sizeof(char *));
        for (int i = 0; i < 40; i++)
        {
            redir_in_args[i] = (char *)calloc(1000, sizeof(char));
        }
        int i = -1;
        while ((redir_in_args[++i] = strtok_r(token2, "<", &token2)))
        {
        }
        char delimit[] = " \t\r\n\v\f"; //possible whitespace chars
        
        input_file = strtok(redir_in_args[i - 1], delimit);
    }

    int fork_redir = fork();
    if (fork_redir == 0)
    {
        if (no_of_redirect_inp > 0)
        {
            int fd1 = open(input_file, O_RDONLY);
            if (fd1 < 0)
            {
                perror("input file");
                exit(0);
            }
            //proceeding if file there
            if (dup2(fd1, STDIN_FILENO) == -1)
            {
                perror("dup2");
                exit(0);
            }
        }
        if ((no_of_redirect_out > 0) || (no_of_redirect_out_append) > 0)
        {
            int fd2;
            if (no_of_redirect_out_append > 0)
                fd2 = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            else
                fd2 = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

            if (fd2 == -1)
            {
                perror("output file");
                exit(0);
            }

            if (dup2(fd2, STDOUT_FILENO) == -1)
            {
                perror("dup2");
                exit(0);
            }
        }

        loopy_func_for_args(redir_args[0]);
        exit(0);

    }
    else
    {
        int status;
        waitpid(fork_redir, &status, WUNTRACED);
    }
    

}