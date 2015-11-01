CC=gcc
EXE=facedetect

CPPFLAGS= `pkg-config --cflags sdl gtk+-2.0`
CFLAGS= -Wall -Wextra -std=c99 -pedantic -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl gtk+-2.0` -lSDL_image -lm

SRC= main.c ./src/IntegralImage.c ./src/ArrayUtils.c ./src/HaarFeatures.c ./src/SDLPixel.c ./src/Treatment.c ./src/Adaboost.c ./src/Sort.c ./src/Training.c ./src/Utils.c 

all: main

main:  
	$(CC) $(CFLAGS) $(SRC) -o $(EXE) $(CPPFLAGS) $(LDLIBS)

clean:
	rm -f *~ ./src/*.o
	rm -f $(EXE)
