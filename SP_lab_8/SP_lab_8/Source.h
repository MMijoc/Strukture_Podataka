#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE (-1)
#define BUFFER_LENGTH 1024

typedef struct _TreeNode {
	char* directoryName;

	struct _TreeNode* child;
	struct _TreeNode* nextSibling;
} TreeNode;

typedef struct _StackNode {
	TreeNode* treeNode;

	struct _StackNode* next;
} StackNode;


TreeNode* CreateNewTreeNode();
StackNode* CreateNewStackNode();
int Push(StackNode* stackHead, TreeNode* treeNode);
int Pop(StackNode* stackHead, TreeNode* result);
int PrintError(char* errorMessage);