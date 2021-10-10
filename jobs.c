#include "jobs.h"

void apply_jobs(char **inside_token, int k)
{
    // printf("ebjenvjn\n");
    int jobs_s_flag = 1, jobs_r_flag = 1;
    for (int i = 0; i < k; i++)
    {
        if (inside_token[i][0] == '-') //for flags
        {
            jobs_r_flag = 0;
            jobs_s_flag = 0;

            for (int j = 1; j < strlen(inside_token[i]); j++) //as we know inside[i][0] = '-'
            {

                //using flag variable to implement what is mentioned in readme #1,2
                //also for the fact that the directory should be determined before the flags
                if (inside_token[i][j] == 's')
                {
                    jobs_s_flag = 1;
                }
                else if (inside_token[i][j] == 'r')
                {
                    jobs_r_flag = 1;
                    // printf("-l detected!\n");
                }
                else
                {
                    printf("wrong jobs command flag...\n");
                    // sys_commands(inside_token, k);
                    return;
                }
            }
        }
    }

    for (int i = 0; i < no_of_backgroundprocess; i++)
    {
        // printf("%d\n", background_pids[i]);
        if (background_pids[i] != 0)
        {
            char **parts = (char **)malloc(100 * sizeof(char *));
            char *file = (char *)malloc(sizeof(char) * 100);
            char st[1000] = "/proc/";
            char b[] = "/stat";
            char *snum = (char *)malloc(sizeof(char) * 200);
            sprintf(snum, "%d", stopped_pids[i]);
            strcat(file, st);
            strcat(file, snum);
            strcat(file, b);
            int fd = open(file, O_RDONLY);
            if (fd == -1)
            {
                background_pids[i] = 0;
                break;
            }
            else
            {
                char *buff = (char *)calloc(300, sizeof(char));
                read(fd, buff, 300);
                int j = 0;
                while (j < 50)
                {
                    parts[j] = strsep(&buff, " ");
                    ++j;
                }
                close(fd);
            }

            char *str;
            if (parts[2][0] == 'R')
            {
                str = "Running";
                if (jobs_r_flag == 1)
                    printf("[%d] %s %s [%d]\n", i + 1, str,
                           background_processes[i], stopped_pids[i]);
            }
            else if (parts[2][0] == 'T' || parts[2][0] == 't')
            {
                str = "Stopped";
                if (jobs_s_flag == 1)
                    printf("[%d] %s %s [%d]\n", i + 1, str,
                           background_processes[i], stopped_pids[i]);
            }
            else if (parts[2][0] == 'D' || parts[2][0] == 'S')
            {
                str = "Running";
                if (jobs_r_flag == 1)
                    printf("[%d] %s %s [%d]\n", i + 1, str,
                           background_processes[i], stopped_pids[i]);
            }
            else if (parts[2][0] == 'Z')
            {
                str = "Stopped";
                if (jobs_s_flag == 1)
                    printf("[%d] %s %s [%d]\n", i + 1, str,
                           background_processes[i], stopped_pids[i]);
            }

            // } else {
            //     printf("[%d] Stopped %s [%d]\n", i + 1,
            //     background_process[i],
            //            stopped_pids[i]);
            // }
        }
    }
}