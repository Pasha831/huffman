#include <stdio.h>
#include "processFile.h"
#include "list.h"

int main() {
    FILE *fr;
    char inputFileName[] = "input.txt";
    int fileLength;
    int freq[MAX_CHAR] = { 0 };  // counter for each ascii element of file

    fr = openFile(inputFileName, &fileLength);
    fillDictionary(fr, &fileLength, freq);

    Node *list = createList(freq);
    list = makeTreeFromList(list);
}
