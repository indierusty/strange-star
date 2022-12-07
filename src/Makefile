CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99 
LIBS=-lraylib -lm
OBJS=main.o player.o stars.o estars.o
NAME=strange_glaxy

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIBS)

main.o: main.c state.h common.h
	$(CC) -c $< $(CFLAGS) $(LIBS) 
 
player.o: player.c player.h common.h state.h
	$(CC) -c $< $(CFLAGS) $(LIBS) 

stars.o: stars.c stars.h common.h state.h
	$(CC) -c $< $(CFLAGS) $(LIBS) 

estars.o: estars.c estars.h common.h state.h
	$(CC) -c $< $(CFLAGS) $(LIBS) 

run: $(NAME)
	./$(NAME)

clean:
	rm $(OBJS) $(NAME)
