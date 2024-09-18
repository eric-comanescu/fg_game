all: main.cpp
	clang++ --library-directory='../lib/' main.cpp -l raylib_linux -o ../game -O2

win: main.cpp
	g++ -L../lib -o ../game.exe main.cpp -lraylib_win -lgdi32 -lwinmm -O2

osx: main.cpp
	clang++ -L../lib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -lraylib_osx main.cpp -o ../game -O2 -std=c++17
