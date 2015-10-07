CC=gcc
EXE=facedetect

CPPFLAGS= `pkg-config --cflags sdl gtk+-2.0`
CFLAGS= -Wall -Wextra -std=c99 -pedantic -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl gtk+-2.0` -lSDL_image


FILES= main.c ./src/IntegralImage.c
#OBJ=$(FILES:.c=.o)

all: main

main:  
	$(CC) $(CFLAGS) $(FILES) -o $(EXE) $(CPPFLAGS) $(LDLIBS)

clean:
	rm -f *~ *.o
	rm -f $(EXE)
