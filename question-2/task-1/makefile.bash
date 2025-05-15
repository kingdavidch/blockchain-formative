CC = gcc
CFLAGS = -Wall -Wextra -O2

# Check if OpenSSL is available
OPENSSL_AVAILABLE := $(shell pkg-config --exists openssl && echo yes)

ifeq ($(OPENSSL_AVAILABLE),yes)
    # Use OpenSSL for hashing
    LDFLAGS = $(shell pkg-config --libs openssl)
    CFLAGS += $(shell pkg-config --cflags openssl)
    HASH_FILE = hash.c
else
    # Use standalone implementation
    HASH_FILE = hash_standalone.c
    # Create symbolic link to use the standalone implementation
    $(shell ln -sf hash_standalone.c hash.c)
endif

all: block_test

block_test: main.c block.c $(HASH_FILE) block.h hash.h
	$(CC) $(CFLAGS) -o block_test main.c block.c $(HASH_FILE) $(LDFLAGS)

clean:
	rm -f block_test
