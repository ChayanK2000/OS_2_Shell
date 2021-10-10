#include "signal_execute.h"
#include "terminal.h"
void signal_CtrlC(int sig_num)
{
    int process = fg_pid;
    if (process > 0)
    {
        kill(process, sig_num);
        printf("\n");
        fflush(stdout);
    }
    else
    {   
        printf("\n");
        display_shell_names_dir();
        fflush(stdout);
    }
}

