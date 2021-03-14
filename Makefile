FLAGS=-std=c++2a -lfmt -lsfml-window -lsfml-system -lsfml-graphics

MyComputer: source.cpp Player.o Map.o RegexSearch.o
	g++ $^ -o $@ $(FLAGS) 

Player.o: Player.cpp Player.hpp
	g++ $< -c $(FLAGS)

Map.o: Map.cpp Map.hpp RegexSearch.o
	g++ $< -c $(FLAGS)

RegexSearch.o: RegexSearch.cpp RegexSearch.hpp
	g++ $< -c $(FLAGS)

Sword.o: Sword.cpp Sword.h
	g++ $< -c $(FLAGS)

clean:
	rm -f *.o MyComputer