CC=gcc
CFLAGS= -Wall -Wextra -std=c99 -pedantic -O3
GTKFLAGS= `pkg-config --libs --cflags gtk+-2.0`
SDLFLAGS= `sdl2-config --cflags`
LIBS= `sdl2-config --libs`

#temporary
gtkall:
	$(CC) maingtk-example.c -o gtkexe $(CFLAGS) $(GTKFLAGS)
sdlall:
	$(CC) $(CFLAGS) mainsdl-example.c -o sdlexe $(SDLFLAGS) $(LIBS)
