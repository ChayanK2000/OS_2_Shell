#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h> //for using command "uname"...not necessary as it gave output as "Linux"
#include "terminal.h"

void display_terminal_names()
{
    // struct utsname *buf;
    char user_name[100];
    getlogin_r(user_name, 100);
    printf("%s", user_name);
    printf("@");
    char host_name[100];
    gethostname(host_name, 100);
    printf("%s:", host_name);
    fflush(stdout);
    
}