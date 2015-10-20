CC=gcc
EXE=facedetect

CPPFLAGS= `pkg-config --cflags sdl gtk+-2.0`
CFLAGS= -Wall -Wextra -std=c99 -pedantic -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl gtk+-2.0` -lSDL_image

SRC= main.c ./src/IntegralImage.c ./src/ArrayUtils.c ./src/HaarFeatures.c

all: main

main:  
	$(CC) $(CFLAGS) $(SRC) -o $(EXE) $(CPPFLAGS) $(LDLIBS)

clean:
	rm -f *~ ./src/*.o
	rm -f $(EXE)
