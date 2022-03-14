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

File initInputFile() {
    File file;
    getFileInfo(file.fileLocation, file.rootFolder, file.fileExtension, file.fileName);
    file.f = openFile(file.fileLocation, &file.fileLength);
    return file;
}

void getFileInfo(char *fileLocation, char *rootFolder, char *fileExtension, char *fileName) {
    printf("Insert file location:");
    fgets(fileLocation, MAX_FILE_SIZE, stdin);

    fileLocation[strlen(fileLocation) - 1] = 0;  // delete useless '\n'
    // check for the " character at the beginning and the end of a path
    if (fileLocation[0] == '"') {
        strcpy(fileLocation, fileLocation + 1);
        // fileLocation = fileLocation + 1;
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
    printf("Time spent: %.3f seconds\n", time_spent);
}
