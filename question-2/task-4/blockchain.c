#include "blockchain.h"

Blockchain* create_blockchain() {
    Blockchain* bc = (Blockchain*)malloc(sizeof(Blockchain));
    bc->genesis_block = create_block("Genesis Block", "0");
    bc->latest_block = bc->genesis_block;
    return bc;
}

Block* create_block(char* data, char* previous_hash) {
    Block* block = (Block*)malloc(sizeof(Block));
    block->index = 0;
    strncpy(block->data, data, DATA_SIZE);
    strncpy(block->previous_hash, previous_hash, HASH_SIZE);
    block->timestamp = time(NULL);
    block->next = NULL;
    calculate_hash(block);
    return block;
}

// Simplified hash calculation (in practice, use SHA-256)
void calculate_hash(Block* block) {
    char input[DATA_SIZE + HASH_SIZE + 20];
    snprintf(input, sizeof(input), "%d%s%ld%s", 
             block->index, block->data, block->timestamp, block->previous_hash);
    
    // Simple hash simulation
    unsigned long hash = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        hash = (hash * 31) + input[i];
    }
    snprintf(block->hash, HASH_SIZE, "%lx", hash);
}

int validate_block(Block* block, Block* prev_block) {
    char temp_hash[HASH_SIZE];
    char input[DATA_SIZE + HASH_SIZE + 20];
    
    snprintf(input, sizeof(input), "%d%s%ld%s", 
             block->index, block->data, block->timestamp, block->previous_hash);
    
    unsigned long hash = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        hash = (hash * 31) + input[i];
    }
    snprintf(temp_hash, HASH_SIZE, "%lx", hash);
    
    return strcmp(temp_hash, block->hash) == 0 && 
           strcmp(block->previous_hash, prev_block->hash) == 0;
}

void add_block(Blockchain* bc, char* data) {
    Block* new_block = create_block(data, bc->latest_block->hash);
    new_block->index = bc->latest_block->index + 1;
    bc->latest_block->next = new_block;
    bc->latest_block = new_block;
}

void save_blockchain(Blockchain* bc, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("Error opening file for writing\n");
        return;
    }

    Block* current = bc->genesis_block;
    int block_count = 0;
    while (current != NULL) {
        block_count++;
        current = current->next;
    }

    fwrite(&block_count, sizeof(int), 1, file);
    
    current = bc->genesis_block;
    while (current != NULL) {
        fwrite(current, sizeof(Block), 1, file);
        current = current->next;
    }

    fclose(file);
}

Blockchain* load_blockchain(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Error opening file for reading\n");
        return NULL;
    }

    Blockchain* bc = (Blockchain*)malloc(sizeof(Blockchain));
    int block_count;
    fread(&block_count, sizeof(int), 1, file);

    Block* prev_block = NULL;
    for (int i = 0; i < block_count; i++) {
        Block* block = (Block*)malloc(sizeof(Block));
        fread(block, sizeof(Block), 1, file);
        block->next = NULL;

        if (i == 0) {
            bc->genesis_block = block;
        } else {
            // Validate block integrity
            if (!validate_block(block, prev_block)) {
                printf("Block %d validation failed\n", block->index);
                free_blockchain(bc);
                fclose(file);
                return NULL;
            }
            prev_block->next = block;
        }
        prev_block = block;
    }
    bc->latest_block = prev_block;

    fclose(file);
    return bc;
}

void free_blockchain(Blockchain* bc) {
    Block* current = bc->genesis_block;
    while (current != NULL) {
        Block* temp = current;
        current = current->next;
        free(temp);
    }
    free(bc);
}
