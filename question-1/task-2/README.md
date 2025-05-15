# Simple Blockchain Simulation in C

This program simulates a basic blockchain to demonstrate how blockchains maintain data integrity through hashing and linking of blocks.

## Files

- `blockchain.h` - Header file with block and blockchain structure definitions
- `blockchain.c` - Implementation of blockchain functions
- `sha256.h` and `sha256.c` - SHA-256 implementation from previous task
- `main.c` - Example program that creates and validates a blockchain
- `Makefile` - For compiling the program

## How to Compile

```
make
```

This will create an executable named `blockchain_sim`.

## How to Run

```
./blockchain_sim
```

The program will:
1. Create a new blockchain with a genesis block
2. Add several blocks with transaction data
3. Print the entire blockchain
4. Validate the blockchain integrity
5. Demonstrate tamper detection by modifying a block and re-validating

## Key Components

### Block Structure

Each block in the blockchain contains:
- **Index**: Position in the chain
- **Timestamp**: When the block was created
- **Data**: Transaction or other data (limited to 256 chars)
- **Previous Hash**: Hash of the previous block
- **Hash**: Hash of this block
- **Nonce**: For mining (not fully implemented in this simulation)

### Blockchain Operations

- **Creating the blockchain**: Initializes a blockchain with a genesis block
- **Adding blocks**: Creates new blocks and adds them to the chain
- **Calculating block hashes**: Uses SHA-256 to generate a unique hash based on block content
- **Validating the chain**: Ensures each block correctly links to the previous one
- **Tamper detection**: Shows how modifying data breaks the chain's integrity

## Understanding Blockchain Integrity

The blockchain maintains integrity through:

1. **Chaining**: Each block contains the hash of the previous block
2. **Hash verification**: Any change to a block's data will change its hash
3. **Full chain validation**: The entire chain is validated before adding new blocks

If someone tries to tamper with data in a block, the hash of that block will change, breaking the link to the next block and invalidating the chain.
