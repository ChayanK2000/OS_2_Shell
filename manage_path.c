#include "manage_path.h"

void manage_dir_names(char *cur_dir)
{
    int len_of_cur_dir = strlen(cur_dir);
    int flag_for_home = 1;
    int i;
    for (i = 0; i < len_home; i++) //using length of home dir...so that say home=/home/c and cur = /home/c/a1/b1/c1/d1...so wo /jome/c ke liye toh '~' print karega hi
    {
        if (cur_home[i] != cur_dir[i])
        {
            flag_for_home = 0;
            break;
        }
    }
    if (flag_for_home == 1) //means '~' is a part of the dir...now whether it is exact same or more is to be done here.
    {
        printf("~");
        //getting the leftover string of cur_dir...alternatively could have used str(n)cpy etc etc
        for (; i < len_of_cur_dir; i++) //carry fwding the previous 'i'
        {
            printf("%c", cur_dir[i]);
        }
    }
    else
    {
        printf("%s", cur_dir);
    }
}
