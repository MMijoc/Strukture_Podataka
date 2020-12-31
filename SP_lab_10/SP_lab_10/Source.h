#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define SUCCESS 0
#define FAILURE (-1)
#define BUFFER_LENGTH 1024
#define ELEMENET_SIZE 50
#define TRUE 1
#define FALSE 0

typedef struct _binTreeNode {
	char element[ELEMENET_SIZE];

	struct _binTreeNode *left;
	struct _binTreeNode *right;
} BinTreeNode;

typedef struct _stackNode {
	BinTreeNode *binNode;

	struct _stackNode *next;
} StackNode;
typedef StackNode Stack;

char *GetFileContent(char *fileName);
BinTreeNode *CreateNewBinTreeNode(char *element);
int InitStack(Stack *S);
StackNode *CreateNewStackNode(BinTreeNode *binNode);
int Push(StackNode *stackHead, BinTreeNode *binNode);
int Pop(StackNode *stackHead, BinTreeNode **result);
int CreateExpressionTree(BinTreeNode **root, char *postfixExpression);
int PrintTreeInorder(BinTreeNode *node, FILE *fp);
int PrintExspressionTreeToFile(BinTreeNode *root, char *fileName);
int FreeBinTree(BinTreeNode *node);
int FreeStack(Stack *S);
int IsNnumber(char *element);
int IsValidOperator(char operation);
int IsNull(int numberOfPointersPassed, char *errorMessage, ...);
int ConsoleInput(const char *message, char *buffer, size_t bufferSize);