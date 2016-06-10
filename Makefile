CFLAGS = -g -Wall
LDFLAGS = -lncurses

c8: main.o c8.o gfx.o inst/do_0x0.o inst/do_0x1.o inst/do_0x2.o inst/do_0x3.o inst/do_0x4.o inst/do_0x5.o inst/do_0x6.o inst/do_0x7.o inst/do_0x8.o inst/do_0x9.o inst/do_0xA.o inst/do_0xB.o inst/do_0xC.o inst/do_0xD.o inst/do_0xE.o

c8.o: c8.c c8.h inst/do.h

gfx.o: gfx.c gfx.h

inst/do_0x0.o: inst/do_0x0.c inst/do.h

inst/do_0x1.o: inst/do_0x1.c inst/do.h

inst/do_0x2.o: inst/do_0x2.c inst/do.h

inst/do_0x3.o: inst/do_0x3.c inst/do.h

inst/do_0x4.o: inst/do_0x4.c inst/do.h

inst/do_0x5.o: inst/do_0x5.c inst/do.h

inst/do_0x6.o: inst/do_0x6.c inst/do.h

inst/do_0x7.o: inst/do_0x7.c inst/do.h

inst/do_0x8.o: inst/do_0x8.c inst/do.h

inst/do_0x9.o: inst/do_0x9.c inst/do.h

inst/do_0xA.o: inst/do_0xA.c inst/do.h

inst/do_0xB.o: inst/do_0xB.c inst/do.h

inst/do_0xC.o: inst/do_0xC.c inst/do.h

inst/do_0xD.o: inst/do_0xD.c inst/do.h

inst/do_0xE.o: inst/do_0xE.c inst/do.h

main.o: c8.h gfx.h inst/do.h

clean:
	rm -f c8
	rm -f *.o inst/*.o *~ inst/*~

