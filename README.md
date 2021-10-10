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

3. piping and dup2 combine is hell lot confusng....wrote in the comments in .c files
4. I observed that always the rightmost arg is taken into account in case of multiple redirections(same direction)
So : cat <a.txt<b.txt<c.txt = cat < c.txt
    echo 1234 > a.txt>b.txt>c.txt = echo>c.txt - with a.txt and b.txt getting erased
    But this was not told in the question to implement multiple, henceleft it half way.

5. say a var insidetoken is a string or array of strings. then even if its correct that insidetoke[x] = NULL, printf("%s\n", inside_token[k]); - would give segmentation fault.
Interestingly, adding some other strings before this value correctly prints NULL : printf("4. %s\n", inside_token[k]);

6. Whenevr waiting for child, use waitpid with the particluar pid. using wait(NULL) can have drastic consequences as we are recursively forking in some cases and using  wait(NULL) can be disasterous. Details witten in sys_commands.c as comments. - still cat a.txt & not working prperly !! iDK why!!
EDIT: Even in terminal it behaves wierdly. This consumed hell lot of time for no reason!

7. cat has a total different legacy. giving hell lot of problems. cat & doesnt work properly.
