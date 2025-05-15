#include "blockchain.h"

int main() {
    // Create and populate blockchain
    Blockchain* bc = create_blockchain();
    add_block(bc, "First transaction");
    add_block(bc, "Second transaction");

    // Print original blockchain
    printf("Original Blockchain:\n");
    Block* current = bc->genesis_block;
    while (current != NULL) {
        printf("Block %d: %s (Hash: %s, Prev: %s)\n", 
               current->index, current->data, current->hash, current->previous_hash);
        current = current->next;
    }

    // Save blockchain to file
    save_blockchain(bc, "blockchain.dat");
    printf("\nBlockchain saved to file\n");

    // Free original blockchain
    free_blockchain(bc);

    // Load blockchain from file
    Blockchain* loaded_bc = load_blockchain("blockchain.dat");
    if (loaded_bc) {
        printf("\nLoaded Blockchain:\n");
        current = loaded_bc->genesis_block;
        while (current != NULL) {
            printf("Block %d: %s (Hash: %s, Prev: %s)\n", 
                   current->index, current->data, current->hash, current->previous_hash);
            current = current->next;
        }
        free_blockchain(loaded_bc);
    }

    return 0;
}
