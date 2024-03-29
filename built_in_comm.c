#include "built_in_comm.h"

void built_in_commands_cd(char **inside_token, int k) //k is the no of rows,i.e the segregated words per command
{
    getcwd(curr_working_dir, sizeof(curr_working_dir));

    if (k == 1) //when only "cd" is enetred with no arguments
    {
        strcpy(last_working_dir, curr_working_dir);
        if (chdir(cur_home) == -1)
        {   
            perror("Unable to go to ~");
            return;
        }
        else
        {
            getcwd(curr_working_dir, sizeof(curr_working_dir));
            cd_count++;
        }
    }
    else if(k>=3)
    {
        printf("Too many arguments for cd command!\n");
        return;
    }
    else if(strcmp(inside_token[1],"-")==0) //beter to take this whole in the else part logically, though no harm here as well
    {   
        if (cd_count<1)
        {
            printf("Old working dir not set\n");
            return;
        }

        char *temp = (char*)malloc(1000*sizeof(char)); //not initilizing will lead to segmentation fault
        strcpy(temp, last_working_dir);
        strcpy(last_working_dir, curr_working_dir);
        if ((chdir(temp) == -1))
        {
            perror("Cannot go to last dir");
            return;
        }
        
        else
        {
            getcwd(curr_working_dir, sizeof(curr_working_dir));
            cd_count++;
        }
                
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
        strcpy(last_working_dir, curr_working_dir);
        if (chdir(temp_path) == -1)
        {
            perror("Cannot change directory");
            return;
        }
        else
        {
            getcwd(curr_working_dir, sizeof(curr_working_dir));
            cd_count++;
        }
    }
}

void built_in_commands_echo(char **inside_token, int k)
{
    for (int i = 1; i < k;i++)
    {
        printf("%s", inside_token[i]);
        if(i!=(k-1))
            printf(" ");
    }
    printf("\n");
}

void built_in_commands_pwd()
{
    char pwd_by_cwd[1000];
    printf("%s\n",getcwd(pwd_by_cwd,sizeof(pwd_by_cwd)));
}