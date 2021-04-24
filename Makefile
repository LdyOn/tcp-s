.PHONY:clean
CC = gcc
CFLAGS = -Wall -g 
OBJ = main.o error.o server.o task.o
vpath %.c src
vpath %.h include

server:$(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
	rm -f  *.o 
#%.o:%.c
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f  *.o 
