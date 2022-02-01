CC = g++
CFLAGS = -Wall -g -std=c++17
PROGS = ex6

all: $(PROGS)

ex6: ex6.o Vector.o
	$(CC) $(CFLAGS) -o $@ $^

ex6.o: ex6.cc Vector.h
	$(CC) $(CFLAGS) -c $^

Vector.o: Vector.cc Vector.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o *~ $(PROGS)
