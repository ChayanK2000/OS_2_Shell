// #include <sys/utsname.h> //for using command "uname"...not necessary as it gave output as "Linux"
#include "terminal.h"
#include "manage_path.h"
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
    manage_dir_names(cur_dir);

    printf(">");
    fflush(stdout);
}
