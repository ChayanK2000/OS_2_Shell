#include "terminal.h"
#include "input.h"
#include "main.h"

int main()
{
    no_of_backgroundprocess = 0;

    cd_count = 0;
    printf("Welcome to this personal shell!!\n");
    printf("****************************************************************************\n");
    
    getcwd(cur_home, sizeof(cur_home)); // has to be more than the exact length of the string...so sizeof(the original number put while declaring = 1000 is best option)
    len_home = strlen(cur_home);
    
    int inp_flag = 0;
    while (1)
    {
        // printf("HI, the home dir is: %s\n",cur_home);
        display_shell_names_dir();
        inp_flag = take_input();

        char st[1000] = "/proc/";
        for (int i = 0; i < no_of_backgroundprocess; i++)
        {
            if (background_pids[i] != 0)
            {
                //	printf("%s\n", background_name[i]);
                int no = background_pids[i];
                char *val = (char *)malloc(sizeof(char) * 100);
                char *cat = (char *)malloc(sizeof(char) * 100);
                int cnt = 0;
                while (no > 0)
                {
                    val[cnt] = no % 10 + '0';
                    no /= 10;
                    ++cnt;
                }

                --cnt;
                int j = 0;
                while (j <= cnt)
                {
                    cat[j] = val[cnt - j];
                    ++j;
                }
                strcat(st, cat);
                strcat(st, "/stat");

                int fd = open(st, O_RDONLY);
                if (fd == -1)
                {
                    printf("Background process 'PID' : %s exited successfully \n", cat);
                    background_pids[i] = 0;
                }
                else
                {
                    char *buff = (char *)calloc(1000, sizeof(char));
                    read(fd, buff, 1000);
                    char **parts = (char **)malloc(100 * sizeof(char *));
                    int k = 0;
                    while (k < 10)
                    {
                        parts[k] = strsep(&buff, " ");
                        ++k;
                    }
                    if (strcmp(parts[2], "Z") == 0)
                    {
                        // printf("%d\n", i);
                        printf("Background process %s of 'PID' : %s exited successfully \n", parts[1], cat);
                        background_pids[i] = 0;
                    }
                    close(fd);
                }
                free(val);
                free(cat);
            }
        }

        if (inp_flag == -1)
            break;
        fflush(stdout);
    }

    return 0;
}