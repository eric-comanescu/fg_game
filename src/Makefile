CC := clang++
CCARGS := -flto -L../lib -std=c++17
OUT := -O2 -o ../bin/game

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	LIBS := -lraylib
else ifeq ($(UNAME_S),Darwin)
	LIBS := -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -lraylib
else
	CC := g++
	LIBS := -lraylib -lgdi32 -lwinmm
	OUT := -O2 -o ../bin/game.exe
endif


.PHONY: all clean deepclean game

all: ../bin ../lib/libraylib.a ../include/raylib.h ../include/rlgl.h ../include/raymath.h game

../bin:
	mkdir ../bin

../lib/libraylib.a:
	cd ../external/raylib/src/; \
	make clean; \
	make PLATFORM=PLATFORM_DESKTOP; \
	mv libraylib.a ../../../lib/;

../include/raylib.h:
	cp ../external/raylib/src/raylib.h ../include/

../include/rlgl.h:
	cp ../external/raylib/src/rlgl.h ../include/

../include/raymath.h:
	cp ../external/raylib/src/raymath.h ../include/

game: main.cpp
	$(CC) $(CCARGS) $^ $(LIBS) $(OUT)

clean:
	rm ../lib/libraylib.a
	rm -r ../bin

deepclean: clean
	cd ../external/raylib/src/; \
	make clean

