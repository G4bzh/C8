CFLAGS = -g -Wall
LDFLAGS = -lncurses

c8: main.o c8.o gfx.o

c8.o: c8.c c8.h

gfx.o: gfx.c gfx.h

main.o: c8.h gfx.h


clean:
	rm -f c8
	rm -f *.o *~ 

