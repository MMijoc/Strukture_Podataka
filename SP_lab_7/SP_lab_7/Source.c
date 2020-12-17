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
#define TRUE 1

#define BUFFER_LENGTH 1024

typedef struct _node {
	double value;

	struct _node *next;
} node;
typedef node stack;

node *CreateNewNode(double value);
int Push(node *stackHead, double value);
int Pop(node *stackHead, double *result);
char *GetFileContent(char *fileName);
int CalculatePostfix(node *stackHead, char *postfix);
int CalculateFromStack(node *stackHead, char operation);

int main()
{
	stack myStack = {0, NULL};
	char fileName[BUFFER_LENGTH];
	char *postfix = NULL;
	double result;

	strcpy(fileName, "postfix");
	postfix = GetFileContent(fileName);

	printf("Postfix expression: %s\n", postfix);
	CalculatePostfix(&myStack, postfix);
	Pop(&myStack, &result);
	printf("Result: %.3lf\n", result);

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

int CalculatePostfix(node *stackHead, char *postfix)
{
	int argTaken = 0, n = 0;
	double value = 0;
	char operation;

	while (TRUE) {
		argTaken = sscanf(postfix, "%lf%n", &value, &n);

		if (argTaken == 1) {
			Push(stackHead, value);
		} else {
			argTaken = sscanf(postfix, "%c%n", &operation, &n);
			if (argTaken == 1) {
				CalculateFromStack(stackHead,operation);
			} else {
				break;
			}
		}

		postfix += n;
	}

	return SUCCESS;
}

int CalculateFromStack(node *stackHead, char operation)
{
	double x, y, result;

	switch (operation) {
		case ' ':
			return FAILURE;
			break;
		case '+':
			Pop(stackHead, &y);
			Pop(stackHead, &x);
			result = x + y;
			Push(stackHead, result);
			break;
		case '-':
			Pop(stackHead, &y);
			Pop(stackHead, &x);
			result = x - y;
			Push(stackHead, result);
			break;
		case '*':
			Pop(stackHead, &y);
			Pop(stackHead, &x);
			result = x * y;
			Push(stackHead, result);
			break;
		case '/':
			Pop(stackHead, &y);
			Pop(stackHead, &x);
			result = x / y;
			Push(stackHead, result);
			break;
		default:
			return FAILURE;	
	}

	return SUCCESS;
}