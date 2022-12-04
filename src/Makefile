CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99 
LIBS=-lraylib -lm
OBJS=main.o player.o
NAME=raylib

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIBS)

main.o: main.c main.h common.h
	$(CC) -c $< $(CFLAGS) $(LIBS) 
 
player.o: player.c player.h common.h main.h
	$(CC) -c $< $(CFLAGS) $(LIBS) 

run: $(NAME)
	./$(NAME)

clean:
	rm $(OBJS) $(NAME)
