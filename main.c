#include <stdio.h>
#include "processFile.h"
#include "list.h"
#include "encoding.h"
#include "decoding.h"

int main() {
    FILE *fr;
    char inputFileName[] = "input.txt";
    unsigned long long fileLength;
    int freq[MAX_CHAR] = { 0 };  // counter for each ascii element of file

    fr = openFile(inputFileName, &fileLength);
    fillDictionary(fr, &fileLength, freq);

    Node *list = createList(freq);
    list = makeTreeFromList(list);

    char dict[ASCII_COUNT][BYTE*BYTE] = { 0 };
    calculateHuffmanCodes(list, dict);

    FILE *fw = fopen("output.txt", "wb");
    encodeFile(fr, fw, &fileLength, dict);
    fclose(fw);

    FILE *encoded = fopen("output.txt", "rb");
    FILE *decoded = fopen("new.txt", "wb");
    decodeFile(encoded, decoded, list);
}
