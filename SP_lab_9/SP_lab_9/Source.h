#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
BinTreeNode *FindMaxValue(BinTreeNode *node);
BinTreeNode *FindMinValue(BinTreeNode *node);
BinTreeNode *FindByValue(BinTreeNode *node, int valueToFind);
int InsertElement(BinTreeNode **node, int value);
BinTreeNode *DeleteNode(BinTreeNode *root, int value);
int PrintTreePreorder(BinTreeNode *node);
int PrintTreePostorder(BinTreeNode *node);
int PrintTreeInorder(BinTreeNode *node);
int FreeBinTree(BinTreeNode *node);
int InputIntegerFromUser(char *message);
int PrintError(char *message);