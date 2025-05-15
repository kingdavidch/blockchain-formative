# Simple Blockchain Persistence in C

This project implements a simplified blockchain with persistence functionality in C, focusing on saving a blockchain to a file and loading it back while ensuring data integrity through hash validation. It is designed as part of an assignment to understand core blockchain data structures.

## Table of Contents
- [Features](#features)
- [Requirements](#requirements)
- [File Structure](#file-structure)
- [Setup and Compilation](#setup-and-compilation)
- [Usage](#usage)
- [Code Overview](#code-overview)
- [Limitations](#limitations)
- [Future Improvements](#future-improvements)

## Features
- Create a blockchain with a genesis block
- Add blocks with transaction data
- Calculate block hashes (simplified, not cryptographic)
- Save the blockchain to a binary file
- Load the blockchain from a file with hash validation
- Free allocated memory to prevent leaks
- Validate block integrity during loading

## Requirements
- C development environment (e.g., GCC, Visual Studio Code with C extension, or any C IDE)
- Basic knowledge of C programming (pointers, structures, dynamic memory, file handling)
- Standard C libraries (`stdio.h`, `stdlib.h`, `string.h`, `time.h`)

## File Structure
- `blockchain.h`: Header file with structure definitions (`Block`, `Blockchain`) and function prototypes
- `blockchain.c`: Implementation of blockchain functions (create, add, save, load, validate)
- `main.c`: Demonstration program that creates, saves, and loads a blockchain
- `README.md`: This documentation file

## Setup and Compilation
1. Ensure you have a C compiler installed (e.g., GCC).
2. Save all source files (`blockchain.h`, `blockchain.c`, `main.c`) in the same directory.
3. Compile the program using:
   ```bash
   gcc -o blockchain main.c blockchain.c
   ```
4. Run the executable:
   ```bash
   ./blockchain
   ```

## Usage
The `main.c` file includes a demo that:
1. Creates a blockchain with a genesis block
2. Adds two transaction blocks ("First transaction" and "Second transaction")
3. Prints the original blockchain
4. Saves the blockchain to `blockchain.dat`
5. Frees the original blockchain
6. Loads the blockchain from `blockchain.dat` and validates it
7. Prints the loaded blockchain

Example output:
```
Original Blockchain:
Block 0: Genesis Block (Hash: 4a5e1e4..., Prev: 0)
Block 1: First transaction (Hash: 7b9f2c8..., Prev: 4a5e1e4...)
Block 2: Second transaction (Hash: 9c3d5a7..., Prev: 7b9f2c8...)

Blockchain saved to file

Loaded Blockchain:
Block 0: Genesis Block (Hash: 4a5e1e4..., Prev: 0)
Block 1: First transaction (Hash: 7b9f2c8..., Prev: 4a5e1e4...)
Block 2: Second transaction (Hash: 9c3d5a7..., Prev: 7b9f2c8...)
```

## Code Overview
- **Structures**:
  - `Block`: Stores index, data, previous hash, current hash, timestamp, and pointer to next block
  - `Blockchain`: Contains pointers to genesis and latest blocks
- **Key Functions**:
  - `create_blockchain()`: Initializes a blockchain with a genesis block
  - `create_block()`: Creates a new block with given data and previous hash
  - `calculate_hash()`: Generates a simplified hash (not cryptographic)
  - `validate_block()`: Verifies block integrity by recomputing hash and checking previous hash
  - `add_block()`: Adds a new block to the blockchain
  - `save_blockchain()`: Writes the blockchain to a binary file
  - `load_blockchain()`: Reads the blockchain from a file and validates it
  - `free_blockchain()`: Frees all allocated memory

## Limitations
- Uses a simplified hash function (not cryptographically secure)
- Basic error handling for file operations
- No advanced blockchain features (e.g., proof-of-work, digital signatures)
- Binary file format is simple and not optimized for large blockchains

## Future Improvements
- Implement a cryptographic hash function (e.g., SHA-256)
- Add more robust error handling and input validation
- Support more complex data in blocks (e.g., transactions, smart contracts)
- Implement a more efficient file format for persistence
- Add serialization/deserialization for cross-platform compatibility
