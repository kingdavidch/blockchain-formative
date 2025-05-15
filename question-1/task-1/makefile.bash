CC = gcc
CFLAGS = -Wall -Wextra -O2

all: sha256_program

sha256_program: main.c sha256.c sha256.h
	$(CC) $(CFLAGS) -o sha256_program main.c sha256.c

clean:
	rm -f sha256_program
