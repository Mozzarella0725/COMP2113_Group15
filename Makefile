FLAGS = -pedantic-errors -std=c++11

realplayer.o: realplayer.cpp realplayer.h game.h rule.h card.h
  g++ $(FLAGS) -c realplayer.cpp
