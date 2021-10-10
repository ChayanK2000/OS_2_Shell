#include "signal_execute.h"
#include "terminal.h"
void signal_CtrlC(int sig_num)
{
    pid_t process = fg_pid;
    if (process > 0)
    {
        kill(process, sig_num);
        printf("\n");
        // // init_shell();
        fflush(stdout);
    }
    else
    {
        printf("\n");
        display_shell_names_dir();
        fflush(stdout);
    }
}