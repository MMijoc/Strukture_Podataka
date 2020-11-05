/*
 *Definirati strukturu osoba(ime, prezime, godina rodjenja) i napisati program koji :
 *a) dinamicki dodaje novi element na pocetak liste,
 *b) ispisuje listu,
 *c) dinamicki dodaje novi element na kraj liste,
 *d) pronalazi element u listi(po prezimenu),
 *e) brise odredjeni element iz liste,
 *U zadatku se ne smiju koristiti globalne varijable.

 *Prethodnom zadatku dodati funkcije:
 *a) dinamicki dodaje novi element iza odredjenog elementa,
 *b) dinamicki dodaje novi element ispred odredjenog elementa,
 *c) sortira listu po prezimenima osoba,
 *d) upisuje listu u datoteku,
 *e) cita listu iz datoteke.
 */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER_LENGTH 1024
#define SUCCESS 0
#define FAILURE (-1)
#define CLEAR_SCREEN "cls"

typedef struct _person {
	char name[BUFFER_LENGTH];
	char lastName[BUFFER_LENGTH];
	int birthYear;

	struct _person *next;
} person;


person *CreateNewNode(char *name, char *lastName, int birthYear);
int InsertAtHead(person *head, person *nodeToInsert);
int InsertAtTail(person *head, person *nodeToInsert);
person *FindTail(person *head);
int PrintList(person head);
int PrintPerson(person *P);
int FindByLastName(person head, char *lastName);
int RemovePerson(person *head, char *lastName);
int PrintMenu();
int SelectMenu();
int PrintError(char *errorMessage);
person *InputFromUser();
int DeleteList(person *head);

int InputFromFile(char *fileName, person *position);


int main()
{
	int isError = 0;

	//FILE *fp = fopen("studenti.txt", "w");

	isError = SelectMenu();

	return isError;
}

person *CreateNewNode(char *name, char *lastName, int birthYear)
{
	person *newNode = NULL;

	newNode = (person *)malloc(sizeof(person));
	if (newNode == NULL) {
		perror("ERROR");
		return NULL;
	}

	strcpy(newNode->name, name);
	strcpy(newNode->lastName, lastName);
	newNode->birthYear = birthYear;
	newNode->next = NULL;

	return newNode;
}

int InsertAtHead(person *head, person *nodeToInsert)
{
	if (nodeToInsert == NULL) return FAILURE;

	if (head->next != NULL)
		nodeToInsert->next = head->next;
	head->next = nodeToInsert;

	return SUCCESS;
}

int InsertAtTail(person *head, person *nodeToInsert)
{
	person *tail = NULL;

	tail = FindTail(head);
	if (tail == NULL)//head.next == NULL
		return InsertAtHead(head, nodeToInsert);

	tail->next = nodeToInsert;

	return SUCCESS;
}

person *FindTail(person *head)
{
	person *tmp = head->next;

	if (tmp == NULL) return NULL;
	while (tmp->next)
		tmp = tmp->next;

	return tmp;
}

int PrintList(person head)
{
	person *tmp = head.next;

	while (tmp) {
		PrintPerson(tmp);
		tmp = tmp->next;
	}

	return SUCCESS;
}

int PrintPerson(person *P)
{
	if (P == NULL) return FAILURE;

	printf("\n%-32s %-32s %-8d", P->name, P->lastName, P->birthYear);
	return SUCCESS;
}

int FindByLastName(person head, char* lastName)
{
	person *tmp = head.next;
	int sameLastName = 0;
	while (tmp) {
		if (strcmp(tmp->lastName, lastName) == 0) {
			PrintPerson(tmp);
			sameLastName++;
		}
		tmp = tmp->next;
	}

	if (sameLastName == 0)
		printf("\nNe postoji osoba s prezimenom \"%s\"", lastName);

	return sameLastName;
}

int RemovePerson(person *head, char *lastName)
{
	person *tmp = head->next;
	person *toFree = NULL;
	person *prev = tmp;
	char select[BUFFER_LENGTH];
	int exits = 0;


	while (tmp) {

		if (strcmp(tmp->lastName, lastName) == 0) {
			printf("\nJeste li sigurni da zelite obrisati:");
			PrintPerson(tmp);
			printf("\n\tUnesite Y za da, blio koju tipku za ne:\n\tUnos: ");
			scanf(" %s", select);
			if (strcmp(select, "Y") == 0) {
				exits = 1;
				if (head->next == tmp) {
					head->next = tmp->next;
					toFree = tmp;
					tmp = tmp->next;
					free(toFree);
				} else {
					prev->next = tmp->next;
					toFree = tmp;
					tmp = tmp->next;
					free(toFree);
				}
			}

		} else {
			prev = tmp;
			if (tmp)
				tmp = tmp->next;
		}

	}

	if (!exits)
		printf("Ne postoji nit jedna osoba s prezimenom \"%s\"\n", lastName);

	return SUCCESS;
}

int PrintMenu()
{
	printf("\n");
	printf("Unos:\n");
	printf("\t1 -> Unos (na pocetak)\n");
	printf("\t2 -> Unos prije studenta\n");
	printf("\t3 -> Unos nakon studenta\n");
	printf("\t4 -> Unos na kraj\n");
	printf("\t5 -> Ucitaj listu iz datoteke\n");

	printf("\nObrada i pretrazivanje:\n");
	printf("\t6 -> Pronadji po prezimenu\n");
	printf("\t7 -> Izbrisi po prezimenu\n");
	printf("\t8 -> Sortiraj\n");

	printf("\nIspis:\n");
	printf("\t9 -> Ispis na ekran\n");
	printf("\t10 -> Ispisi listu u datoteku\n");
	printf("\t11 -> Obrisi listu\n\n");
	printf("\tExit -> Izlaz iz programa\n");

	return SUCCESS;
}


