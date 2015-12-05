CC=clang

CPPFLAGS= `pkg-config --cflags gtk+-3.0`
CFLAGS= -Wall -Wextra -std=c99 -pedantic -O3 -g
LDFLAGS=
LDLIBS= `pkg-config --libs gtk+-3.0` -lSDL_image -lm

SRC= gtk.c
OBJ= ${SRC:.c=.o}

all: gtk

gtk:${OBJ}  
	$(CC) ${OBJ} ${CFLAGS} ${LDLIBS} -o gtk

clean:
	rm -f *.o *~
	rm -f gtk
