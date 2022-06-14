#ifndef HUFFMAN_LIST_H
#define HUFFMAN_LIST_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    unsigned char symb;
    unsigned char isSymb;
    unsigned int freq;
    struct Node *left, *right, *next;
} Node;

void addToList(Node **pphead, int value, char symb);
void addToTree(Node **pphead, Node *newNode);
Node *createList(int *freq);
Node *makeNodeFromNodes(Node *left, Node *right);
Node *makeTreeFromList(Node *head);

#endif //HUFFMAN_LIST_H