int SelectMenu()
{
	char select[BUFFER_LENGTH] = { '\0' };
	char tmpBuffer[BUFFER_LENGTH] = { '\0' };
	int isError = 0;
	int numArg = 0;
	person Head = { "HEAD", "HEAD", 0, NULL };

	while (1) {
		if (isError) return FAILURE;

		PrintMenu();
		do {
			printf("Izbor: ");
			fgets(tmpBuffer, BUFFER_LENGTH - 1, stdin);
			strtok(tmpBuffer, "\n");
			numArg = sscanf(tmpBuffer, "%s", select);
		} while (numArg < 0);

		if (strcmp(select, "1") == 0) {
			isError = InsertAtHead(&Head, InputFromUser());

		} else if (strcmp(select, "2") == 0) {


		} else if (strcmp(select, "3") == 0) {
			

		} else if (strcmp(select, "4") == 0) {
			isError = InsertAtTail(&Head, InputFromUser());

		} else if (strcmp(select, "5") == 0) {
			strcpy(tmpBuffer, "studenti");
			InputFromFile(tmpBuffer, &Head);

		} else if (strcmp(select, "6") == 0) {
			printf("Unesite prezime koje pretrazujete: ");
			fgets(tmpBuffer, BUFFER_LENGTH - 1, stdin);
			strtok(tmpBuffer, "\n");
			FindByLastName(Head, tmpBuffer);

		} else if (strcmp(select, "7") == 0) {
			printf("Unesite prezime po kojem zelite brisati: ");
			fgets(tmpBuffer, BUFFER_LENGTH - 1, stdin);
			strtok(tmpBuffer, "\n");
			RemovePerson(&Head, tmpBuffer);

		} else if (strcmp(select, "8") == 0) {


		} else if (strcmp(select, "9") == 0) {
			PrintList(Head);

		} else if (strcmp(select, "10") == 0) {


		} else if (strcmp(select, "11") == 0) {


		} else if (strcmp(select, "0") == 0) {
			//test option


		}else if (_stricmp(select, "exit") == 0) {
			break;
		} else {
			printf("Nepoznata naredba: \"%s\"", select);
		}

		printf("\nPress any key to continue . . .");
		fgets(tmpBuffer, BUFFER_LENGTH - 1, stdin);
		system(CLEAR_SCREEN);
	}

	DeleteList(&Head);

	return SUCCESS;
}

person *InputFromUser()
{
	char name[BUFFER_LENGTH] = { '\0' };
	char lastName[BUFFER_LENGTH] = { '\0' };
	char birthYear[BUFFER_LENGTH] = { '\0' };
	int year = 0;
	person *newPerson = NULL;

	printf("Unesite ime: ");
	fgets(name, BUFFER_LENGTH - 1, stdin);
	strtok(name, "\n");
	printf("Unesite prezime: ");
	fgets(lastName, BUFFER_LENGTH - 1, stdin);
	strtok(lastName, "\n");
	
	//atoi nece prepoznat mjesovitu kombinaciju slova i broeva kao gresku npr 11aa je 11 ili 22aa33 je 22
	do {
		printf("Unesite godinu rodjenja: ");
		fgets(birthYear, BUFFER_LENGTH - 1, stdin);
		strtok(birthYear, "\n");
		year = atoi(birthYear);
		if (year == 0)
			printf("\nNepravilan unos!\n");
	} while (year == 0);

	newPerson = CreateNewNode(name, lastName, year);
	if (newPerson == NULL) {
		PrintError("Memory allocation failed");
		return NULL;
	}

	return newPerson;
}

int PrintError(char *errorMessage)
{

	if (errorMessage == NULL) {
		fprintf(stderr, "\nUnknown Error!");
		return SUCCESS;
	} else {
		fprintf(stderr, errorMessage);

	}
	return SUCCESS;
}

int DeleteList(person *head)
{
	person *toFree = head->next;
	person *tmp = NULL;

	while (toFree) {
		tmp = toFree->next;
		free(toFree);
		toFree = tmp;
	}
	head->next = NULL;
	return SUCCESS;
}

int InputFromFile(char *fileName, person *head)
{
	FILE *fp = NULL;
	char buffer[3*BUFFER_LENGTH] = {'\n'};
	char *tmp = NULL;
	char name[BUFFER_LENGTH] = { '\0' }, lastName[BUFFER_LENGTH] = { '\0' }, birthYear[BUFFER_LENGTH] = { '\0' };
	int year = 0;


	if (strstr(fileName, ".txt") == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		perror("ERROR");
		return FAILURE;
	}

	while (!feof(fp)) {
		fgets(buffer, BUFFER_LENGTH, fp);

		tmp = strtok(buffer, ",");
		strcpy(name, tmp);

		tmp = strtok(NULL, ",");
		strcpy(lastName, tmp);

		tmp = strtok(NULL, ",\n");
		strcpy(birthYear, tmp);
		year = atoi(birthYear);

		InsertAtTail(head, CreateNewNode(name, lastName, year));

	}

	fclose(fp);

	return SUCCESS;
}