#include "decoding.h"
#include "encoding.h"

void decodeFile(FILE *in, FILE *out, Node *root) {
    unsigned char buff[1] = { 0 };
    int i = 0;
    fseek(in, -1L, SEEK_END);
    unsigned long long length = ftell(in);
    int tail = fgetc(in);
    fseek(in, 0L, SEEK_SET);
    bit2char symb;
    int countDown = BYTE;
    fread(buff, 1, 1, in);
    symb.symb = buff[0];
    while (i < length && !((i == length - 1) && countDown == tail)) {
        Node *current = root;
        symb.symb = symb.symb >> 1;
        countDown--;
        if (countDown <= 0) {
            fread(buff, 1, 1, in);
            i++;
            symb.symb = buff[0];
            countDown = BYTE;
        }
        while (!current->isSymb) {
            if (symb.bit.b1) {
                current = current->right;
            } else {
                current = current->left;
            }
            symb.symb = symb.symb >> 1;
            countDown--;
            if (countDown <= 0) {
                fread(buff, 1, 1, in);
                i++;
                symb.symb = buff[0];
                countDown = BYTE;
            }
        }
        buff[0] = current->symb;
        fwrite(buff, 1, 1, out);
    }
}