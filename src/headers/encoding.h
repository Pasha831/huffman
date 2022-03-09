#include <stdio.h>
#include "list.h"
#define ASCII_COUNT 256
#define BYTE 8

#ifndef HUFFMAN_ENCODING_H
#define HUFFMAN_ENCODING_H

typedef union bit2char {
    unsigned char symb;
    struct bit {
        unsigned b1 : 1;
        unsigned b2 : 1;
        unsigned b3 : 1;
        unsigned b4 : 1;
        unsigned b5 : 1;
        unsigned b6 : 1;
        unsigned b7 : 1;
        unsigned b8 : 1;
    }bit;
}bit2char;


void calculateHuffmanCodes(Node *root, char dict[ASCII_COUNT][ASCII_COUNT]);
void encodeFile(FILE* in, FILE* out, const unsigned long long *fileLength, char dict[ASCII_COUNT][ASCII_COUNT]);

#endif //HUFFMAN_ENCODING_H
