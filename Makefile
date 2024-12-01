CC = g++
CFLAGS = -pedantic-error -std=c++11
SRC = src/card.c src/game.c tests/test_card.c tests/test_game.c  # Includes both card management and game logic test files
INC = -Iinclude
EXEC = test_game


realplayer.o: realplayer.cpp realplayer.h game.h rule.h card.h
	$(CC) $(CFLAGS) -c realplayer.cpp

# Default target to compile the project
all: $(EXEC)

# Link all the source files into the final executable
$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(INC) -o $(EXEC)

# Clean up generated files (e.g., the executable)
clean:
	rm -f $(EXEC)
