#include "built_in_comm.h"

void built_in_commands_cd(char **inside_token, int k)
{
    if(k == 1) //when only "cd" is enetred with no arguments
    {
        chdir(cur_home);
    }
    else if(k>=3)
    {
        printf("Too many arguments for cd command!\n");
        // exit(1);
    }
    else
    {
        int ind = -1;
        char *temp_path = (char *)malloc(1000 * sizeof(char));
        if(inside_token[1][0]=='~')
        {
            // strcpy(temp_path, cur_home);
            for (int p = 0; p < len_home;p++)
            {
                temp_path[++ind] = cur_home[p];
            }

            // strcat(temp_path, inside_token[1]);? how to do this in one line??
            for (int j = 1; j < strlen(inside_token[1]); j++) //i=1 coz '~' already satisfied
            {
                char ch = inside_token[1][j];
                temp_path[++ind] = ch;
            }
        }
        else
        {
            // strcpy(temp_path, inside_token[1]);
            for (int j = 0;j<strlen(inside_token[1]);j++)
            {
                temp_path[++ind] = inside_token[1][j];
            }
        }
        temp_path[++ind] = '\0';
        if (chdir(temp_path) == -1)
        {
            perror("Cannot change directory");
        }
    }


}