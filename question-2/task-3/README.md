# Blockchain with Transactions Implementation in C

## Overview

This project extends a basic blockchain implementation to include transaction support, demonstrating how real blockchain systems track and validate transactions within blocks. The implementation maintains all core blockchain properties while adding transaction handling capabilities.

## Key Features

- **Transaction Management**:
  - Create transactions with sender, receiver, amount, and timestamp
  - Add transactions to blocks
  - Automatic block creation when transaction threshold is reached

- **Blockchain Integrity**:
  - SHA-256 cryptographic hashing of all transaction data
  - Chain validation that includes transaction verification
  - Genesis block initialization

- **Memory Management**:
  - Proper allocation/deallocation of all structures
  - Transaction data cleanup

## File Structure

```
blockchain-c/
├── transaction.h       # Transaction structure and interface
├── transaction.c       # Transaction implementation
├── block.h            # Block structure and interface (updated)
├── block.c            # Block implementation (updated)
├── blockchain.h       # Blockchain structure and interface (updated)
├── blockchain.c       # Blockchain implementation (updated)
├── sha256.h           # SHA-256 hashing interface
├── sha256.c           # SHA-256 implementation (using OpenSSL)
├── main.c             # Updated demonstration program
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
gcc -c transaction.c block.c blockchain.c sha256.c main.c
gcc transaction.o block.o blockchain.o sha256.o main.o -o blockchain -lcrypto
```

Run the program:
```bash
./blockchain
```

## Usage Example

The `main.c` file demonstrates the transaction functionality:

```c
#include "blockchain.h"
#include <stdio.h>

int main() {
    // Create blockchain
    Blockchain *blockchain = create_blockchain();
    
    // Create and add transactions
    add_transaction(blockchain, create_transaction("Alice", "Bob", 1.5));
    add_transaction(blockchain, create_transaction("Bob", "Charlie", 0.7));
    add_transaction(blockchain, create_transaction("Charlie", "Alice", 2.1));
    add_transaction(blockchain, create_transaction("Dave", "Eve", 3.0));
    
    // Print and validate blockchain
    print_blockchain(blockchain);
    printf("Blockchain valid: %s\n", 
           is_blockchain_valid(blockchain) ? "Yes" : "No");
    
    // Clean up
    destroy_blockchain(blockchain);
    return 0;
}
```

## API Documentation

### Transaction Functions

- `Transaction* create_transaction(sender, receiver, amount)`
  - Creates a new transaction
- `void destroy_transaction(transaction)`
  - Frees transaction memory
- `void print_transaction(transaction)`
  - Prints transaction details
- `char* transaction_to_string(transaction)`
  - Serializes transaction for hashing

### Block Functions (Updated)

- `Block* create_block(index, previous_hash)`
  - Creates a new empty block
- `void destroy_block(block)`
  - Frees block and all transactions
- `int add_transaction_to_block(block, transaction)`
  - Adds transaction to a block (returns success status)
- `void calculate_hash(block)`
  - Computes hash including all transactions

### Blockchain Functions (Updated)

- `Block* add_block(blockchain)`
  - Adds new empty block to chain
- `int add_transaction(blockchain, transaction)`
  - Adds transaction to most recent block (creates new block if needed)
- `int is_blockchain_valid(blockchain)`
  - Validates entire chain including transactions
- `void print_blockchain(blockchain)`
  - Prints entire chain with transaction details

## Transaction Rules

1. Each block holds up to 3 transactions (configurable)
2. Exceeding the limit automatically creates a new block
3. All transactions are included in block hash calculations
4. Transactions cannot be modified after being added to a block

## Validation Checks

The blockchain validation performs these checks:
1. Verifies genesis block properties
2. Checks hash chain integrity
3. Validates each block's hash includes all transactions
4. Ensures no transaction tampering occurred

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Future Enhancements

- Transaction signatures/authentication
- Merkle trees for transaction hashing
- Dynamic transaction limits per block
- Transaction fee support
- Network propagation of transactions
- UTXO (Unspent Transaction Output) model
- Wallet address support

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any:
- Bug fixes
- Security improvements
- Performance enhancements
- New features
- Documentation updates
