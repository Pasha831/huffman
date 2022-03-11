#ifndef HUFFMAN_PROCESSFILE_H
#define HUFFMAN_PROCESSFILE_H

#include <stdio.h>
#include <stdlib.h>

FILE *openFile(char *fileName, unsigned long long *length);
void fillDictionary(FILE *fr, const unsigned long long *length, int *freq);

#endif //HUFFMAN_PROCESSFILE_H
