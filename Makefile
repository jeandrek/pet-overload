CC=	gcc
PROGRAM=overload
OBJECTS=main.o game.o maze.o hud.o sprite.o texture.o
LDFLAGS=-lSDL2 $(DBG$(DEBUG)$(OS))
CFLAGS=	-Wall -W -O2 $(DBG$(DEBUG))
DBG1=	-Og -g -DDEBUG
# Kludge to get it to work optimally on MS Windows:
# Use -mwindows if and only if we are on Windows and
# if this is not a debug build.
DBGWindows_NT=-mwindows

$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(PROGRAM) $(OBJECTS)
