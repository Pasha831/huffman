#ifndef HUFFMAN_PROCESSFILE_H
#define HUFFMAN_PROCESSFILE_H

#include <stdio.h>
#include <stdlib.h>

FILE *openFile(char *fileName, int *length);
void fillDictionary(FILE *fr, const int *length, int *freq);

#endif //HUFFMAN_PROCESSFILE_H
