# model overgenomen van stackoverflow en heb hierbij mijn eigen elementen in gestoken
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -pedantic -O2
LDFLAGS=-lSDL

OBJECTS=main.o make_matrix.o

all: main

main: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o main $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) main

.PHONY: all clean