CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99 
LIBS=-lraylib -lm
OBJS=main.o 
NAME=raylib

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIBS)

main.o: main.c common.h
	$(CC) -c $< $(CFLAGS) $(LIBS) 
 
run: $(NAME)
	./$(NAME)
clean:
	rm $(OBJS) $(NAME)
