#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

FILE * file;
FILE * file1;

// из-за нехватки времени функции написаны на основе того, что давали на уроках, а не свои - на обе домашние работы по 
// 4 задачи у меня было всего два дня.
BinTreeIntNode* getSuccessor(BinTreeIntNode *node) {
    BinTreeIntNode *current = node->right;
    BinTreeIntNode *parent = node;
    BinTreeIntNode *s = node;

    while (current != NULL) {
        parent = s;
        s = current;
        current = current->left;
    }
    if (s != node->right) {
        parent->left = s->right;
        s->right = node->right;
    }
    return s;
}



boolean treeNodeDelete(BinTreeIntNode *root, int key) {
    BinTreeIntNode *current = root;
    BinTreeIntNode *parent = root;
    boolean isLeftChild = true;

    while (current->key != key) {
        parent = current;
        if (key < current->key) {
            current = current->left;
            isLeftChild = true;
        } else {
            current = current->right;
            isLeftChild = false;
        }
        if (current == NULL)
            return false;
    }

    if (current->left == NULL && current->right == NULL) {
        if (current == root)
            root = NULL;
        else if (isLeftChild)
            parent->left = NULL;
        else
            parent->right = NULL;
    }
    else if (current->right == NULL) {
        if (isLeftChild)
            parent->left = current->left;
        else
            parent->right = current->left;
    }
    else if (current->left == NULL) {
        if (isLeftChild)
            parent->left = current->right;
        else
            parent->right = current->right;
    }
    else {
        BinTreeIntNode *successor = getSuccessor(current);
        if (current == root)
            root = successor;
        else if (isLeftChild)
            parent->left = successor;
        else
            parent->right = successor;
        successor->left = current->left;
    }
    return true;
}

void printBinTree(BinTreeIntNode *root) {
    if (root) {
        printf("%d", root->key);
        if (root->left || root->right) {
            printf("(");
            if (root->left)
                printBinTree(root->left);
            else
                printf("NULL");
            printf(",");
            if (root->right)
                printBinTree(root->right);
            else
                printf("NULL");
            printf(")");
        }
    }
}


BinTreeIntNode* treeInsert(BinTreeIntNode *t, int data) {
    BinTreeIntNode *newNode;
    newNode = (BinTreeIntNode*) malloc(sizeof(BinTreeIntNode));
    newNode->key = data;
    newNode->left = NULL;
    newNode->right = NULL;
    BinTreeIntNode *current = t;
    BinTreeIntNode *parent = t;
    if (t == NULL) {
        t = newNode;
    } else {
        while (current->key != data) {
            parent = current;
            if (current->key > data) {
                current = current->left;
                if (current == NULL) {
                    parent->left = newNode;
                    return t;
                }
            } else {
                current = current->right;
                if (current == NULL) {
                    parent->right = newNode;
                    return t;
                }
            }
        }
    }
    return t;
}


BinTreeIntNode* balancedTree(int n) {
    BinTreeIntNode *newNode;
    int x;
    int nL;
    int nR;

    if (n == 0) {
        return NULL;
    } else {
        fscanf(file, "%d", &x);
        nL = n / 2;
        nR = n - nL - 1;
        newNode = (BinTreeIntNode*) malloc(sizeof(BinTreeIntNode));
        newNode->key = x;
        newNode->left = balancedTree(nL);
        newNode->right = balancedTree(nR);
    }
    
    return newNode;
}

BinTreeIntNode * getBalancedTree() {
    BinTreeIntNode *tree = NULL;
    const int count = 15; // в файле 15 чисел, данные подготовлены преподавателем курса
    tree = balancedTree(count);
    printBinTree(tree);
    return tree;
}

BinTreeIntNode* nonBalancedTree(int n) {
    BinTreeIntNode *newNode;
    int x;
    int nL;
    int nR;

    if (n == 0) {
        return NULL;
    } else {
        fscanf(file1, "%d", &x);
        nL = n / 4;
        nR = n - nL - 1;
        newNode = (BinTreeIntNode*) malloc(sizeof(BinTreeIntNode));
        newNode->key = x;
        newNode->left = nonBalancedTree(nL);
        if(nR < 0 )
           newNode->right = NULL;
        else   
           newNode->right = nonBalancedTree(nR);
    }
    return newNode;
}



BinTreeIntNode * getNonBalancedTree() {
    BinTreeIntNode *tree = NULL;
    const int count = 16; // в файле 16 чисел, данные подготовлены преподавателем курса, я добавил число 22
    tree = nonBalancedTree(count);
    printBinTree(tree);
    return tree;
}


// Написать функцию проверяющую является ли переданное в неё бинарное дерево сбалансированным 
int binTreeDepth(BinTreeIntNode* root) {
    int max=0;
    if (root == NULL) {
     return 0;
    }
	if (root->left == NULL && root->right == NULL)
	    return 1;
    if (binTreeDepth(root->left) > binTreeDepth(root->right))
        max=binTreeDepth(root->left);
	else
        max=binTreeDepth(root->right);
	return 1 + max;
	   
}

boolean checkIsBalanced (BinTreeIntNode* root) {
 BinTreeIntNode *left = root->left;
 BinTreeIntNode *right = root->right;
 if(abs(binTreeDepth(left) - binTreeDepth(right)) > 1) {
    //printf("The tree is not balanced.\n");
    return false;
 }
 else {
    //printf("The tree is balanced.\n");
    return true;
 }
}

// написать программу, которая:
// создаст [50] деревьев по [10000] узлов и заполнит узлы случайными целочисленными значениями;
// пока не сделал.

int main(int argc, char** argv) {
    file = fopen("../src/balance.txt", "r");
    if (file == NULL) {
        printf("%s \n", "Cannot open file ../src/balance.txt");
        return 1;
    }
    file1 = fopen("../src/nonbalance.txt", "r");
    if (file1 == NULL) {
           printf("%s \n", "Cannot open file ./nonbalance.txt");
           return 1;
    }

    BinTreeIntNode * balancedBinTree = getBalancedTree();
    printf("\n");
    BinTreeIntNode * nonBalancedBinTree = getNonBalancedTree();
    printf("\nBalanced tree:\n");
    printBinTree(balancedBinTree);
    if (checkIsBalanced(balancedBinTree))
        printf("\nThe check function says the tree is balanced.\n");
    else
        printf("\nThe check function says the tree is NOT balanced.\n");
    printf("\nNon-Balanced tree:\n");
    printBinTree(nonBalancedBinTree);
    if (checkIsBalanced(nonBalancedBinTree))
        printf("\nThe check function says the tree is balanced.\n");
    else
        printf("\nThe check function says the tree is NOT balanced.\n");
    
    fclose(file);
    fclose(file1);

    return 0;

}
