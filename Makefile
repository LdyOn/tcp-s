.PHONY:clean
CC = gcc
CFLAGS = -Wall -g 
OBJ = main.o error.o server.o task.o log.o
vpath %.c src
vpath %.h include

qserver:$(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
	@echo "清理中间文件"
	@rm -f  *.o 
	@mv qserver  bin/
	@echo "编译完成"
#%.o:%.c
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f  *.o 
	@echo "clean complete"
