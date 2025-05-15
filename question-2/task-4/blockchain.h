#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define HASH_SIZE 64
#define DATA_SIZE 256

typedef struct Block {
    int index;
    char data[DATA_SIZE];
    char previous_hash[HASH_SIZE];
    char hash[HASH_SIZE];
    time_t timestamp;
    struct Block* next;
} Block;

typedef struct Blockchain {
    Block* genesis_block;
    Block* latest_block;
} Blockchain;

// Blockchain function prototypes
Blockchain* create_blockchain();
Block* create_block(char* data, char* previous_hash);
void calculate_hash(Block* block);
int validate_block(Block* block, Block* prev_block);
void add_block(Blockchain* bc, char* data);
void save_blockchain(Blockchain* bc, const char* filename);
Blockchain* load_blockchain(const char* filename);
void free_blockchain(Blockchain* bc);

#endif
