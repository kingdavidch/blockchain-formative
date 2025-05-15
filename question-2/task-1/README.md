# Blockchain Block Structure Implementation

This project implements the fundamental Block structure used in blockchain technology along with functions to create, hash, and display blocks.

## Files in this Project

- `block.h` - Header file defining the Block structure and related functions
- `block.c` - Implementation of Block-related functions
- `hash.h` - Header file for SHA-256 hashing functions
- `hash.c` - Implementation of SHA-256 using OpenSSL
- `hash_standalone.c` - Alternative SHA-256 implementation (no external dependencies)
- `main.c` - Test program that creates and displays blocks
- `Makefile` - For building the project

## Block Structure

The Block structure is defined as follows:

```c
typedef struct Block {
    uint32_t index;                  // Block position in the chain
    time_t timestamp;                // When the block was created
    char data[MAX_DATA_SIZE];        // Block data (could be transactions)
    char prev_hash[HASH_LENGTH + 1]; // Hash of previous block
    char hash[HASH_LENGTH + 1];      // Hash of this block
} Block;
```

## Key Components:

### 1. Block Attributes
- **Index**: The position of the block in the blockchain
- **Timestamp**: When the block was created
- **Data**: Information stored in the block (e.g., transaction details)
- **Previous Hash**: The hash of the preceding block, creating the blockchain link
- **Hash**: The unique identifier for this block, calculated using SHA-256

### 2. Core Functions
- `create_block()`: Creates a new block with specified index, data, and previous hash
- `calculate_hash()`: Computes the SHA-256 hash of a block based on its contents
- `display_block()`: Prints all information in a block in a readable format
- `free_block()`: Properly deallocates memory used by a block

## Building and Running

To compile the program:
```
make
```

To run the test program:
```
./block_test
```

The program will create a genesis block and a second block that links to it, then display both blocks to demonstrate the structure and linking mechanism.

## Dependencies

The project can use either:
- OpenSSL library for SHA-256 hashing (preferred)
- A standalone SHA-256 implementation (used if OpenSSL is not available)

The Makefile will automatically detect and use the appropriate option.
