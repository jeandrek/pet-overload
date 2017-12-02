CC=	gcc
PROGRAM=overload
OBJECTS=main.o game.o sprite.o
LDFLAGS=-lSDL2
CFLAGS=	-Wall -O2

$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(PROGRAM) $(OBJECTS)
