CCARGS := -L../lib -std=c++17

OUT := -O2 ../game

ifeq ($(OS),Windows_NT)
	CC := g++
	LIBS := -lraylib_win -lgdi32 -lwinmm
	OUT += .exe
else
	CC := clang++

	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		LIBS := -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -lraylib_osx
	else
		LIBS := -lraylib_linux
	endif
endif

all: main.cpp
	$(CC) $(CCARGS) $(LIBS) $^ $(OUT)

#all: main.cpp
#	clang++ --library-directory='../lib/' main.cpp -l raylib_linux -o ../game -O2

#win: main.cpp
#	g++ -L../lib -o ../game.exe main.cpp -lraylib_win -lgdi32 -lwinmm -O2

osx: main.cpp
	clang++ -L../lib -std=c++17 $(LIBS) main.cpp -o ../game -O2
