CC = gcc
CFLAGS = -Wall -g `sdl2-config --cflags`
LIBS = `sdl2-config --libs` -lSDL2_image  # Link SDL2_image for image loading

SRC = src/card.c src/game.c tests/test_card.c tests/test_game.c
INC = -Iinclude
EXEC = test_game

# Default target to compile the project
all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(INC) -o $(EXEC) $(LIBS)

clean:
	rm -f $(EXEC)
