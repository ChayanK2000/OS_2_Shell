COMPILER = gcc
CFLAGS = -c -Wall

all: shell

shell: terminal.o built_in_comm.o ls.o input.o main.o
	$(COMPILER) terminal.o built_in_comm.o ls.o input.o main.o -o shell

terminal.o: terminal.c
	$(COMPILER) $(CFLAGS) terminal.c

built_in_comm.o: built_in_comm.c
	$(COMPILER) $(CFLAGS) built_in_comm.c

input.o: input.c
	$(COMPILER) $(CFLAGS) input.c

ls.o: ls.c
	$(COMPILER) $(CFLAGS) ls.c

main.o: main.c
	$(COMPILER) $(CFLAGS) main.c

clean:
	rm *.o shell