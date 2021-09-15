#include "ls.h"
#include "input.h"
void get_ls_info(char **inside_token, int k) //k is the no of rows - the no of segmented words
{
    // char *all_ls_paths = (char *)malloc(1000 * sizeof(char));
    // all_ls_paths = "";
    char space = ' ';
    char *ls_path = (char *)malloc(1000 * sizeof(char));
    int ind = -1; //index of ls_path having all arguments except the flags
    // printf("%d\n", sizeof(inside_token));
    count = 0;
    int ls_a_flag = 0, ls_l_flag = 0;
    int dir_mention = 0;

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
                else if (inside_token[i][j] == 'l')
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

            if (inside_token[i][0] == '~')
            {
                // memcpy(ls_path, cur_home, strlen(cur_home)); //cant just assign ls_path = cur_home!
                for (int p = 0; p < len_home; p++)
                {
                    ls_path[++ind] = cur_home[p];
                }
                for (int j = 1; j < strlen(inside_token[i]); j++)
                {
                    char ch = inside_token[i][j];
                    // strncat(ls_path, &ch, 1);
                    ls_path[++ind] = ch;
                }
                ls_path[++ind] = space; //writing only " " wihtout variable led to a warning :"assignment makes integer from pointer without a cast"
            }
            else
            {
                // memcpy(ls_path, inside_token[i], strlen(inside_token[i])); //for memcpy to work, inside_token[x] must be allocated via malloc so tht it points to address
                for (int j = 0; j < strlen(inside_token[i]); j++)
                {
                    ls_path[++ind] = inside_token[i][j];
                }
                ls_path[++ind] = space;
            }
            //*****IMPORTANT*****
            //list_files(ls_path, ls_a_flag, ls_l_flag); //cant always call this directly.
            //then ls yo/ -a bo/...-a will not be applied on yo.
            //Thus either make another loop or just store these paths maybe in a array and then execute all of these

            //again making a 2d array seems tedious. Hence just joining all the paths with space. would use strtok again as before.
            // thus similar to just removing the instances of -a or -l... from inside_token(whole 2d)
            // strcat(all_ls_paths, ls_path);
            // strncat(all_ls_paths, &space, 1);

            //Update even the above was not required. Converted the ls_path itself to the long string having all path to directories mentioned.
        }
    }
    if (dir_mention == 0) //case when nothing is entered for path of dir. Could also be done by just adding "./" in ls_path always beforehand
    {                     //can also be done using dir_count
        list_files(".", ls_a_flag, ls_l_flag);
    }
    else
    {
        ls_path[++ind] = '\0';
        char *token;
        while ((token = strtok_r(ls_path, " ", &ls_path)))
        {
            list_files(token, ls_a_flag, ls_l_flag);
        }
    }
}

void list_files(char *ls_path, int ls_a_flag, int ls_l_flag)
{

    count++;
    DIR *dir_ptr;
    struct dirent *dir_read;
    dir_ptr = opendir(ls_path);
    if (dir_ptr == NULL)
    {
        perror("Open Dir");
        exit(1);
    }
    //below 2 lines just when 2 or more directories given for ls
    if (dir_count > 1)
        printf("%s/:\n", ls_path);

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
    //following if just for printing \n for d-1 times while displaying of various drectories

    if ((dir_count > 1) && (dir_count - count >= 1))
    {
        printf("\n");
    }
}
