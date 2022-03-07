#include <stdio.h>
#include "processFile.h"

int main() {
    FILE *fr;
    char inputFileName[] = "input.txt";
    int fileLength;
    int freq[256] = { 0 };  // counter for each ascii element of file

    fr = openFile(inputFileName, &fileLength);
    fillDictionary(fr, &fileLength, freq);
}
