CC=	gcc
PROGRAM=overload
OBJECTS=main.o game.o map.o hud.o sprite.o texture.o
LDFLAGS=-lSDL2 $(LF$(DEBUG)$(OS))
CFLAGS=	-Wall -W -Wno-unused-result -O2 $(CF$(DEBUG))
CF1=	-Og -g -DDEBUG
# Kludge to get it to work optimally on MS Windows:
# Use -mwindows if and only if we are on Windows and
# if this is not a debug build.
LFWindows_NT=-mwindows

$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(PROGRAM) $(OBJECTS)
