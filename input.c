#include "input.h"
#include "command.h"
#include "piping.h"
void loopy_func_for_args(char *inp)
{
    char *token;
    //strtok gives issue if called again afterwards for same variable...hence usng strtok_r
    while ((token = strtok_r(inp, ";", &inp)))
    {
        int no_of_pipes_direct = 0;
        for (int j = 0; j < strlen(token); j++)
        {

            if ((token[j] == '|') || (token[j] == '<') || (token[j] == '>'))
                no_of_pipes_direct++;
        }
        if (no_of_pipes_direct > 0)
        {
            pipe_func(token);
            continue; //necessary as when its not there, the pipe arg would have already been executed and
            //again the below line calling tok_by_delim would be there treating the whole token as one argment(just like without piping)
        }
        tok_by_delim_and_execute(token);
    }
}
void tok_by_delim_and_execute(char * token)
{
    char delimit[] = " \t\r\n\v\f";   //possible whitespace chars
    int check_of_while_of_spaces = 0; //var so that we neglect those instances where after tokenizing with spaces,tab,etc, we get nothing.
    char **inside_token = (char **)malloc(40 * sizeof(char *));
    for (int i = 0; i < 40; i++)
    {
        inside_token[i] = (char *)calloc(1000, sizeof(char));
    }
    int i = -1;
    while ((inside_token[++i] = strtok_r(token, delimit, &token)))
    {
        check_of_while_of_spaces = 1;
    }

    if (check_of_while_of_spaces == 1) // to avoid the cases like ls dir1 ; ;   ;cd xyz, and as mentined above beside declaration
    {
        check_for_appropriate_command(inside_token, i);
    }
}

int take_input()
{
    char *inp;
    size_t size_for_inp = 1000 * sizeof(char);
    inp = (char *)malloc(size_for_inp);
    getline(&inp, &size_for_inp, stdin);

    if ((inp[0] == 'e')&&(inp[1] == 'x')&&(inp[2] == 'i')&&(inp[3] == 't'))
    {
        return -1;
    }

    loopy_func_for_args(inp);

    return 0;
}