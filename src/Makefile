CCARGS := -L../lib -std=c++17

OUT := -O2 -o ../bin/game

ifeq ($(OS),Windows_NT)
	CC := g++
	LIBS := -lraylib -lgdi32 -lwinmm
	OUT := -O2 -o ../game.exe
else
	CC := clang++

	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		LIBS := -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -lraylib
	else
		LIBS := -lraylib
	endif
endif

.DELETE_ON_ERROR:
all: main.cpp ../bin/ ../lib/libraylib.a
	$(CC) $(CCARGS) $(LIBS) $^ $(OUT)

.PHONY: clean
clean:
	rm -r ../bin

../bin/:
	mkdir ../bin/

../lib/libraylib.a:
	cd ../external/raylib/src/ ; make PLATFORM=DESKTOP
	mv ../external/raylib/src/libraylib.a ../lib/libraylib.a

