#include "../headers/processFile.h"
#include "../headers/list.h"
#include "../headers/encoding.h"
#include "../headers/decoding.h"

int main() {
    File inputFile = initInputFile();
    File outputFile = initOutputFile(&inputFile);

    int freq[ASCII_COUNT] = { 0 };  // counter for each ascii element of file
    clock_t start = clock();  // just to see, how long it takes to encode & decode file

    fillDictionary(inputFile.f, &inputFile.fileLength, freq);

    Node *list = createList(freq);
    createMeta(&outputFile, list);
    list = makeTreeFromList(list);

    char dict[ASCII_COUNT][ASCII_COUNT] = { 0 };
    calculateHuffmanCodes(list, dict);

    encodeFile(inputFile.f, outputFile.f, &inputFile.fileLength, dict);
    fclose(outputFile.f);

    FILE *encoded = fopen(outputFile.fileLocation, "rb");
    FILE *decoded = fopen("new.txt", "wb");

    char metaName[MAX_FILE_SIZE] = { 0 };
    strcpy(metaName, outputFile.rootFolder);
    strcat(metaName, "meta.txt");

    FILE *meta = fopen(metaName, "rt");
    Node* tree = metaToTree(meta);
    decodeFile(encoded, decoded, tree);

    showHappyEnd();
    clock_t end = clock();
    showExecutionTime(&start, &end);
}
