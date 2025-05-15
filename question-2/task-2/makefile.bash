gcc -c block.c
gcc -c blockchain.c
gcc -c sha256.c
gcc -c main.c
gcc block.o blockchain.o sha256.o main.o -o blockchain -lcrypto
./blockchain
