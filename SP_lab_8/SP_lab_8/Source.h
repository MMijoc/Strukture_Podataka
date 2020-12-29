#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define SUCCESS 0
#define FAILURE (-1)
#define BUFFER_LENGTH 1024
#define TRUE 1

typedef struct _TreeNode {
	char *directoryName;

	struct _TreeNode *child;
	struct _TreeNode *nextSibling;
} TreeNode;

typedef struct _StackNode {
	TreeNode *treeNode;

	struct _StackNode *next;
} StackNode;


TreeNode *CreateNewTreeNode();
StackNode *CreateNewStackNode();
int Push(StackNode *stackHead, TreeNode *treeNode);
int Pop(StackNode *stackHead, TreeNode *result);
int AllocateBuffers(char **path, char **inputBuffer, char **command, char **commandArgument);
int CommandLine();
int SetDirectoryName(TreeNode *directory, char *directoryName);
int PrintHelp(char *command);
int MakeNewDirectory(TreeNode *currentDirectory, char *newDirectoryName);
int PrintDirectory(TreeNode *currentDirectory);
int ChangeDirectory(TreeNode **currentDirectory, char *directoryName, char *path, StackNode *stackHead);
TreeNode *FindDirectory(TreeNode *currentDirectory, char *directoryName);
int PrintError(char *errorMessage);
int ValidatePointer(int numberOfPointersPassed, char *errorMessage, ...);
int FreeStack(StackNode *S);
int FreeAllMemory(char* path, char* inputBuffer, char* command, char* commandArgument, TreeNode* root, StackNode* stackHead);
int FreeTree(TreeNode *T);
int FreeBuffers(char *path, char *inputBuffer, char *command, char *commandArgument);
int ReturnToPreviusDirectory(TreeNode **currentDirectory, TreeNode *rootDirectory, char *path, StackNode *stackHead);