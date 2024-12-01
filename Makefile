FLAGS = -pedantic-errors -std=c++11

all: game

game: main.o AI_Player.o realplayer.o game.o card.o rule.o
	g++ $(FLAGS) main.o AI_Player.o realplayer.o game.o card.o rule.o -o game

main.o: main.cpp game.h card.h realplayer.h rule.h
	g++ $(FLAGS) -c main.cpp

AI_Player.o: AI\ Player.cpp card.h
	g++ $(FLAGS) -c "AI Player.cpp" -o AI_Player.o

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
