FLAGS = -pedantic-errors -std=c++11

all: game

game: main.o AIPlayer.o realplayer.o game.o card.o rule.o
	g++ $(FLAGS) main.o AIPlayer.o realplayer.o game.o card.o rule.o -o game

main.o: main.cpp game.h card.h realplayer.h rule.h AIPlayer.h
	g++ $(FLAGS) -c main.cpp

AIPlayer.o: AIPlayer.cpp AIPlayer.h card.h
	g++ $(FLAGS) -c AIPlayer.cpp

realplayer.o: realplayer.cpp realplayer.h game.h rule.h card.h
	g++ $(FLAGS) -c realplayer.cpp

game.o: game.c game.h card.h
	g++ $(FLAGS) -c game.c

card.o: card.c card.h
	g++ $(FLAGS) -c card.c

rule.o: rule.c rule.h
	g++ $(FLAGS) -c rule.c

clean:
	rm -f *.o game
