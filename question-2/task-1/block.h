#ifndef BLOCK_H
#define BLOCK_H

#include <stdint.h>
#include <time.h>

// Define constants
#define HASH_LENGTH 64     // SHA-256 hash represented as hex string (64 chars)
#define MAX_DATA_SIZE 1024 // Maximum size for block data

// Block structure definition
typedef struct Block {
    uint32_t index;                  // Block position in the chain
    time_t timestamp;                // When the block was created
    char data[MAX_DATA_SIZE];        // Block data (could be transactions)
    char prev_hash[HASH_LENGTH + 1]; // Hash of previous block (null-terminated)
    char hash[HASH_LENGTH + 1];      // Hash of this block (null-terminated)
} Block;

// Function prototypes
Block* create_block(uint32_t index, const char* data, const char* prev_hash);
void calculate_hash(Block* block);
void display_block(const Block* block);
void free_block(Block* block);

#endif // BLOCK_H
