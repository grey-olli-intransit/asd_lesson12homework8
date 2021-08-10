#ifndef BINTREE_H
#define BINTREE_H

#define true 1==1
#define false 1==0
typedef int boolean;

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} BinTreeIntNode;

BinTreeIntNode* treeInsert(BinTreeIntNode *t, int data);
void printBinTree(BinTreeIntNode *root);
boolean treeNodeDelete(BinTreeIntNode *root, int key);

#endif // BINTREE_H


