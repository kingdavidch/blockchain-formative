#ifndef BLOCK_H
#define BLOCK_H

#include <time.h>

typedef struct {
    unsigned int index;
    time_t timestamp;
    char *data;
    char *previous_hash;
    char *hash;
} Block;

Block* create_block(unsigned int index, const char *data, const char *previous_hash);
void destroy_block(Block *block);
void calculate_hash(Block *block);
void print_block(const Block *block);

#endif // BLOCK_H
