CC = gcc
CFLAGS = -Wall -g
SRC = src/card.c tests/test_card.c
INC = -Iinclude
EXEC = test_card

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(INC) -o $(EXEC)

clean:
	rm -f $(EXEC)
