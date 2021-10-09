#include "ls.h"
#include "input.h"
#include "sys_commands.h"

void get_ls_info(char **inside_token, int k) //k is the no of rows ,i.e, the no of segmented words
{
    char space = ' ';
    char slash = '/';
    char *ls_path = (char *)malloc(1000 * sizeof(char)); // this will have all words except 'ls' and '-al'
    int ind = -1; //index of ls_path having all arguments except the flags
    count = 0;
    int ls_a_flag = 0, ls_l_flag = 0;
    int dir_mention = 0;

    for (int i = 1; i < k; i++) //starting from i=1 as we already know inside_token[0] = "ls"
    {

        if (inside_token[i][0] == '-') //for flags
        {

            for (int j = 1; j < strlen(inside_token[i]); j++) //as we know inside[i][0] = '-'
            {

                //using flag variable to implement what is mentioned in readme #1,2
                //also for the fact that the directory should be determined before the flags
                if (inside_token[i][j] == 'a')
                {
                    ls_a_flag = 1;
                }
                else if (inside_token[i][j] == 'l')
                {
                    ls_l_flag = 1;
                    // printf("-l detected!\n");
                }
                else
                {
                    printf("wrong ls command flag...Re-directing the request via execvp\n");
                    sys_commands(inside_token, k);
                    return;
                }
            }
        }
        else //for directories
        {
            dir_mention = 1;

            if (inside_token[i][0] == '~')
            {
                // memcpy(ls_path, cur_home, strlen(cur_home)); //cant just assign ls_path = cur_home!
                for (int p = 0; p < len_home; p++)
                {
                    ls_path[++ind] = cur_home[p];
                }
                for (int j = 1; j < strlen(inside_token[i]); j++)
                {
                    char ch = inside_token[i][j];
                    // strncat(ls_path, &ch, 1);
                    ls_path[++ind] = ch;
                }
                if (ls_path[ind] != '/') // to add a slash if not already present. this is necessary when using this path to get stat or lstat of some other file.
                {
                    ls_path[++ind] = slash;
                }
                ls_path[++ind] = space; //writing only " " wihtout variable led to a warning :"assignment makes integer from pointer without a cast"
            }
            else
            {
                // memcpy(ls_path, inside_token[i], strlen(inside_token[i])); //for memcpy to work, inside_token[x] must be allocated via malloc so tht it points to address
                for (int j = 0; j < strlen(inside_token[i]); j++)
                {
                    ls_path[++ind] = inside_token[i][j];
                }
                if(ls_path[ind] != '/')
                {
                    ls_path[++ind] = slash;
                }
                ls_path[++ind] = space;
            }
            //*****IMPORTANT*****
            //list_files(ls_path, ls_a_flag, ls_l_flag); //cant always call this directly.
            //then ls yo/ -a bo/...-a will not be applied on yo.
            //Thus either make another loop or just store these paths maybe in a array and then execute all of these

            //again making a 2d array seems tedious. Hence just joining all the paths with space. would use strtok again as before.
            // thus similar to just removing the instances of -a or -l... from inside_token(whole 2d)
            // strcat(all_ls_paths, ls_path);
            // strncat(all_ls_paths, &space, 1);

            //Update: even the just above 2 lines of code(now commented) was not required. Converted the ls_path itself to the long string having all path to directories mentioned.
        }
    }
    if (dir_mention == 0) //case when nothing is entered for path of dir. Could also be done by just adding "./" in ls_path always beforehand
    {                     //can also be done using dir_count
        list_files("./", ls_a_flag, ls_l_flag);
    }
    else
    {
        ls_path[++ind] = '\0';
        char *token;
        while ((token = strtok_r(ls_path, " ", &ls_path)))
        {   
            list_files(token, ls_a_flag, ls_l_flag);
        }
    }
}

void list_files(char *each_ls_path, int ls_a_flag, int ls_l_flag)
{

    count++;
    DIR *dir_ptr;
    struct dirent *dir_read;
    dir_ptr = opendir(each_ls_path);
    if (dir_ptr == NULL)
    {
        perror("Open Dir");
        return;
    }
    //below 2 lines just when 2 or more directories given for ls
    if (dir_count > 1)
        printf("%s:\n", each_ls_path);
    ll sum_1st_line = 0;
    while ((dir_read = readdir(dir_ptr)) != NULL)
    {
        // printf("%d\n", ls_a_flag);
        if (ls_a_flag == 0)
        {
            if ((dir_read->d_name)[0] == '.')
                continue;
        }
        if (ls_l_flag == 1)
        {
            char *file_name = (char *)malloc(1000);
            strcpy(file_name, each_ls_path);
            strcat(file_name, dir_read->d_name);
            // printf("entered here (%s)\n", dir_read->d_name);
            ll blks = display_details(file_name);
            sum_1st_line += blks;
        }
        printf("%s\n", dir_read->d_name);//ths sum_1st_line just aese hi...coz to do hai ki this total sum / 2 = th first line which we see in ls -l
    }
    if(ls_l_flag == 1)
    {
        printf("total %lld\n", sum_1st_line/2);
    }
    //following if just for printing \n for d-1 times while displaying of various drectories
    if ((dir_count > 1) && (dir_count - count >= 1))
    {
        printf("\n");
    }
}


ll display_details( char *xyz)
{
    struct stat buff;
    if(lstat(xyz, &buff)==-1)
    {
        perror("GONE");
        return 1;
    }
    // struct tm dt;
    printf((S_ISDIR(buff.st_mode)) ? "d" : "");
    printf((S_ISREG(buff.st_mode)) ? "-" : "");
    printf((S_ISLNK(buff.st_mode)) ? "l" : "");
    printf((buff.st_mode & S_IRUSR) ? "r" : "-");
    printf((buff.st_mode & S_IWUSR) ? "w" : "-");
    printf((buff.st_mode & S_IXUSR) ? "x" : "-");
    printf((buff.st_mode & S_IRGRP) ? "r" : "-");
    printf((buff.st_mode & S_IWGRP) ? "w" : "-");
    printf((buff.st_mode & S_IXGRP) ? "x" : "-");
    printf((buff.st_mode & S_IROTH) ? "r" : "-");
    printf((buff.st_mode & S_IWOTH) ? "w" : "-");
    printf((buff.st_mode & S_IXOTH) ? "x" : "-");
    printf("\t");
    printf("%ld\t", buff.st_nlink);
    printf("%s\t", getpwuid(buff.st_uid)->pw_name);
    printf("%s\t", getgrgid(buff.st_gid)->gr_name);

    printf("%ld\t", buff.st_size);
    // char buffer[80];
    // time_t timeStamp = buff.st_atime;
    // printf("%ld\t", timeStamp);
    // localtime(&timeStamp);
    // strftime(buffer, 80, " %h %e\t", &dt);
    // printf("%s\t", buffer);
    // char tM[20];
    // strftime(tm, 20, "%T", localtime(&(buff.st_mtime)));
    // printf("%s\t", tm);

    char timer[14];
    strftime(timer, 14, "%h %d\t%H:%M", localtime(&buff.st_mtime));
    printf("%s ", timer);
    return buff.st_blocks;
}