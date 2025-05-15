# Blockchain Implementation in C

## Overview

This project implements a simplified blockchain data structure in C. It demonstrates the core concepts of blockchain technology including block creation, cryptographic hashing, and chain validation.

## Features

- Block creation with index, timestamp, data, previous hash, and current hash
- SHA-256 cryptographic hashing for block integrity
- Linked list implementation for the blockchain
- Blockchain validation to ensure data integrity
- Genesis block creation
- Memory management for all blockchain components

## File Structure

```
blockchain-c/
├── block.h            # Block structure and interface
├── block.c            # Block implementation
├── blockchain.h       # Blockchain structure and interface
├── blockchain.c       # Blockchain implementation
├── sha256.h           # SHA-256 hashing interface
├── sha256.c           # SHA-256 implementation (using OpenSSL)
├── main.c             # Demonstration program
└── README.md          # This file
```

## Requirements

- C compiler (GCC recommended)
- OpenSSL development libraries
- Basic C development environment

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/blockchain-c.git
   cd blockchain-c
   ```

2. Install OpenSSL (if not already installed):
   - On Ubuntu/Debian:
     ```bash
     sudo apt-get install libssl-dev
     ```
   - On macOS (using Homebrew):
     ```bash
     brew install openssl
     ```

## Compilation and Execution

Compile the project:
```bash
gcc -c block.c
gcc -c blockchain.c
gcc -c sha256.c
gcc -c main.c
gcc block.o blockchain.o sha256.o main.o -o blockchain -lcrypto
```

Run the program:
```bash
./blockchain
```

## Usage Example

The `main.c` file demonstrates basic usage:

```c
#include "blockchain.h"
#include <stdio.h>

int main() {
    // Create a new blockchain
    Blockchain *blockchain = create_blockchain();
    
    // Add some blocks
    add_block(blockchain, "First Transaction");
    add_block(blockchain, "Second Transaction");
    add_block(blockchain, "Third Transaction");
    
    // Print the blockchain
    print_blockchain(blockchain);
    
    // Validate the blockchain
    if (is_blockchain_valid(blockchain)) {
        printf("\nBlockchain validation successful!\n");
    } else {
        printf("\nBlockchain validation failed!\n");
    }
    
    // Clean up
    destroy_blockchain(blockchain);
    
    return 0;
}
```

## API Documentation

### Block Functions

- `Block* create_block(unsigned int index, const char *data, const char *previous_hash)`
  - Creates a new block with the given parameters
- `void destroy_block(Block *block)`
  - Frees all memory associated with a block
- `void calculate_hash(Block *block)`
  - Computes the SHA-256 hash for the block
- `void print_block(const Block *block)`
  - Prints block information to stdout

### Blockchain Functions

- `Blockchain* create_blockchain()`
  - Creates a new blockchain with a genesis block
- `void destroy_blockchain(Blockchain *blockchain)`
  - Frees all memory associated with the blockchain
- `void add_block(Blockchain *blockchain, const char *data)`
  - Adds a new block to the blockchain with the given data
- `int is_blockchain_valid(const Blockchain *blockchain)`
  - Validates the integrity of the blockchain (returns 1 if valid)
- `void print_blockchain(const Blockchain *blockchain)`
  - Prints the entire blockchain to stdout

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Future Improvements

- Add proof-of-work mechanism
- Implement peer-to-peer networking
- Add transaction handling
- Improve error handling
- Add persistence (file storage)
- Implement consensus algorithms

## Contributing

Contributions are welcome! Please open an issue or submit a pull request.
