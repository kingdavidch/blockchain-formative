# SHA-256 Implementation in C

This program implements the SHA-256 hashing algorithm in C for understanding how data integrity is maintained in blockchain systems.

## Files

- `sha256.h` - Header file with function declarations
- `sha256.c` - Implementation of the SHA-256 algorithm
- `main.c` - Driver program that demonstrates usage
- `Makefile` - For compiling the program

## How to Compile

```
make
```

This will create an executable named `sha256_program`.

## How to Run

Default usage:
```
./sha256_program
```
This will hash the default string "Blockchain Cryptography".

With custom input:
```
./sha256_program "Your custom input string"
```

## Implementation Details

The SHA-256 algorithm works as follows:

1. **Message Padding**: The input message is padded to a length that is a multiple of 512 bits.
   - First, a single '1' bit is appended
   - Then '0' bits are appended until the message length is 448 mod 512
   - Finally, a 64-bit representation of the original message length is appended

2. **Message Processing**: The padded message is processed in 512-bit blocks.
   - Each block goes through 64 rounds of operations that mix the data
   - These operations include bitwise functions, modular addition, and bit rotation

3. **Hash Computation**: Through the processing of each block, a 256-bit hash value is built up.
   - The algorithm maintains 8 working variables (a through h)
   - For each block, these variables are initialized with the current hash values
   - After processing a block, these variables are added to the current hash values

4. **Output**: The final result is a 256-bit (32-byte) hash value, typically represented as a 64-character hexadecimal string.

The SHA-256 algorithm is designed to be one-way (cannot be reversed) and collision-resistant (extremely unlikely to find two inputs that generate the same hash).
