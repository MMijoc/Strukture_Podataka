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

typedef struct _queue {
	node head;
	node *tail;
} queue;

node *CreateNewNode(int value);
int Push(node *stackHead, int value);
int Pop(node *stackHead, int *result);
int GetRandomNumber(int min, int max);
void InitQueue(queue *q);
int Enqueue(queue *q, int value);
int Dequeue(queue *q, int *result);

int main()
{
	//node Stack = {0, NULL};
	int i, tmp;
	//for (i = 0; i < 10; i++) {
	//	Push(&Stack, i);
	//}

	//for (i = 0; i <= 10; i++) {
	//	Pop(&Stack, &tmp);
	//	printf("%d ", tmp);
	//}


	queue Q;
	InitQueue(&Q);
	for (i = 1; i <= 10; i++) {
		Enqueue(&Q, i);
	}


	for (i = 1; i <= 10; i++) {
		Dequeue(&Q, &tmp);
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

int GetRandomNumber(int min, int max)
{
	return rand() % (max - min) + min;
}

void InitQueue(queue *q)
{
	q->head.next = NULL;
	q->head.value = 0;
	q->tail = NULL;
}

int Enqueue(queue *q, int value)
{
	node *nodeToEnqueue = NULL;
	
	nodeToEnqueue = CreateNewNode(value);
	if (NULL == nodeToEnqueue) return FAILURE;

	if (q->tail != NULL) {
		q->tail->next = nodeToEnqueue;
		q->tail = q->tail->next;
	}

	if (q->head.next == NULL) {
		q->head.next = nodeToEnqueue;
		q->tail = q->head.next;
	}

	return SUCCESS;
}

int Dequeue(queue *q, int *result)
{
	node *nodeToDequeue = NULL;

	if (q->head.next == NULL) return FAILURE;

	nodeToDequeue = q->head.next;
	*result = nodeToDequeue->value;
	q->head.next = nodeToDequeue->next;

	if (q->head.next == NULL)
		q->tail = NULL;

	free(nodeToDequeue);
	return SUCCESS;
}
