CC=gcc
CPPFLAGS= `pkg-config --cflags sdl gtk+-2.0`
CFLAGS= -std=c99 -pedantic -O3 #-Wall -Wextra -std=c99 -pedantic -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl gtk+-2.0` -lSDL_image
SRC= main.c

all:
	$(CC) $(CFLAGS) $(SRC) -o facedetect $(CPPFLAGS) $(LDLIBS)
clean:
	rm -f *~ *.o
	rm -f facedetect
