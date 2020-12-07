#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

/*
Napisati program koji pomocu vezanih listi simulira rad:
a) stoga,
b) reda.
Napomena: Funkcija "push" sprema cijeli broj, slucajno generirani u opsegu od 10 -100.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SUCCESS 0
#define FAILURE (-1)

#define BUFFER_LENGTH 1024

typedef struct _node {
	int value;

	struct _node *next;
} node;
typedef node* stack;

node *CreateNewNode(int value);
int Push(node *stackHead, int value);
int Pop(node *stackHead, int *result);

int main()
{
	node Stack = {0, NULL};
	int i, tmp;
	for (i = 0; i < 10; i++) {
		Push(&Stack, i);
	}

	for (i = 0; i <= 10; i++) {
		Pop(&Stack, &tmp);
		printf("%d ", tmp);
	}

	return SUCCESS;
}

node *CreateNewNode(int value)
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

int Push(node *stackHead, int value)
{
	node *nodeToPush = NULL;

	nodeToPush = CreateNewNode(value);
	if (NULL == nodeToPush) return FAILURE;

	nodeToPush->next = stackHead->next;
	stackHead->next = nodeToPush;

	return SUCCESS;
}

int Pop(node *stackHead, int *result)
{
	node *nodeToPop = stackHead->next;
	if (NULL == nodeToPop) {
		printf("Stack is empty");
		return FAILURE;
	}

	*result = nodeToPop->value;
	stackHead->next = stackHead->next->next;
	free(nodeToPop);

	return SUCCESS;
}