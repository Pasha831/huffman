#ifndef HUFFMAN_PROCESSFILE_H
#define HUFFMAN_PROCESSFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#define MAX_FILE_SIZE 1000

typedef struct File {
    FILE *f;
    char fileLocation[MAX_FILE_SIZE];
    char fileName[MAX_FILE_SIZE];
    char fileExtension[MAX_FILE_SIZE];
    char rootFolder[MAX_FILE_SIZE];
    unsigned long long fileLength;
} File;

void showExecutionTime(const clock_t *start, const clock_t *end);
File initInputFile();
File initOutputFile(File *inputFile);
void getFileInfo(char *fileLocation, char *rootFolder, char *fileExtension, char *fileName);
FILE *openFile(char *fileName, unsigned long long *length);
void fillDictionary(FILE *fr, const unsigned long long *length, int *freq);

#endif //HUFFMAN_PROCESSFILE_H
