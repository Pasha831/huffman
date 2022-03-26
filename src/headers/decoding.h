#include <stdio.h>
#include "list.h"

#ifndef HUFFMAN_DECODING_H
#define HUFFMAN_DECODING_H

void decodeFile(FILE *in, FILE *out, Node *root);
Node* metaToTree (FILE* meta);

#endif //HUFFMAN_DECODING_H
