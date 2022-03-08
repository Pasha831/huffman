#include "encoding.h"
#include <string.h>

void simmetric(const Node *root, char dict[ASCII_COUNT][BYTE*BYTE], char* code, int level)
{
    level++;
    if (root->isSymb){
        strcpy(dict[root->symb], code);
    } else {
        code[level] = '0';
        simmetric(root->left, dict, code, level);
        code[level] = '1';
        simmetric(root->right, dict, code, level);
        code[level] = 0;
    }
    level--;
}


void calculateHuffmanCodes(Node *root, char dict[ASCII_COUNT][BYTE*BYTE]) {
    char code[BYTE] = { 0 };
    code[0] = '0';
    int level = 0;
    simmetric(root, dict, code, level);
}


void encodeFile(FILE* in, FILE* out, const unsigned long long *fileLength, char dict[ASCII_COUNT][BYTE*BYTE]) {
    int len = 0;
    int i = 0;
    int tail = 0;  // number of meaningless bits in the end of file
    unsigned char buff[1] = { 0 };
    char str[BYTE*BYTE] = { 0 };
    fseek(in, 0, SEEK_SET);
    while (i < *fileLength || len > 0) {
        while (i < *fileLength && len < BYTE) {
            fread(buff, 1, 1, in);
            i++;
            strcat(str, dict[buff[0]]);
            len += strlen(dict[buff[0]]);
        }
        while (len < BYTE) {
            strcat(str, "0");
            tail++;
            len++;
        }
        bit2char symb;
        symb.bit.b1 = (unsigned)str[0];
        symb.bit.b2 = (unsigned)str[1];
        symb.bit.b3 = (unsigned)str[2];
        symb.bit.b4 = (unsigned)str[3];
        symb.bit.b5 = (unsigned)str[4];
        symb.bit.b6 = (unsigned)str[5];
        symb.bit.b7 = (unsigned)str[6];
        symb.bit.b8 = (unsigned)str[7];
        buff[0] = symb.symb;
        fwrite(buff, 1, 1, out);
        int j = 0;
        while (str[BYTE+j]) {
            str[j] = str[BYTE+j];
            j++;
        }
        len -= BYTE;
        str[j] = 0;
    }
    buff[0] = (unsigned char)tail;
    fwrite(buff, 1, 1, out);
}
