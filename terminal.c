// #include <sys/utsname.h> //for using command "uname"...not necessary as it gave output as "Linux"
#include "terminal.h"
// #include "main.h" //for getting cur_home_dir, all common libraries

void display_shell_names_dir()
{
    // struct utsname *buf;
    char user_name[100];
    getlogin_r(user_name, 100);
    printf("<");
    printf("%s", user_name);
    printf("@");
    char host_name[100];
    gethostname(host_name, 100);
    printf("%s:", host_name);

    //printing the current directory as ~ or anything else accordingly
    char cur_dir[1000];
    getcwd(cur_dir, sizeof(cur_dir));
    // if (strcmp(cur_home,cur_dir) == 0)
    // {
    //     printf("~");
    // }
    // int len_of_home_dir = strlen(cur_home); //not reqd as already there in main.c,main.h
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

    printf(">");
    fflush(stdout);
}
