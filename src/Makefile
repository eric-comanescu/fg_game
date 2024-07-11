all: main.cpp
	clang++ --library-directory='../lib/' main.cpp -l raylib -o ../game -O2

win: main.cpp
	g++ -o ../game.exe main.cpp -lraylib -lgdi32 -lwinmm

rg: ../game
	rm ../game

