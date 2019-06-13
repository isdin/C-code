CC=clang
CFLAGS=-O3 -Wall
LIBS=-pthread
SRC=src

all: server.out client.out
server.out: server.o
	$(CC) $(CFLAGS) $(LIBS) -o server.out server.o -m32
client.out: client.o string.o
	$(CC) $(CFLAGS) $(LIBS) -o client.out client.o string.o -m32
server.o: $(SRC)/server.c
	$(CC) $(CFLAGS) -c $(SRC)/server.c -m32
string.o: $(SRC)/string.c
	$(CC) $(CFLAGS) -c $(SRC)/string.c -m32
client.o: $(SRC)/client.c
	$(CC) $(CFLAGS) -c $(SRC)/client.c -m32

.PHONY: clean
clean:
	rm -f *.o *.out