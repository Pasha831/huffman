#include "list.h"

void addToList(Node **pphead, int freq, char symb) {
    while (*pphead) {
        if ((*pphead)->freq > freq) {
            break;
        }
        pphead = &((*pphead)->next);
    }
    Node *pnew = (Node *)malloc(sizeof(Node));
    pnew->symb = symb;
    pnew->isSymb = 1;
    pnew->freq = freq;
    pnew->left = pnew->right = NULL;
    pnew->next = *pphead;
    *pphead = pnew;
}

void addToTree(Node **pphead, Node *newNode) {
    while (*pphead) {
        if ((*pphead)->freq > newNode->freq) {
            break;
        }
        pphead = &((*pphead)->next);
    }
    newNode->next = *pphead;
    *pphead = newNode;
}

Node *createList(int *freq) {
    Node *list = NULL;
    for (int i = 0; i < 256; i++) {
        if (freq[i] != 0) {
            addToList(&list, freq[i], (char)i);  // i - ascii code of symbol
        }
    }
    return list;
}

Node *makeNodeFromNodes(Node *left, Node *right) {
    Node *res = (Node *)malloc(sizeof (Node));
    res->freq = left->freq + right->freq;
    res->isSymb = 0;
    res->symb = 0;
    res->left = left;
    res->right = right;
    res->next = NULL;
    return res;
}

Node *makeTreeFromList(Node *head) {
    while (head && head->next) {
        Node *left = head;
        Node *right = head->next;
        Node *newNode = makeNodeFromNodes(left, right);
        addToTree(&head, newNode);
        head = head->next->next;
    }
    return head;
}