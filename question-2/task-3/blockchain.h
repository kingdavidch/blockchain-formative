#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"
#include "transaction.h"

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
Block* add_block(Blockchain *blockchain);
int add_transaction(Blockchain *blockchain, Transaction *transaction);
int is_blockchain_valid(const Blockchain *blockchain);
void print_blockchain(const Blockchain *blockchain);

#endif // BLOCKCHAIN_H
