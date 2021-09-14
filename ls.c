#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
int main()
{
    // char str[100];
    // scanf("%s", &str);
    DIR *dir_ptr;
    struct dirent *dir_read;
    dir_ptr = opendir(".");
    if (dir_ptr == NULL)
    {
        perror("Open Dir");
    }
    while ((dir_read = readdir(dir_ptr)) != NULL)
    {
        printf("%s\n", dir_read->d_name);
    }
    

    
    return 0;
}

// int var = 5;
// int var1 = 9;
// int *ptr;
// ptr = &var;
// printf("%lld %lld %lld %lld\n", ptr, *ptr, &ptr, &var);