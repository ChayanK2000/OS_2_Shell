#include "ls.h"
void get_ls_info(char **inside_token,int k) //k is the no of rows - the no of segmented words
{
    
    // printf("%d\n", sizeof(inside_token));
    int ls_a_flag = 0, ls_l_flag = 0;
    int dir_mention = 0;
    // printf("%d\n", k);
    for (int i = 1; i < k; i++) //starting from i=1 as we already know inside_token[0] = "ls"
    {
        
        if (inside_token[i][0] == '-') //for flags
        {
            
            for (int j = 1; j < strlen(inside_token[i]); j++) //as we know inside[i][0] = '-'
            {

                //using flag variable to implement what is mentioned in readme #1,2
                //also for the fact that the directory should be determined before the flags
                if (inside_token[i][j] == 'a') 
                {
                    ls_a_flag = 1;

                }
                else if(inside_token[i][j] == 'l')
                {
                    ls_l_flag = 1;
                }
                else
                {
                    printf("wrong ls command flag");
                    exit(1);
                }
            }
        }
        else //for directories
        {
            dir_mention = 1;
            char *ls_path = (char *)malloc(1000 * sizeof(char));
            if (inside_token[i][0] == '~')
            {
                memcpy(ls_path, cur_home, strlen(cur_home)); //cant just assign ls_path = cur_home!
                for (int j = 1; j < strlen(inside_token[i]); j++)
                {
                    char ch = inside_token[i][j];
                    strncat(ls_path, &ch, 1);
                }
            }
            else
            {
                memcpy(ls_path, inside_token[i], strlen(inside_token[i]));//for memcpt to work, inside_token[x] must be allocated via malloc so tht it points to address
            }
            // printf("The ls path is: %s\n", ls_path);
            list_files(ls_path,ls_a_flag,ls_l_flag);
        }

    }
    if (dir_mention == 0) //case when nothing is entered for path of dir. Could also be done by just adding "./" in ls_path always beforehand
    {
        list_files(".", ls_a_flag, ls_l_flag);
    }
    
    
}

void list_files(char *ls_path, int ls_a_flag, int ls_l_flag)
{
    DIR *dir_ptr;
    struct dirent *dir_read;
    dir_ptr = opendir(ls_path);
    if (dir_ptr == NULL)
    {
        perror("Open Dir");
        exit(1);
    }
    while ((dir_read = readdir(dir_ptr)) != NULL)
    {
        // printf("%d\n", ls_a_flag);
        if (ls_a_flag == 0)
        {
            if ((dir_read->d_name)[0] == '.')
                continue;
        }
        printf("%s\n", dir_read->d_name);
    }
}


// int var = 5;
// int var1 = 9;
// int *ptr;
// ptr = &var;
// printf("%lld %lld %lld %lld\n", ptr, *ptr, &ptr, &var);