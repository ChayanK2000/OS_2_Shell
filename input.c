#include "input.h"
#include "ls.h"
#include "built_in_comm.h"
int take_input()
{
    char *inp;
    size_t size_for_inp = 1000 * sizeof(char);
    inp = (char *)malloc(size_for_inp);
    getline(&inp, &size_for_inp, stdin);

    if (inp[0] == 'q')
    {
        return -1;
    }

    char delimit[] = " \t\r\n\v\f"; //possible whitespace chars
    char *token;
    //strtok gives issue if called again afterwards for same variable...hence usng strtok_r
    while ((token = strtok_r(inp,";",&inp)))
    {
        int check_of_while_of_spaces = 0; //var so that we neglect those instances where after tokenizing with spaces, we get nothing.
        char **inside_token = (char **)malloc(40 * sizeof(char *));
        for (int i = 0; i < 40; i++)
        {
            inside_token[i] = (char *)calloc(1000, sizeof(char));
        }
        int i = -1;
        dir_count = 0;
        while ((inside_token[++i] = strtok_r(token, delimit, &token)))
        {
            check_of_while_of_spaces = 1;
            if ((inside_token[i][0] != '-') && (i >= 1))
            {
                dir_count++; //using/writing this just for those cases where mmore than directory is given...
                //hence we need to first write "dir name:" before listing files and exra newline at end etc etc
            }
        }
        if (check_of_while_of_spaces == 1) // to avoid the cases like ls dir1 ; ;   ;cd xyz, and as mentined above beside declaration
        {
            if (strcmp(inside_token[0], "ls") == 0)
            {
                get_ls_info(inside_token,i); //sending the value of 'i' which is basically no of segmented words.
                //This is because we cant calcualte te no of rows occupied in a 2d array in c
                
            }
            else if (strcmp(inside_token[0],"cd") == 0)
            {
                built_in_commands_cd(inside_token,i);
            }

            else if (strcmp(inside_token[0], "echo") == 0)
            {
                built_in_commands_echo(inside_token, i);//no need of whole command and i...just send the argument
            }

            else if (strcmp(inside_token[0], "pwd") == 0)//because in normal terminal as well...it doent matter what is there after pwd..if pwd present then it just gives the pwd.
            {
                built_in_commands_pwd();
            }
            // else
            // {
            //     sys_commands(inside_token, i);
            // }
        }
    }
    return 0;
}