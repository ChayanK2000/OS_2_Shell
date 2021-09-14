COMPILER = gcc
CFLAGS = -c -Wall

all: shell

shell: terminal.o main.o
	$(COMPILER) terminal.o main.o -o shell

terminal.o: terminal.c
	$(COMPILER) $(CFLAGS) terminal.c

main.o: main.c
	$(COMPILER) $(CFLAGS) main.c

clean:
	rm *.o shell