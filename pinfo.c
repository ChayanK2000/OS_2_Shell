//IMPORTANT INFO: $$ and $BASHPID gives the pid of bash itself, whereas self is different. Hence have to /proc/self/stat in this pinfo.c
// c@chayan-hp-15-notebook-pc:~$ echo $$
// 2410
// c@chayan-hp-15-notebook-pc:~$ echo $BASHPID 
// 2410
// c@chayan-hp-15-notebook-pc:~$ cat /proc/2410/stat /proc/self/stat
// 2410 (bash) S 2402 2410 2410 34816 9504 4194304 8443 45112 8 762 31 17 83 189 20 0 1 0 13340 23732224 1288 18446744073709551615 94324303974400 94324305036296 140729836702624 0 0 0 65536 3670020 1266777851 1 0 0 17 1 0 0 160 0 0 94324307135888 94324307182948 94324326207488 140729836710303 140729836710308 140729836710308 140729836711918 0
// 9504 (cat) R 2410 9504 2410 34816 9504 4194304 91 0 0 0 0 0 0 0 20 0 1 0 627930 8134656 477 18446744073709551615 93859145560064 93859145591248 140724418489104 0 0 0 0 0 0 0 0 0 17 2 0 0 0 0 0 93859147688560 93859147690176 93859173011456 140724418495251 140724418495287 140724418495287 140724418498543 0

#include "pinfo.h"
#include "manage_path.h"
void apply_pinfo(char **inside_token, int k)
{
    char *proc_file_to_open = (char *)malloc(1000);
    char *proc = (char *)malloc(10);
    char *pid_of_process = (char *)malloc(50);
    char *end_stat = (char *)malloc(10);
    char *end_exe = (char *)malloc(10);
    end_stat = "/stat";
    proc = "/proc/";
    end_exe = "/exe";

    if (k == 1)
    {
        pid_of_process = "self";
    }

    else if (k>=3)
    {
        printf("Error: Currently in my implementation, pinfo can accept at max 1 arg(pid)\n");
        return;
    }

    else 
    {
        pid_of_process = inside_token[1];
    }

    strcat(proc_file_to_open, proc);
    strcat(proc_file_to_open, pid_of_process);
    strcat(proc_file_to_open, end_stat);


    char *pinfo_str = (char *)malloc(1000);
    int fd = open(proc_file_to_open, O_RDONLY);
    
    if (fd < 0)
    {
        perror("file opening");
        return;
    }

    //LSEEK NOT WORKING ON /PROC files!!

    // int total_length = lseek(fd, 0, SEEK_END);
    // lseek(fd, 0, SEEK_SET);
    // printf("%d %d\n", fd, total_length);


    if (read(fd, pinfo_str, 500) < 0)
    {
        perror("Error in reading");
        return;
    }

    char *token;
    int nth_word = 0;
    char *exec_file = (char *)malloc(1000);
    char *pid_for_ref = (char *)malloc(100);
    while ((token = strtok_r(pinfo_str, " ", &pinfo_str)))
    {
        if (nth_word == 0)
        {
            printf("pid -- %s\n", token);
            strcpy(pid_for_ref, token);
        }
        // if (nth_word == 1)
        // {
        //     // int ind = 0;
        //     for (int i = 1; i < strlen(token) - 1; i++)
        //     {
        //         exec_file[i - 1] = token[i];
        //     }
        // }
        if (nth_word == 2)
        {
            printf("Process Status -- %s\n", token);
        }
        if (nth_word == 22)
        {
            printf("memory -- %s\n", token);
        }
        nth_word++;
    }
    char *pathname = (char *)malloc(1000);
    strcat(exec_file, proc);
    strcat(exec_file, pid_for_ref);
    strcat(exec_file, end_exe);
    printf("execfile is %s\n", exec_file);
    int exe_index = readlink(exec_file, pathname, 1000);
    pathname[exe_index] = '\0';
    if(exe_index<0)
    {
        perror("symlink for exe");
        return;
    }
    printf("Executable Path -- ");
    manage_dir_names(pathname);
    printf("\n");

    close(fd);
}