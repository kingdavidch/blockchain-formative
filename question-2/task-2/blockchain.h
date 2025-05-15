#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"

typedef struct BlockchainNode {
    Block *block;
    struct BlockchainNode *next;
} BlockchainNode;

typedef struct {
    BlockchainNode *head;
    BlockchainNode *tail;
} Blockchain;

Blockchain* create_blockchain();
void destroy_blockchain(Blockchain *blockchain);
void add_block(Blockchain *blockchain, const char *data);
int is_blockchain_valid(const Blockchain *blockchain);
void print_blockchain(const Blockchain *blockchain);

#endif // BLOCKCHAIN_H
