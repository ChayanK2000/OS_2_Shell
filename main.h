
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h> // for malloc in main.c
// int zz ; //readme pt 2
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef long long ll;
char cur_home[1000];
int len_home;
int cd_count;
int background_pids[200];
int no_of_backgroundprocess;
