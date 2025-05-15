#ifndef BLOCK_H
#define BLOCK_H

#include <time.h>
#include "transaction.h"

typedef struct {
    unsigned int index;
    time_t timestamp;
    Transaction **transactions;
    unsigned int transaction_count;
    char *previous_hash;
    char *hash;
} Block;

Block* create_block(unsigned int index, const char *previous_hash);
void destroy_block(Block *block);
void calculate_hash(Block *block);
void print_block(const Block *block);
int add_transaction_to_block(Block *block, Transaction *transaction);

#endif // BLOCK_H
