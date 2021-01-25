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


int PrintMenu();
int SelectMenu();
int PrintList(node *head);
node *CreateNewNode(double coeff, int exp);
int InsertAtPosition(node *position, node *nodeToInsert);
int SortedInput(node *head, node *nodeToInsert);
int InputFromFile(node *head, char *fileName);
int InputFromString(node *head, char *buffer);
int AddPoly(node *poly1, node *poly2, node *result);
int MultiplyPoly(node *poly1, node *poly2, node *result);
int DeleteList(node *head);
int ConsoleInput(char *message, char *buffer, size_t bufferSize);
int PrintError(char *message);


int main()
{
	return SelectMenu();
}

int PrintMenu()
{
	printf("1 -> Unesi prvi polinom iz datoteke\n");
	printf("2 -> Unesi drugi polinom iz datoteke\n");
	printf("3 -> Zbroji polinome\n");
	printf("4 -> Pomnozi polinome\n");
	printf("\texit -> izlaz iz programa\n");

	return SUCCESS;
}

int SelectMenu()
{
	char tmpBuffer[BUFFER_LENGTH];
	node poly1 = {0, 0, NULL};
	node poly2 = {0, 0, NULL};
	node result1 = {0, 0, NULL};
	node result2 = {0, 0, NULL};
	int isError = 0;


	while (!isError) {
		isError = PrintMenu();
		ConsoleInput("Izbor: ", tmpBuffer, BUFFER_LENGTH);

		if (strcmp(tmpBuffer, "1") == 0) {
			ConsoleInput("Unesite ime datoteke u kojoj je zapisan prvi polinom: ", tmpBuffer, BUFFER_LENGTH);
			if (poly1.next != NULL)
				DeleteList(&poly1);
			InputFromFile(&poly1, tmpBuffer);
		
		} else if (strcmp(tmpBuffer, "2") == 0) {
			ConsoleInput("Unesite ime datoteke u kojoj je zapisan drugi polinom: ", tmpBuffer, BUFFER_LENGTH);
			if (poly2.next != NULL)
				DeleteList(&poly2);
			InputFromFile(&poly2, tmpBuffer);
		
		} else if (strcmp(tmpBuffer, "3") == 0) {
			if (poly1.next == NULL || poly2.next == NULL) {
				printf("Potrebno je unijeti oba polinoma!\n");
				ConsoleInput("Press any key to continue . . .", tmpBuffer, BUFFER_LENGTH);
				system("cls");
				continue;
			}
			isError = AddPoly(&poly1, &poly2, &result1);
			printf("Prvi polinom: ");
			PrintList(&poly1);
			printf("Drugi polinom: ");
			PrintList(&poly2);
			printf("Rezultat zbrajanja: ");
			PrintList(&result1);
		
		} else if (strcmp(tmpBuffer, "4") == 0) {
			if (poly1.next == NULL || poly2.next == NULL) {
				printf("Potrebno je unijeti oba polinoma!\n");
				ConsoleInput("Press any key to continue . . .", tmpBuffer, BUFFER_LENGTH);
				system("cls");
				continue;
			}
			isError = MultiplyPoly(&poly1, &poly2, &result2);
			printf("Prvi polinom: ");
			PrintList(&poly1);
			printf("Drugi polinom: ");
			PrintList(&poly2);
			printf("Rezultat mnozenja: ");
			PrintList(&result2);
		
		
		} else if (_strcmpi(tmpBuffer, "exit") == 0) {
			
			DeleteList(&poly1);
			DeleteList(&poly2);
			DeleteList(&result1);
			DeleteList(&result2);
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

int InsertAtPosition(node *position, node *nodeToInsert)
{
	
	nodeToInsert->next = position->next;
	position->next = nodeToInsert;

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
	while (tmp->next != NULL && tmp->next->exp < nodeToInsert->exp)
		tmp = tmp->next;

	if (tmp->next != NULL && nodeToInsert->exp == tmp->next->exp) {
		tmp->next->coeff += nodeToInsert->coeff;
		if (tmp->next->coeff == 0) {
			node *toFree = tmp->next;
			tmp->next = tmp->next->next;
			free(toFree);
		}

		free(nodeToInsert);
		return SUCCESS;
	}

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

int AddPoly(node *poly1, node *poly2, node *result)
{
	poly1 = poly1->next;
	poly2 = poly2->next;

	//polinomi su nuzno sortirani
	while (poly1 != NULL && poly2 != NULL) {
		if (poly1->exp == poly2->exp) {
			SortedInput(result, CreateNewNode(poly1->coeff + poly2->coeff, poly1->exp));
			poly1 = poly1->next;
			poly2 = poly2->next;
		} else if (poly1->exp < poly2->exp) {
			SortedInput(result, CreateNewNode(poly1->coeff, poly1->exp));
			poly1 = poly1->next;
		} else {
			SortedInput(result, CreateNewNode(poly2->coeff, poly2->exp));
			poly2 = poly2->next;
		}

	}

	while (poly1) {
		SortedInput(result, CreateNewNode(poly1->coeff, poly1->exp));
		poly1 = poly1->next;
	}

	while (poly2) {
		SortedInput(result, CreateNewNode(poly2->coeff, poly2->exp));
		poly2 = poly2->next;
	}

	return SUCCESS;
}

int MultiplyPoly(node *poly1, node *poly2, node *result)
{
	node *tmp = NULL;

	poly1 = poly1->next;
	tmp = poly2->next;
	while (poly1) {
		while (tmp) {
			SortedInput(result, CreateNewNode(poly1->coeff * tmp->coeff, poly1->exp + tmp->exp));
			tmp = tmp->next;
		}

		poly1 = poly1->next;
		tmp = poly2->next;
	}

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
