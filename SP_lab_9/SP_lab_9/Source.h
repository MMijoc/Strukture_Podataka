#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define SUCCESS 0
#define FAILURE (-1)
#define BUFFER_LENGTH 1024
#define TRUE 1

typedef struct _binTreeNode {
	int value;

	struct _binTreeNode *left;
	struct _binTreeNode *right;
} BinTreeNode;

int PrintMenu();
int SelectMenu();
BinTreeNode *CreateNewBinTreeNode(int value);
BinTreeNode *FindMaxValue(BinTreeNode *root);
BinTreeNode *FindMinValue(BinTreeNode *root);
BinTreeNode *FindByValue(BinTreeNode *root, int valueToFind);
int PrintTreePreorder(BinTreeNode *root);
int PrintInorder(BinTreeNode *root);
int PrintTreePostorder(BinTreeNode *root);
int DeleteNode(BinTreeNode *root, BinTreeNode *nodeToDelete);
int FreeBinTree(BinTreeNode *root);
int PrintError(char *message);