#include "terminal.h"
#include "input.h"
#include "main.h"
#include "signal_execute.h"
#include <math.h>

int main()
{
    no_of_backgroundprocess = 0;
    
    cd_count = 0;
    printf("Welcome to this personal shell!!\n");
    printf("****************************************************************************\n");
    
    getcwd(cur_home, sizeof(cur_home)); // has to be more than the exact length of the string...so sizeof(the original number put while declaring = 1000 is best option)
    len_home = strlen(cur_home);
    
    int inp_flag = 0;
    // int count = -1;
    while (1)
    {
        // printf("HI, the home dir is: %s\n",cur_home);
        // count++;
        // printf("(%d)\n", count);
        signal(SIGINT, signal_CtrlC);

        display_shell_names_dir();
        fg_pid = 0;
        inp_flag = take_input();

        char st[1000] = "/proc/";
        for (int i = 0; i < no_of_backgroundprocess; i++)
        {
            if (background_pids[i] != 0)
            {
                //	printf("%s\n", background_name[i]);
                int no = background_pids[i];
                char pid_no_in_str[15];
                sprintf(pid_no_in_str, "%d", no);
                strcat(st, pid_no_in_str);
                strcat(st, "/stat");

                int fd = open(st, O_RDONLY);
                if (fd == -1)
                {
                    printf("Background process 'PID' : %s exited successfully \n", pid_no_in_str);
                    background_pids[i] = 0;
                }
                else
                {
                    char *buff = (char *)calloc(1000, sizeof(char));
                    read(fd, buff, 1000);
                    char **parts = (char **)malloc(100 * sizeof(char *));
                    int k = -1;
                    while((parts[++k] = strtok_r(buff," ",&buff)))
                    {

                    }

                    if (strcmp(parts[2], "Z") == 0)
                    {
                        // printf("%d\n", i);
                        printf("Background process %s of 'PID' : %s exited successfully \n", parts[1], pid_no_in_str);
                        background_pids[i] = 0;
                    }
                    // free(buff);
                    // for (int kk = 0; kk < k;kk++)
                    // {
                    //     free(parts[kk]);
                    // }
                    // free(parts);
                    close(fd);
                }
                
            }
        }

        if (inp_flag == -1)
            break;
        fflush(stdout);
    }

    return 0;
}