COMPILER = gcc
CFLAGS = -c -Wall

all: shell

shell: manage_path.o terminal.o pinfo.o sys_commands.o built_in_comm.o ls.o piping.o redirect.o input.o command.o main.o signal_execute.o
	$(COMPILER) manage_path.o terminal.o pinfo.o sys_commands.o built_in_comm.o ls.o piping.o redirect.o input.o command.o main.o signal_execute.o -o shell

manage_path.o: manage_path.c
	$(COMPILER) $(CFLAGS) manage_path.c

terminal.o: terminal.c
	$(COMPILER) $(CFLAGS) terminal.c

pinfo.o: pinfo.c
	$(COMPILER) $(CFLAGS) pinfo.c


sys_commands.o: sys_commands.c
	$(COMPILER) $(CFLAGS) sys_commands.c

built_in_comm.o: built_in_comm.c
	$(COMPILER) $(CFLAGS) built_in_comm.c

piping.o: piping.c
	$(COMPILER) $(CFLAGS) piping.c

redirect.o: redirect.c
	$(COMPILER) $(CFLAGS) redirect.c

input.o: input.c
	$(COMPILER) $(CFLAGS) input.c

ls.o: ls.c
	$(COMPILER) $(CFLAGS) ls.c

command.o: command.c
	$(COMPILER) $(CFLAGS) command.c

main.o: main.c
	$(COMPILER) $(CFLAGS) main.c

signal_execute.o: signal_execute.c
	$(COMPILER) $(CFLAGS) signal_execute.c

clean:
	rm *.o shell