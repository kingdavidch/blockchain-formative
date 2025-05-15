#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdint.h>
#include <time.h>
#include "sha256.h"

// Define the maximum data size for each block
#define MAX_DATA_SIZE 256

// Define the Block structure
typedef struct Block {
    uint32_t index;         // Position in the blockchain
    time_t timestamp;       // When the block was created
    char data[MAX_DATA_SIZE]; // Data stored in the block
    char prev_hash[65];     // Hash of the previous block (hex string)
    char hash[65];          // Hash of this block (hex string)
    uint32_t nonce;         // Nonce for mining (optional for this simulation)
    struct Block* next;     // Pointer to the next block in the chain
} Block;

// Define the Blockchain structure
typedef struct {
    Block* genesis;  // First block in the chain
    Block* latest;   // Most recent block in the chain
    uint32_t size;   // Number of blocks in the chain
} Blockchain;

// Function prototypes
Blockchain* create_blockchain();
void calculate_block_hash(Block* block, char hash_str[65]);
Block* create_new_block(Blockchain* blockchain, const char* data);
int validate_blockchain(Blockchain* blockchain);
void print_blockchain(Blockchain* blockchain);
void free_blockchain(Blockchain* blockchain);

#endif // BLOCKCHAIN_H
