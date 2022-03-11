#include "../headers/list.h"

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
    if (!(head && head->next)) {
        Node *temp = head;  // we store here head temporarily

        // we process both left and right of the tree, so we need an empty right node
        Node *tempRight = (Node *)malloc(sizeof (Node));
        tempRight->freq = 0;
        tempRight->isSymb = 0;
        tempRight->symb = 0;
        tempRight->left = NULL;
        tempRight->right = NULL;
        tempRight->next = NULL;

        // newNode - a node, where we will store our head after creating of a tree with one leaf
        Node *newNode = (Node *)malloc(sizeof (Node));
        newNode->freq = head->freq + 0;
        newNode->isSymb = 0;
        newNode->symb = 0;
        newNode->left = temp;  // our previous head with only 1 element
        newNode->right = tempRight;  // temporary empty right leaf with isSymb = 0
        newNode->next = NULL;
        head = newNode;  // shift a pointer to the start of the tree

        return head;
    }

    while (head && head->next) {
        Node *left = head;
        Node *right = head->next;
        Node *newNode = makeNodeFromNodes(left, right);
        addToTree(&head, newNode);
        head = head->next->next;
    }
    return head;
}