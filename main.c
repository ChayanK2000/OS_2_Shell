#include "terminal.h"
#include "input.h"
#include "main.h"

int main()
{
    printf("Welcome to this personal shell!!\n");
    printf("****************************************************************************\n");

    getcwd(cur_home, sizeof(cur_home)); // has to be more than the exact length of the string...so sizeof(the original number put while declaring = 1000 is best option)
    int inp_flag = 0;
    while (1)
    {
        printf("HI, the home dir is: %s\n",cur_home);
        display_shell_names_dir();

        inp_flag = take_input();
        if (inp_flag == -1)
            break;
    }


    return 0;
}