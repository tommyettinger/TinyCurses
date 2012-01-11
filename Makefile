CC=gcc
CFLAGS=-Wall -O3 `sdl-config --cflags`
LIBS=`sdl-config --libs` -lSDL_ttf

all: TinyCurses

TinyCurses: TinyCurses.o
        $(CC) -shared $(CFLAGS) $(LIBS) -o TinyCurses.so

