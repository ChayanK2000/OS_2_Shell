#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char *hello = (char *)malloc(1 * sizeof(char));
    printf("%s %ld %ld\n", hello,strlen(hello),sizeof(hello));
    hello = "budd";
    printf("%s %ld %ld %ld", hello, strlen(hello), sizeof(hello), sizeof(char));
    fflush(stdout);
    return 0;
}