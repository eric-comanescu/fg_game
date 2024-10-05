CC := clang++
CCARGS := -L../lib -std=c++17
OUT := -O2 -o ../game

UNAME_S := $(shell uname -s)

# ifdef OS
# 	CC := g++
# 	LIBS := -lraylib_win -lgdi32 -lwinmm
# 	OUT := -O2 -o ../game.exe
# else
# 	CC := clang++

# 	UNAME_S := $(shell uname -s)
# 	ifeq ($(UNAME_S),Darwin)
# 		LIBS := -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -lraylib_osx
# 	else
# 		LIBS := -lraylib_linux
# 	endif
# endif

ifeq ($(UNAME_S),Linux)
	LIBS := -lraylib_linux
else ifeq ($(UNAME_S),Darwin)
	LIBS := -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -lraylib_osx
else
	CC := g++
	LIBS := -lraylib_win -lgdi32 -lwinmm
	OUT := -O2 -o ../game.exe
endif

all: main.cpp
	$(CC) $(CCARGS) $^ $(LIBS) $(OUT)

clean:
	rm ../game
