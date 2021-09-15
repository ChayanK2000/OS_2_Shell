COMPILER = gcc
CFLAGS = -c -Wall

all: shell

shell: terminal.o ls.o input.o main.o
	$(COMPILER) terminal.o ls.o input.o main.o -o shell

terminal.o: terminal.c
	$(COMPILER) $(CFLAGS) terminal.c

input.o: input.c
	$(COMPILER) $(CFLAGS) input.c

ls.o: ls.c
	$(COMPILER) $(CFLAGS) ls.c

main.o: main.c
	$(COMPILER) $(CFLAGS) main.c

clean:
	rm *.o shell