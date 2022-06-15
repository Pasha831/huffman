#include "../headers/processFile.h"

FILE *openFile(char *fileName, unsigned long long *length) {
    FILE *fr = fopen(fileName, "rb");
    if (!fr) {
        printf("Can't open the file to encode!\n");
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

File initInputFile() {
    File file;
    getFileInfo(file.fileLocation, file.rootFolder, file.fileExtension, file.fileName);
    file.f = openFile(file.fileLocation, &file.fileLength);
    return file;
}

void getFileInfo(char *fileLocation, char *rootFolder, char *fileExtension, char *fileName) {
    printf("\nInsert file location:");
    fgets(fileLocation, MAX_FILE_SIZE, stdin);

    fileLocation[strlen(fileLocation) - 1] = 0;  // delete useless '\n'
    // check for the " character at the beginning and the end of a path
    if (fileLocation[0] == '"') {
        strcpy(fileLocation, fileLocation + 1);
    }
    if (fileLocation[strlen(fileLocation) - 1] == '"') {
        fileLocation[strlen(fileLocation) - 1] = 0;
    }

    strcat(rootFolder, fileLocation);
    for (int i = (int)strlen(rootFolder) - 1; i >= 0; i--) {
        if (rootFolder[i - 1] == '\\') {
            rootFolder[i] = 0;
            strcpy(fileName, fileLocation + i);
            for (int j = 0; j < (int)strlen(fileName); j++) {
                if (fileName[j] == '.') {
                    fileName[j] = 0;
                }
            }
            break;
        }
    }

    for (int i = 0; i < strlen(fileLocation); i++) {
        if (fileLocation[i] == '.') {
            strcpy(fileExtension, rootFolder + i);
            return;
        }
    }
}

File initOutputFile(File *inputFile) {
    File outputFile = *inputFile;
    strcat(outputFile.fileName, "_compressed");

    strcat(outputFile.rootFolder, outputFile.fileName);
    strcat(outputFile.rootFolder, "(");
    strcat(outputFile.rootFolder, outputFile.fileExtension);  // to store an extension of file not in meta :)
    strcat(outputFile.rootFolder, ")");
    strcat(outputFile.rootFolder, "\\");
    printf("Creating \"%s\" folder...\n", outputFile.fileName);
    mkdir(outputFile.rootFolder);

    strcpy(outputFile.fileLocation, outputFile.rootFolder);
    strcat(outputFile.fileLocation, outputFile.fileName);
    strcat(outputFile.fileLocation, outputFile.fileExtension);

    outputFile.f = fopen(outputFile.fileLocation, "wb");

    return outputFile;
}

void showExecutionTime(const clock_t *start, const clock_t *end) {
    double time_spent = (double)(*end - *start) / CLOCKS_PER_SEC;
    printf("Time spent: %.3f seconds\n\n", time_spent);
}

void showHappyEnd() {
    printf("Done!\n");
}

File openEncodedFile() {
    File encodedFile;

    printf("\nInsert the path to compressed folder:");
    fgets(encodedFile.rootFolder, MAX_FILE_SIZE, stdin);

    // prettify rootFolder string
    encodedFile.rootFolder[strlen(encodedFile.rootFolder) - 1] = 0;
    if (encodedFile.rootFolder[0] == '"') {
        strcpy(encodedFile.rootFolder, encodedFile.rootFolder + 1);
    }
    if (encodedFile.rootFolder[strlen(encodedFile.rootFolder) - 1] == '"') {
        encodedFile.rootFolder[strlen(encodedFile.rootFolder) - 1] = 0;
    }

    // obtain the extension of the file from brackets
    strcpy(encodedFile.fileExtension, encodedFile.rootFolder);
    encodedFile.fileExtension[strlen(encodedFile.fileExtension) - 1] = 0;  // delete extra ")" at the end
    for (int i = strlen(encodedFile.fileExtension) - 1; i >= 0; i--) {
        if (encodedFile.fileExtension[i] == '.') {
            strcpy(encodedFile.fileExtension, encodedFile.fileExtension + i);
            break;
        }
    }

    // obtain the file name from rootFolder string
    strcpy(encodedFile.fileName, encodedFile.rootFolder);
    int canDelete = 1;
    for (int i = strlen(encodedFile.fileName) - 1; i >= 0; i--) {
        if (encodedFile.fileName[i] == '_' && canDelete == 1) {
            encodedFile.fileName[i] = 0;
            canDelete = 0;
        }
        if (encodedFile.fileName[i] == '\\') {
            strcpy(encodedFile.fileName, encodedFile.fileName + i + 1);
            break;
        }
    }

    // create a path to the file
    strcpy(encodedFile.fileLocation, encodedFile.rootFolder);
    strcat(encodedFile.fileLocation, "\\");
    strcat(encodedFile.fileLocation, encodedFile.fileName);
    strcat(encodedFile.fileLocation, "_compressed");
    strcat(encodedFile.fileLocation, encodedFile.fileExtension);

    // open encoded file
    encodedFile.f = fopen(encodedFile.fileLocation, "rb");
    if (!encodedFile.f) {  // show an error, if there is something wrong
        printf("Can't open the encoded file!\n");
        exit(1);
    }

    return encodedFile;
}

File initDecodedFile(File *encoded) {
    File decoded = *encoded;

    // obtain a father folder of the compressed file
    for (int i = strlen(decoded.rootFolder) - 1; i >= 0; i--) {
        if (decoded.rootFolder[i - 1] == '\\') {
            decoded.rootFolder[i] = 0;
            break;
        }
    }

    // create a path to the decoded file
    strcpy(decoded.fileLocation, decoded.rootFolder);
    strcat(decoded.fileLocation, decoded.fileName);
    strcat(decoded.fileLocation, decoded.fileExtension);

    decoded.f = fopen(decoded.fileLocation, "wb");
    if (!decoded.f) {
        printf("Can't open the decoded file!\n");
        exit(1);
    }

    return decoded;
}

File openMetaFile(File *encoded) {
    File meta = *encoded;

    // change the extension to .txt
    strcpy(meta.fileExtension, ".txt");

    // change a name of the file to meta
    strcpy(meta.fileName, "meta");

    // create a path to the meta.txt file
    strcpy(meta.fileLocation, meta.rootFolder);
    strcat(meta.fileLocation, "\\");
    strcat(meta.fileLocation, meta.fileName);
    strcat(meta.fileLocation, meta.fileExtension);

    meta.f = fopen(meta.fileLocation, "rb");
    if (!meta.f) {
        printf("Can't open meta.txt file!\n");
        exit(1);
    }

    return meta;
}