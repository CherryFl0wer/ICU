CC=gcc
EXE=facedetect

CPPFLAGS= `pkg-config --cflags sdl gtk+-2.0`
CFLAGS= -Wall -Wextra -std=c99 -pedantic -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl gtk+-2.0` -lSDL_image


FILES= main.c ./src/ArrayUtils.c ./src/IntegralImage.c

all: main

main:  
	$(CC) $(CFLAGS) $(FILES) -o $(EXE) $(CPPFLAGS) $(LDLIBS)

clean:
	rm -f *~ ./src/*.o
	rm -f $(EXE)
