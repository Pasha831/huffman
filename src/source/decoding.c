#include "../headers/decoding.h"
#include "../headers/encoding.h"

void getNewByte(FILE *in, int *i, bit2char *symbol, int *countDown) {
    unsigned char buff[1] = { 0 };
    fread(buff, 1, 1, in);  // read new symbol from input file
    (*i)++;  // increase a counter of read bytes
    symbol->symb = buff[0];  // fill the union with new byte
    *countDown = BYTE;  // set a counter of non-processed bits to BYTE = 8
}

void shiftTheBit(bit2char *symbol, int *countDown) {
    symbol->symb = symbol->symb >> 1;
    (*countDown)--;
}

unsigned long long getNumberOfBytes(FILE *in) {
    fseek(in, -1L, SEEK_END);
    return ftell(in);
}

int getSizeOfTail(FILE *in) {
    int tailSize = fgetc(in);
    fseek(in, 0L, SEEK_SET);
    return tailSize;
}

void changeTheDirection(Node **currentNode, bit2char *symbol) {
    if (symbol->bit.b1) {
        *currentNode = (*currentNode)->right;
    } else {
        *currentNode = (*currentNode)->left;
    }
}

void decodeFile(FILE *in, FILE *out, Node *root) {
    unsigned long long numberOfBytes = getNumberOfBytes(in);  // number of Bytes to read
    int tailSize = getSizeOfTail(in);  // size of unnecessary tail of bits at the of the file
    int bitsToRead;  // counter of how many bits we have to process (when we read symbol, it equals 8, then it decreases)
    int i = -1;  // a counter of read bytes (-1 at the start - it's a feature :D)
    bit2char symbol;  // union structure to store at the same place both char and bit representation of a byte symbol

    getNewByte(in, &i, &symbol, &bitsToRead);

    while (i < numberOfBytes && !((i == numberOfBytes - 1) && bitsToRead == tailSize)) {
        Node *currentNode = root;

        if (bitsToRead <= 0) {
            getNewByte(in,&i, &symbol, &bitsToRead);
        }

        while (!currentNode->isSymb) {
            changeTheDirection(&currentNode, &symbol);
            shiftTheBit(&symbol, &bitsToRead);

            if (bitsToRead <= 0) {
                getNewByte(in,&i, &symbol, &bitsToRead);
            }
        }
        fwrite(&currentNode->symb, 1, 1, out);
    }
}