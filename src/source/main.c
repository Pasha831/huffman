#include <stdio.h>
#include "../headers/processFile.h"
#include "../headers/list.h"
#include "../headers/encoding.h"
#include "../headers/decoding.h"

int main() {
    FILE *fr;
    char inputFileName[] = "input.txt";
    unsigned long long fileLength;
    int freq[ASCII_COUNT] = { 0 };  // counter for each ascii element of file

    fr = openFile(inputFileName, &fileLength);
    fillDictionary(fr, &fileLength, freq);

    Node *list = createList(freq);
    list = makeTreeFromList(list);

    char dict[ASCII_COUNT][ASCII_COUNT] = { 0 };
    calculateHuffmanCodes(list, dict);

    FILE *fw = fopen("output.txt", "wb");
    encodeFile(fr, fw, &fileLength, dict);
    fclose(fw);

    FILE *encoded = fopen("output.txt", "rb");
    FILE *decoded = fopen("new.txt", "wb");
    decodeFile(encoded, decoded, list);
}
