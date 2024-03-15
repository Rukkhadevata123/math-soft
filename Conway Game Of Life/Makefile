CC=gcc
CFLAGS=-I.
DEPS = game_of_life.h
OBJ = main.o game_of_life.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

game_of_life: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)