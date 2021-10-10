#include "command.h"
#include "ls.h"
#include "built_in_comm.h"
#include "sys_commands.h"
#include "pinfo.h"

void check_for_appropriate_command(char **inside_token, int i)
{
    // printf("2. %s\n", inside_token[i]);
    
    if (strcmp(inside_token[0], "ls") == 0)
    {
        dir_count = 0;

        for (int p = 1; p < i; p++) //p==1 as 'ls' alredy there with 0th index
        {
            if ((inside_token[p][0] != '-'))
            {
                dir_count++; //using/writing this just for those cases where mmore than directory is given...
                //hence we need to first write "dir name:" before listing files and exra newline at end etc etc
            }
        }
        get_ls_info(inside_token, i); //sending the value of 'i' which is basically no of segmented words.
        //This is because we cant calcualte te no of rows occupied in a 2d array in c
    }
    else if (strcmp(inside_token[0], "cd") == 0)
    {
        built_in_commands_cd(inside_token, i);
    }

    else if (strcmp(inside_token[0], "echo") == 0)
    {
        built_in_commands_echo(inside_token, i); //no need of whole command and i...just send the argument
    }

    else if (strcmp(inside_token[0], "pwd") == 0) //because in normal terminal as well...it doent matter what is there after pwd..if pwd present then it just gives the pwd.
    {
        built_in_commands_pwd();
    }
    else if (strcmp(inside_token[0], "pinfo") == 0)
    {
        apply_pinfo(inside_token, i);
    }
    
    else
    {
        sys_commands(inside_token, i);
    }
}