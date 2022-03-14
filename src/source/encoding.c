#include "../headers/encoding.h"
#include <string.h>

void simmetric(const Node *root, char dict[ASCII_COUNT][ASCII_COUNT], char* code, int level)
{
    level++;
    if (root->freq == 0) {  // root->freq == 0 - process tree with only one leaf, where right is empty
        return;
    } else if (root->isSymb) {
        strcpy(dict[root->symb], code);
    } else {
        code[level] = '0';
        simmetric(root->left, dict, code, level);  // move left
        code[level] = '1';
        simmetric(root->right, dict, code, level);  // move right
        code[level] = 0;
    }
    level--;
}


void calculateHuffmanCodes(Node *root, char dict[ASCII_COUNT][ASCII_COUNT]) {
    char code[ASCII_COUNT] = { 0 };
    int level = -1;
    simmetric(root, dict, code, level);
}

void fillTheByte(bit2char *symb, const char *str) {
    symb->bit.b1 = (unsigned)str[0];
    symb->bit.b2 = (unsigned)str[1];
    symb->bit.b3 = (unsigned)str[2];
    symb->bit.b4 = (unsigned)str[3];
    symb->bit.b5 = (unsigned)str[4];
    symb->bit.b6 = (unsigned)str[5];
    symb->bit.b7 = (unsigned)str[6];
    symb->bit.b8 = (unsigned)str[7];
}

void pushMeaninglessZeros(char *str, int *tail) {
    strcat(str, "0");
    (*tail)++;
}

// essentially, it's a "shl" command from assembly :D
void shiftBitsToLeft(char *str) {
    int j = 0;
    while (str[BYTE+j]) {
        str[j] = str[BYTE+j];
        j++;
    }
    str[j] = 0;
}

void loadingBar(unsigned long long *printedBytes, const unsigned long long *readBytes, const unsigned long long *fileLength) {
    char a = 177, b = 219, ret = 13;

    double progress = (((double)*readBytes - (double)*printedBytes) / (double)*fileLength) * 100;
    if ((int)progress >= 1) {
        for (int i = 0; i < (int)progress; i++) {
            printf("%c", b);
            // Sleep(10);
        }
        *printedBytes = *readBytes;
    }
}

void encodeFile(FILE* in, FILE* out, const unsigned long long *fileLength, char dict[ASCII_COUNT][ASCII_COUNT]) {
    unsigned long long readBytes = 0;  // number of already read bytes of a file
    int tail = 0;  // number of meaningless bits in the end of file
    unsigned char buff[1] = { 0 };  // buffer to read single characters
    char str[ASCII_COUNT] = { 0 };  // buffer to store characters
    fseek(in, 0, SEEK_SET);  // return to the start of the file
    unsigned long long printedBytes = 0;

    printf("Compressing...\n");
    while (readBytes < *fileLength || strlen(str) > 0) {
        while (readBytes < *fileLength && strlen(str) < BYTE) {
            fread(buff, 1, 1, in);
            readBytes++;
            strcat(str, dict[buff[0]]);
        }
        while (strlen(str) < BYTE) {  // if we read all bytes, but there is still something in the buffer
            pushMeaninglessZeros(str, &tail);
        }

        bit2char symb;
        fillTheByte(&symb, str);
        fwrite(&symb.symb, 1, 1, out);
        loadingBar(&printedBytes, &readBytes, fileLength);

        shiftBitsToLeft(str);
    }
    buff[0] = (unsigned char)tail;
    fwrite(buff, 1, 1, out);
    printf("\n");
}

