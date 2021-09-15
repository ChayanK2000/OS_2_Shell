#include <sys/types.h>
#include <dirent.h>
#include "main.h"
void get_ls_info(char **inside_token,int k);
void list_files(char *ls_path, int ls_a_flag, int ls_l_flag);
// void display_details(char *)
int count; //random var for checking value of dir_count - count