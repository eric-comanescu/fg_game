CC := clang++
CCARGS := -flto -L../lib -I../include -std=c++17
OUT := -O2 -o ../bin/game
MAKE := make

LIST := main.cpp Game.cpp Input.cpp ./states/StateMachine.cpp ./states/StateStack.cpp ./states/game/PlayState.cpp ./states/State.cpp ./entities/GameEntity.cpp ./entities/player/Player.cpp Fight.cpp ./states/player/IdleState.cpp ./states/player/ForwardWalkState.cpp ./states/player/BackwardsWalkState.cpp ./states/player/CrouchState.cpp ./states/player/CrouchBlockState.cpp ./states/player/AttackState.cpp ./states/player/BlockstunState.cpp ./states/player/HitstunState.cpp ./objects/Hitbox.cpp ./objects/Attack.cpp ./services/Animation.cpp ./services/UserInterface.cpp

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	LIBS := -lraylib
else ifeq ($(UNAME_S),Darwin)
	LIBS := -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -lraylib
else
	CC := g++
	CCARGS := -flto -L../lib -I../include -std=c++17
	LIBS := -lraylib -lgdi32 -lwinmm
	OUT := -O2 -o ../bin/game.exe
	MAKE := mingw32-make
endif


.PHONY: all clean deepclean game

all: ../bin ../lib/libraylib.a ../include/raylib.h ../include/rlgl.h ../include/raymath.h game

../bin:
	mkdir ../bin

../lib/libraylib.a:
	cd ../external/raylib/src/; \
	$(MAKE) clean; \
	$(MAKE) PLATFORM=PLATFORM_DESKTOP; \
	mv libraylib.a ../../../lib/;

../include/raylib.h:
	cp ../external/raylib/src/raylib.h ../include/

../include/rlgl.h:
	cp ../external/raylib/src/rlgl.h ../include/

../include/raymath.h:
	cp ../external/raylib/src/raymath.h ../include/

game: $(LIST)
	$(CC) $(CCARGS) $^ $(LIBS) $(OUT)

clean:
	rm -r ../bin

deepclean: clean
	rm ../lib/libraylib.a
	cd ../external/raylib/src/; \
	$(MAKE) clean
