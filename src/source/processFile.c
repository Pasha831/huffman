#include "../headers/processFile.h"

FILE *openFile(char *fileName, unsigned long long *length) {
    FILE *fr = fopen(fileName, "rb");
    if (!fr) {
        printf("Can't open the file!\n");
        exit(1);
    }
    fseek(fr, 0L, SEEK_END);
    *length = ftell(fr);
    fseek(fr, 0, SEEK_SET);
    return fr;
}

void fillDictionary(FILE *fr, const unsigned long long *length, int *freq) {
    for (int i = 0; i < *length; i++) {
        freq[(unsigned char) fgetc(fr)]++;
    }
}
