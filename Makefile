CFLAGS = -g -Wall
LDFLAGS = -lncurses

c8: main.o c8.o gfx.o inst/do_0x0.o inst/do_0x1.o

c8.o: c8.c c8.h inst/do.h

gfx.o: gfx.c gfx.h

inst/do_0x0.o: inst/do_0x0.c inst/do.h

inst/do_0x1.o: inst/do_0x1.c inst/do.h

main.o: c8.h gfx.h inst/do.h


clean:
	rm -f c8
	rm -f *.o inst/*.o *~ inst/*~

