#include "../headers/processFile.h"
#include "../headers/list.h"
#include "../headers/encoding.h"
#include "../headers/decoding.h"

int main() {
    File inputFile = initInputFile();
    int freq[ASCII_COUNT] = { 0 };  // counter for each ascii element of file
    clock_t start = clock();  // just to see, how long it takes to encode & decode file

    fillDictionary(inputFile.f, &inputFile.fileLength, freq);

    Node *list = createList(freq);
    list = makeTreeFromList(list);

    char dict[ASCII_COUNT][ASCII_COUNT] = { 0 };
    calculateHuffmanCodes(list, dict);

    File outputFile = initOutputFile(&inputFile);
    encodeFile(inputFile.f, outputFile.f, &inputFile.fileLength, dict);

    FILE *encoded = fopen(outputFile.fileLocation, "rb");
    FILE *decoded = fopen("new.txt", "wb");
    decodeFile(encoded, decoded, list);

    clock_t end = clock();
    showExecutionTime(&start, &end);
}
