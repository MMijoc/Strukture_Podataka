#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

/*
 *Napisati program koji iz datoteke cita postfiks izraz i zatim korištenjem stoga racuna
 *rezultat. Stog je potrebno realizirati preko vezane liste.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE (-1)

#define BUFFER_LENGTH 1024

typedef struct _node {
	double value;

	struct _node *next;
} node;

typedef struct _queue {
	node head;
	node *tail;
} queue;

node *CreateNewNode(double value);
int Push(node *stackHead, double value);
int Pop(node *stackHead, double *result);
char *GetFileContent(char *fileName);
int InputPostfixFromString(node *stackHead, char *postfix);

int main()
{
	char fileName[BUFFER_LENGTH];
	char *fileContent = NULL;

	strcpy(fileName, "postfix");
	fileContent = GetFileContent(fileName);
	printf("%s\n", fileContent);

	return SUCCESS;
}


node *CreateNewNode(double value)
{
	node *newNode = NULL;

	newNode = (node *)malloc(sizeof(node));
	if (NULL == newNode) {
		perror("Memory allocation failed:");
		return NULL;
	}

	newNode->value = value;
	newNode->next = NULL;

	return newNode;
}

int Push(node *stackHead, double value)
{
	node *nodeToPush = NULL;

	nodeToPush = CreateNewNode(value);
	if (NULL == nodeToPush) return FAILURE;

	nodeToPush->next = stackHead->next;
	stackHead->next = nodeToPush;

	return SUCCESS;
}

int Pop(node *stackHead, double *result)
{
	node *nodeToPop = stackHead->next;
	if (NULL == nodeToPop)	return FAILURE;


	*result = nodeToPop->value;
	stackHead->next = stackHead->next->next;
	free(nodeToPop);

	return SUCCESS;
}

char *GetFileContent(char *fileName)
{
	char *fileContent = NULL;
	FILE *fp = NULL;
	int length = 0;

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		perror("ERROR");
		return NULL;
	}

	fseek(fp, 0, SEEK_END);
	length = ftell(fp) + 1; // +1 for '\0'

	fileContent = (char *)malloc(length * sizeof(char));
	if (fileContent == NULL) {
		perror("Memory allocation failed:");
		return NULL;
	}

	fseek(fp, 0, SEEK_SET);
	fgets(fileContent, length, fp);
	fclose(fp);

	return fileContent;
}