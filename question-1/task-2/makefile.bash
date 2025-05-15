CC = gcc
CFLAGS = -Wall -Wextra -O2

all: blockchain_sim

blockchain_sim: main.c blockchain.c sha256.c blockchain.h sha256.h
	$(CC) $(CFLAGS) -o blockchain_sim main.c blockchain.c sha256.c

clean:
	rm -f blockchain_sim
