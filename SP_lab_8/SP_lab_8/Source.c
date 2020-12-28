/*
 *Napisati program koji pomocu vezanih listi (stabala) predstavlja strukturu direktorija.
 *Omoguciti unos novih direktorija i pod-direktorija, ispis sadrzaja direktorija i povratak u prethodni direktorij.
 *Tocnije program treba preko menija simulirati koristenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.
 */

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Source.h"

int main()
{

	return SUCCESS;
}


TreeNode* CreateNewTreeNode()
{
	TreeNode* newNode = NULL;

	newNode = (TreeNode*)malloc(sizeof(TreeNode));
	if (newNode == NULL) {
		PrintError("Tree node memory allocation failed!");
		return NULL;
	}

	newNode->child = NULL;
	newNode->nextSibling = NULL;
	newNode->directoryName = NULL;

	return newNode;
}

StackNode* CreateNewStackNode()
{
	StackNode* newNode = NULL;

	newNode = (StackNode*)malloc(sizeof(StackNode));
	if (newNode == NULL) {
		PrintError("Tree node memory allocation failed!");
		return NULL;
	}

	newNode->treeNode = NULL;
	newNode->next = NULL;

	return newNode;
}

int Push(StackNode* stackHead, TreeNode* treeNode)
{
	StackNode* nodeToPush = NULL;

	nodeToPush = CreateNewStackNode();
	if (NULL == nodeToPush) return FAILURE;

	nodeToPush->treeNode = treeNode;

	nodeToPush->next = stackHead->next;
	stackHead->next = nodeToPush;

	return SUCCESS;
}

int Pop(StackNode* stackHead, TreeNode *result)
{
	StackNode* nodeToFree = NULL;

	if (NULL == stackHead->next) {
		result = NULL;
		return FAILURE; // stack is empty
	}

	result = stackHead->next->treeNode;
	nodeToFree = stackHead->next;
	stackHead->next = stackHead->next->next;

	free(nodeToFree);
	return SUCCESS;
}

int PrintError(char* errorMessage)
{
	if (errorMessage == NULL) {
		fprintf(stderr, "\nUnknown Error!");
		return SUCCESS;
	} else {
		fprintf(stderr, errorMessage);
	}

	return SUCCESS;
}