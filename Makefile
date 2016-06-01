CFLAGS = -g -Wall
LDFLAGS = -lncurses

c8: main.o c8.o screen.o

c8.o: c8.c c8.h

screen.o: screen.c screen.h

main.o: c8.h screen.h


clean:
	rm -f c8

