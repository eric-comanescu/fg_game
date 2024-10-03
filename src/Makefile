CCARGS := -L../lib -std=c++17

OUT := -O2 -o ../game

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
