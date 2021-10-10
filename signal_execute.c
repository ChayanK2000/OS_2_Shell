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
        display_shell_names_dir(); //necessary to do this as ctrl c is just a signal which means we havent really entered anythin in the input asked.
        //Hence teh program will stay at asking the input but the names and direc will not be seen if this is not written here.
        fflush(stdout);
    }
}

// void signal_CtrlZ(int sig_num)
// {
//     pid_t process = processpid;
//     // kill(process, SIGTTIN);
//     if (process > 0)
//     {
//         kill(process, sig_num);
//         // signal(SIGTSTP, sigintHandlerZ);
//         printf("\n");
//         // init_shell();
//         fflush(stdout);
//         background_pids[no_of_backgroundprocess] = process;
//         stopped_pids[no_of_backgroundprocess] = process;

//         char *file = (char *)malloc(sizeof(char) * 100);
//         char st[1000] = "/proc/";
//         char b[] = "/stat";
//         char *snum = (char *)malloc(sizeof(char) * 200);
//         sprintf(snum, "%d", process);
//         strcat(file, st);
//         strcat(file, snum);
//         strcat(file, b);
//         int fd = open(file, O_RDONLY);
//         if (fd == -1)
//         {
//             perror("Ctrl-Z");
//         }
//         else
//         {
//             char *buff = (char *)calloc(300, sizeof(char));
//             read(fd, buff, 300);
//             char **parts = (char **)malloc(100 * sizeof(char *));
//             int i = 0;
//             while (i < 50)
//             {
//                 parts[i] = strsep(&buff, " ");
//                 ++i;
//             }
//             close(fd);
//             background_process[no_of_backgroundprocess] = parts[1];
//             no_of_backgroundprocess++;
//         }
//     }
//     else
//     {
//         printf("\n");
//         init_shell();
//         fflush(stdout);
//     }
// }

void signal_CtrlZ(int sig_num)
{
    int process = fg_pid;
    if (process > 0)
    {
        kill(process, sig_num);
        printf("\n");

        // printf("%d\n", process);
        background_pids[no_of_backgroundprocess] = process;
        stopped_pids[no_of_backgroundprocess] = process;

        int i;
        for (i = 0; i < 200; i++)
        {
            if (foreground_pids[i] == process)
                break;
        }
        background_processes[no_of_backgroundprocess] = foreground_processes[i];
        no_of_backgroundprocess++;

        fflush(stdout);
    }
    else
    {
        printf("\n");
        display_shell_names_dir(); //necessary to do this as ctrl c is just a signal which means we havent really entered anythin in the input asked.
        //Hence teh program will stay at asking the input but the names and direc will not be seen if this is not written here.
        fflush(stdout);
    }
}