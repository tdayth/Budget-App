all : budget commands

CFLAGS = -Wall -g -std=gnu99

budget : budget.c
	gcc -o budget budget.c

commands: commands.o ops.o
	gcc $(CFLAGS) -o commands commands.o ops.o

commands.o: commands.c ops.h
		gcc $(CFLAGS) -c commands.c

ops.o: ops.c ops.h
	gcc $(CFLAGS) -c ops.c

clean:
	rm budget commands *.o
