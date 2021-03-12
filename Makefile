FLAGS=-std=c++2a -lfmt -lsfml-window -lsfml-system -lsfml-graphics

MyComputer: source.cpp Player.o Map.o
	g++ $^ -o $@ $(FLAGS) 

Player.o: Player.cpp Player.hpp
	g++ $< -c $(FLAGS)

Map.o: Map.cpp Map.hpp
	g++ $< -c $(FLAGS)

clean:
	rm -f *.o MyComputer