CC             = gcc
CFLAGS         =-Wall -g -lreadline -std=c99
OFILES         = main.o shell_functions.o error_handling.o

all: $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o shimple

main: main.c
	$(CC) $(CFLAGS) -c main.c 

shell_functions: shell_functions.c
	$(CC) $(CFLAGS) -c shell_functions.c

error_handling: error_handling.c
	$(CC) $(CFLAGS) -c error_handling.c

clean:
	rm -rf *.o
