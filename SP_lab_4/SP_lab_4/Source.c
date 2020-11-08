/*
 *Napisati program za zbrajanje i mnozenje polinoma.
 *Koeficijenti i eksponenti se citaju iz datoteke.
 *Napomena: Eksponenti u datoteci nisu nuzno sortirani.
 */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE (-1)

#define BUFFER_LENGTH 1024

typedef struct _node {

	double coeff;
	int exp;

	struct _node *next;
} node;

node *CreateNewNode(double coeff, int exp);
int SortedInput(node *head, node *nodeToInsert);
int PrintError(char *message);
int InputFromFile(node *head, char *fileName);
int InputFromString(node *head, char *buffer);
int PrintList(node *head);
int InsertAtPosition(node *position, node *nodeToInsert);

int main()
{
	char tmpBuffer[BUFFER_LENGTH];
	node Head = {0, 0, NULL};


	strcpy(tmpBuffer, "poly1");
	InputFromFile(&Head, tmpBuffer);
	PrintList(&Head);

	
	system("pause");
	return SUCCESS;
}

node *CreateNewNode(double coeff, int exp)
{
	node *tmp = NULL;

	tmp = (node *)malloc(sizeof(node));
	if (tmp == NULL) {
		perror("ERROR");
		return NULL;
	}

	tmp->coeff = coeff;
	tmp->exp = exp;
	tmp->next = NULL;

	return tmp;
}

int SortedInput(node *head, node *nodeToInsert)
{
	node *tmp = NULL;
	node *nextNode = NULL;

	if (head == NULL || nodeToInsert == NULL) {
		PrintError("Invalid function parameters");
		return FAILURE;
	}

	if (head->next == NULL) {
		head->next = nodeToInsert;
		return SUCCESS;
	}
	
	tmp = head;
	while (tmp->next != NULL && tmp->next->exp < nodeToInsert->exp)
		tmp = tmp->next;

	//pod pretpostavkom da se nece nikad pojaviti dva elementa s istim exsponentima
	//ili jos gore dva elementa s istim eksponentima i suprotinim koeficijentima (dakle 0)
	//al to nije nigdje osigurano

	nodeToInsert->next = tmp->next;
	tmp->next = nodeToInsert;

	return SUCCESS;
}

int InputFromFile(node *head, char *fileName)
{
	FILE *fp = NULL;
	char buffer[BUFFER_LENGTH] = {'\0'};
	double coeff = 0;
	int exp = 0;

	 
	if (strstr(fileName, ".txt") == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		perror("ERROR");
		return FAILURE;
	}


	while (!feof(fp)) {
		memset(buffer, '\0', BUFFER_LENGTH);
		fgets(buffer, BUFFER_LENGTH - 1, fp);
		InputFromString(head, buffer);
	}


	fclose(fp);
	return SUCCESS;
}

int InputFromString(node *head, char *buffer)
{
	int argTaken = 0, n = 0;
	double coeff = 0;
	int exp = 0;

	while (1) {
		argTaken = sscanf(buffer, "%lf %d %n", &coeff, &exp, &n);
		if (argTaken != 2)
			break;
		buffer += n;
		SortedInput(head, CreateNewNode(coeff, exp));
	}

	return SUCCESS;
}

int PrintError(char *message)
{
	if(message == NULL) {
		fprintf(stderr, "\nUnknown error occurred!");
		return SUCCESS;
	}
	fprintf(stderr, "\n%s", message);
	
	return SUCCESS;
}

int InsertAtPosition(node *position, node *nodeToInsert)
{
	
	nodeToInsert->next = position->next;
	position->next = nodeToInsert;

	return SUCCESS;
}

int PrintList(node *head)
{
	node *tmp = head->next;

	while (tmp) {
		printf("%.2lf*X^(%d)", tmp->coeff, tmp->exp);
		tmp = tmp->next;
		if (tmp == NULL) break;

		(tmp->coeff > 0) ? printf(" +") : printf(" ");

	}
	puts("");

	return SUCCESS;
}