PROGRAM=overload
OBJECTS=main.o game.o map.o hud.o sprite.o texture.o
LDFLAGS=`sdl2-config --libs`
CFLAGS=	`sdl2-config --cflags` -Wall -W -Wno-unused-result -O2 $(CF$(DEBUG))
CF1=	-Og -g -DDEBUG

$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(PROGRAM) $(OBJECTS)
