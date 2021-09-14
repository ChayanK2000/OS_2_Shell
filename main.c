#include "terminal.h"
#include "main.h"

int main()
{
    printf("Welcome to this personal shell!!\n");
    printf("****************************************************************************\n");

    getcwd(cur_home, sizeof(cur_home)); // has to be more than the exact length of the string...so sizeof(the original number put while dec;aring is best option)
    while(1)
    {
        display_shell_names_dir();
        char *inp;
        size_t size_for_inp = 1000 * sizeof(char);
        inp = (char *)malloc(size_for_inp);
        getline(&inp, &size_for_inp, stdin);
        if (inp[0] == 'A')
        {
            break;
        }
    }


    return 0;
}