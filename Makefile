FLAGS = -pedantic-errors -std=c++11
CFLAGS = -Wall

all: game

game: main.o realplayer.o game.o card.o rule.o relay.o game_state.o
	g++ $(FLAGS) main.o realplayer.o game.o card.o rule.o relay.o game_state.o -o game

main.o: main.cpp game_state.h card.h rule.h realplayer.h relay.h
	g++ $(FLAGS) -c main.cpp

realplayer.o: realplayer.cpp realplayer.h game.h rule.h card.h
	g++ $(FLAGS) -c realplayer.cpp

game.o: game.c game.h card.h
	g++ $(FLAGS) -c game.c

card.o: card.c card.h
	g++ $(FLAGS) -c card.c

rule.o: rule.c rule.h
	g++ $(FLAGS) -c rule.c

relay.o: relay.c relay.h
	gcc $(CFLAGS) -c relay.c

game_state.o: game_state.cpp game_state.h card.h rule.h relay.h realplayer.h
	g++ $(FLAGS) -c game_state.cpp

clean:
	rm -f *.o game
