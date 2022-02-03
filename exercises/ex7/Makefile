CC = g++
CFLAGS = -Wall -g -std=c++17
PROGS = ex7

all: $(PROGS)

ex7: ex7.o Vector.o
	$(CC) $(CFLAGS) -o $@ $^

ex7.o: ex7.cc Vector.h
	$(CC) $(CFLAGS) -c $^

Vector.o: Vector.cc Vector.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o *~ $(PROGS)