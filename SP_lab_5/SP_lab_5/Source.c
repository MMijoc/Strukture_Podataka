/*
 *Za dvije sortirane liste L1 i L2 (mogu se procitati iz datoteke ili unijeti rucno, bitno je samo da su sortirane), napisati program koji stvara novu vezanu listu tako da racuna:
 *a) L1 unija L2,
 *b) L1 presjek L2.
 *Liste osim pokazivaca na slijedecu strukturu imaju i jedan cjelobrojni element, po kojem su sortirane.
 */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE (-1)

typedef struct _node {
	int value;

	struct _node *next;
} node;

#define BUFFER_LENGTH 1024

node *CreateNewNode(int value);
int InputFromFile(node *head, char *fileName);
int InputFromString(node *head, char *buffer);
int PrintList(node *head);
int ConsoleInput(char *message, char *buffer, size_t bufferSize);
int PrintError(char *message);
int DeleteList(node *head);
int SortedInput(node *head, node *nodeToInsert);
int ListUnion(node *L1, node *L2, node *result);
int ListIntersection(node *L1, node *L2, node *result);
int SelectMenu();
int PrintMenu();



int main()
{
	return SelectMenu();
}

node *CreateNewNode(int value)
{
	node *tmp = NULL;

	tmp = (node *)malloc(sizeof(node));
	if (tmp == NULL) {
		perror("ERROR");
		return NULL;
	}

	tmp->value = value;
	tmp->next = NULL;

	return tmp;
}

int PrintList(node *head)
{
	node *tmp = head->next;

	if (NULL == tmp) {
		printf("Lista je prazna!");
		return FAILURE;
	}

	while (tmp) {
		printf("%d ", tmp->value);
		tmp = tmp->next;
	}
	printf("\n");

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
	int value = 0;

	while (1) {
		argTaken = sscanf(buffer, "%d %n", &value, &n);
		if (argTaken != 1)
			break;
		buffer += n;
		SortedInput(head, CreateNewNode(value));
	}

	return SUCCESS;
}

int ConsoleInput(char *message, char *buffer, size_t bufferSize)
{
	if (message)
		printf("%s", message);
	memset(buffer, '\0', bufferSize);
	fgets(buffer, bufferSize - 1, stdin);
	strtok(buffer, "\n");

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

int DeleteList(node *head)
{
	node *toFree = NULL;
	node* tmp = head->next;
	while(tmp) {
		toFree = tmp;
		tmp = tmp->next;
		free(toFree);
	}

	head->next = NULL;
	return SUCCESS;
}

int SortedInput(node *head, node *nodeToInsert)
{
	node *tmp = NULL;
	node *nextNode = NULL;

	if (head == NULL || nodeToInsert == NULL) {
		PrintError("Invalid function parameters!");
		return FAILURE;
	}

	if (head->next == NULL) {
		head->next = nodeToInsert;
		return SUCCESS;
	}
	
	tmp = head;
	while (tmp->next != NULL && tmp->next->value < nodeToInsert->value)
		tmp = tmp->next;

	if (tmp->next != NULL && nodeToInsert->value == tmp->next->value) {
		free(nodeToInsert); //podrazumjeva da u istoj listi nema duplih vrijednosti
		return SUCCESS;
	}

	nodeToInsert->next = tmp->next;
	tmp->next = nodeToInsert;

	return SUCCESS;
}

int ListUnion(node *L1, node *L2, node *result)
{
	node *tmp = L1->next;

	while (tmp) {
		SortedInput(result, CreateNewNode(tmp->value));
		tmp = tmp->next;
	}

	tmp = L2->next;
	while (tmp) {
		SortedInput(result, CreateNewNode(tmp->value));
		tmp = tmp->next;
	}

	return SUCCESS;
}

int ListIntersection(node *L1, node *L2, node *result)
{
	node *tmp1 = L1->next;
	node *tmp2 = L2->next;

	while (tmp1 && tmp2) {

		if (tmp1->value > tmp2->value) {
			tmp2 = tmp2->next;

		} else if (tmp1->value < tmp2->value) {
			tmp1 = tmp1->next;

		} else {
			result->next = CreateNewNode(tmp1->value);
			result = result->next;
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
	}

	return SUCCESS;
}

int PrintMenu()
{
	printf("1 -> Unesi prvu listu iz datoteke\n");
	printf("2 -> Unesi drugi listu iz datoteke\n");
	printf("3 -> Unesi rucno prvu listu\n");
	printf("4 -> Unesi rucno drugu listu\n");
	printf("5 -> Unija listi\n");
	printf("6 -> Presjek listi\n");
	printf("\texit -> izlaz iz programa\n");

	return SUCCESS;
}

int SelectMenu()
{
	char tmpBuffer[BUFFER_LENGTH];
	node list1 = {0, NULL};
	node list2 = {0, NULL};
	node result1 = {0, NULL};
	node result2 = {0, NULL};

	while (1) {
		PrintMenu();
		ConsoleInput("Izbor: ", tmpBuffer, BUFFER_LENGTH);

		if (strcmp(tmpBuffer, "1") == 0) {
			ConsoleInput("Unesite ime datoteke u kojoj je zapisana prva lista: ", tmpBuffer, BUFFER_LENGTH);
			if (list1.next != NULL)
				DeleteList(&list1);
			InputFromFile(&list1, tmpBuffer);
		
		} else if (strcmp(tmpBuffer, "2") == 0) {
			ConsoleInput("Unesite ime datoteke u kojoj je zapisana druga lista: ", tmpBuffer, BUFFER_LENGTH);
			if (list2.next != NULL)
				DeleteList(&list2);
			InputFromFile(&list2, tmpBuffer);
		
		} else if (strcmp(tmpBuffer, "3") == 0) {
			ConsoleInput("Unesite prvu listu: ", tmpBuffer, BUFFER_LENGTH);
			if (list2.next != NULL)
				DeleteList(&list2);
			InputFromString(&list1, tmpBuffer);
			PrintList(&list1);

		} else if (strcmp(tmpBuffer, "4") == 0) {
			ConsoleInput("Unesite drugu listu: ", tmpBuffer, BUFFER_LENGTH);
			if (list2.next != NULL)
				DeleteList(&list2);
			InputFromString(&list2, tmpBuffer);
			PrintList(&list2);
		
		} else if (strcmp(tmpBuffer, "5") == 0) {
			if (list1.next == NULL || list2.next == NULL) {
				printf("Potrebno je unijeti obe liste!\n");

			} else {
				ListUnion(&list1, &list2, &result1);
				printf("Prva lista: ");
				PrintList(&list1);
				printf("Druga lista: ");
				PrintList(&list2);
				printf("Unija: ");
				PrintList(&result1);
			}
		
		} else if (strcmp(tmpBuffer, "6") == 0) {
			if (list1.next == NULL || list2.next == NULL) {
				printf("Potrebno je unijeti obe liste!\n");				

			} else {
				ListIntersection(&list1, &list2, &result2);
				printf("Prva lista: ");
				PrintList(&list1);
				printf("Druga lista: ");
				PrintList(&list2);
				printf("Presjek: ");
				PrintList(&result2);
			}
		
		
		} else if (_strcmpi(tmpBuffer, "exit") == 0) {
			DeleteList(&list1);
			DeleteList(&list2);
			return SUCCESS;
		
		} else {
			printf("\nNepoznata naredba \"%s\"", tmpBuffer);
		}
		
		ConsoleInput("\nPress any key to continue . . .", tmpBuffer, BUFFER_LENGTH);
		system("cls");
		DeleteList(&result1);
		DeleteList(&result2);
	
	}


	return FAILURE;
}