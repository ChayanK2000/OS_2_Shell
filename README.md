# OS Assignment 2_1 - Implementing Shell in C
## Chayan Kochar
## 2019114008

---
To execute run the following commands:

1.  ```
    make
    ```
2.  ```
    ./shell
    ```

3. If you want to clear the produced *.o files or the executable 'shell' file, run
    ```
    make clean
    ```

### Structure of files
separate .c and .h files is present for every command/utility. For example: 
- ls.h,ls.c is related to the 'ls' command.
- manage_path.h, manage_path.c is related to shorten the pathname using ~ if necessary.
- terminal.h, terminal.c is just to print the user@hostname and the directory always
- etc etc

Currently the shell has all features like the ls, pinfo,built-ins: echo,cd,pwd. Background process,repeat is not done yet

---


Notes for personal ref apart from the comments already present:

1. In LINUX shell, on entering "ls -lllll" it works behaving juts as ls -l even though -llll is invalid.
But if we have ls -lzzz...it shows as invalid.
Also in linux, ls -l -l is totally fine giving normal ans 1 time  - handled

2. We can have decalarations multiple times but not definitions. Like for example "main.h" is included in many files. suppose main.h has "int zz=5;" this will be a problem. instead if we do "int zz;" its fine - done