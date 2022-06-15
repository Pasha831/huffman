#include "../headers/processFile.h"
#include "../headers/list.h"
#include "../headers/encoding.h"
#include "../headers/decoding.h"

int main() {
    int action = 0;
    printf("Hello! It's a huffman compressor/decompressor!\n\n");

    do {
        printf("What do you want to do?\n"
               "1. Compress the file\n"
               "2. Decompress the file\n"
               "0. Exit\n"
               "Action:");
        scanf("%d", &action);
        while (getchar() != '\n');  // to clean stdin buffer

        switch (action) {
            case 1: {
                File inputFile = initInputFile();

                int freq[ASCII_COUNT] = { 0 };  // counter for each ascii element of file
                clock_t start = clock();  // just to see, how long it takes to encode & decode file

                fillDictionary(inputFile.f, &inputFile.fileLength, freq);

                Node *list = createList(freq);
                if (!list) {
                    printf("Compressing file is empty!\n");
                    exit(1);
                }
                File outputFile = initOutputFile(&inputFile);
                createMeta(&outputFile, list);
                list = makeTreeFromList(list);

                char dict[ASCII_COUNT][ASCII_COUNT] = { 0 };
                calculateHuffmanCodes(list, dict);

                encodeFile(inputFile.f, outputFile.f, &inputFile.fileLength, dict);
                fclose(outputFile.f);
                fclose(inputFile.f);

                showHappyEnd();
                clock_t end = clock();
                showExecutionTime(&start, &end);
                break;
            }
            case 2: {
                File encoded = openEncodedFile();
                File decoded = initDecodedFile(&encoded);
                File meta = openMetaFile(&encoded);
                Node *tree = metaToTree(meta.f);

                clock_t start = clock();  // let's measure the decoding time!
                decodeFile(encoded.f, decoded.f, tree);
                clock_t end = clock();

                // only for Max <3
                fclose(encoded.f);
                fclose(decoded.f);
                fclose(meta.f);

                showHappyEnd();
                showExecutionTime(&start, &end);

                break;
            }
            case 0:
                printf("\nHave a nice day, goodbye!\n");
                break;
            default:
                printf("\nChoose a correct number!\n\n");
        }
    } while (action);
}
