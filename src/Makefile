all: main.cpp
	clang++ --library-directory='../lib/' main.cpp -l raylib -o ../game -O2

win: main.cpp
	g++ -L../lib -o ../game.exe main.cpp -lraylib_win -lgdi32 -lwinmm -O2

rg: ../game
	rm ../game

