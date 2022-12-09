CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99 
LIBS=-lraylib -lm
OBJS=main.o player.o stars.o estars.o screen_gameplay.o \
	 screen_logo.o screen_title.o screen_ending.o screen_tutorial.o
NAME=strange_glaxy

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIBS)

main.o: main.c state.h screens.h common.h
	$(CC) -c $< $(CFLAGS) $(LIBS) 
 
player.o: player.c common.h state.h
	$(CC) -c $< $(CFLAGS) $(LIBS) 

stars.o: stars.c common.h state.h
	$(CC) -c $< $(CFLAGS) $(LIBS) 

estars.o: estars.c common.h state.h
	$(CC) -c $< $(CFLAGS) $(LIBS) 

screen_gameplay.o: screen_gameplay.c screens.h state.h
	$(CC) -c $< $(CFLAGS) $(LIBS) 

screen_logo.o: screen_logo.c common.h screens.h 
	$(CC) -c $< $(CFLAGS) $(LIBS) 

screen_title.o: screen_title.c common.h screens.h 
	$(CC) -c $< $(CFLAGS) $(LIBS) 

screen_ending.o: screen_ending.c common.h screens.h
	$(CC) -c $< $(CFLAGS) $(LIBS) 

screen_tutorial.o: screen_tutorial.c common.h screens.h
	$(CC) -c $< $(CFLAGS) $(LIBS) 

run: $(NAME)
	./$(NAME)

clean:
	rm $(OBJS) $(NAME)
