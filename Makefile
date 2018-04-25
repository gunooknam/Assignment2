OBJS = main.c
EXEC = main 
CC = gcc

all : main.c
	$(CC) -o $(EXEC) $(OBJS)

clean :
	rm -rf $(EXEC)

