CC=	gcc
PROGRAM=overload
OBJECTS=main.o game.o sprite.o texture.o
LDFLAGS=-lSDL2
CFLAGS=	-Wall -W -O2

$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(PROGRAM) $(OBJECTS)
