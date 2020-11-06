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


int PrintMenu();
int SelectMenu();
int PrintList(person head);
int PrintPerson(person *P);
int PrintError(char *errorMessage);
int ConsoleInput(const char *message, char *buffer, size_t bufferSize);
person *CreateNewNode(char *name, char *lastName, int birthYear);
person *InputFromUser();
person *FindByLastName(person *position, char *lastName);
person *FindPrevious(person *head, char *lastName);
person *FindTail(person *head);
int NumberOfElements(person *head);
int InsertNode(person *position, person *nodeToInsert);
int InsertAtHead(person *head, person *nodeToInsert);
int InsertAtTail(person *head, person *nodeToInsert);
int InsertBefore(person *head, person *nodeToInsert);
int InputFromFile(char *fileName, person *position);
int PrintToFile(person *head, char *fileName);
int RemovePerson(person *head, char *lastName);
int DeleteList(person *head);
int SortListByLastName(person *head);

int main()
{
	int isError = 0;

	isError = SelectMenu();

	return isError;
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
	person *tmp = NULL;
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
			isError = InsertBefore(&Head, InputFromUser());

		} else if (strcmp(select, "3") == 0) {
			ConsoleInput("Unesite prezime osobe nakon koje zelite unijeti novu osobu: ", tmpBuffer, BUFFER_LENGTH);
			tmp = FindByLastName(Head.next, tmpBuffer);
			if (tmp == NULL) {
				printf("Ne postoji osoba s prezimenom \"%S\"", tmpBuffer);
				continue;
			}
			isError = InsertNode(tmp, InputFromUser());
			
		} else if (strcmp(select, "4") == 0) {
			isError = InsertAtTail(&Head, InputFromUser());

		} else if (strcmp(select, "5") == 0) {
			ConsoleInput("Unesite ime datoteke: ", tmpBuffer, BUFFER_LENGTH);
			InputFromFile(tmpBuffer, &Head);

		} else if (strcmp(select, "6") == 0) {
			if (Head.next == NULL) {
				printf("Can not search emty lsit!");
				continue;
			}

			ConsoleInput("Unesite prezime koje pretrazujete: ", tmpBuffer, BUFFER_LENGTH);
			tmp = NULL;
			tmp = FindByLastName(Head.next, tmpBuffer);
			if (tmp == NULL) {
				printf("Ne postoji niti jedan osoba s imenom \"%s\"", tmpBuffer);
				continue;
			} else {
				printf("Osoba(e) s prezimenom \"%s\"", tmpBuffer);
				while (tmp != NULL) {
					PrintPerson(tmp);
					tmp = FindByLastName(tmp->next, tmpBuffer);
				}
			}

		} else if (strcmp(select, "7") == 0) {
			ConsoleInput("Unesite prezime po kojem zelite brisati: ", tmpBuffer, BUFFER_LENGTH);
			isError = RemovePerson(&Head, tmpBuffer);

		} else if (strcmp(select, "8") == 0) {
			SortListByLastName(&Head);

		} else if (strcmp(select, "9") == 0) {
			PrintList(Head);

		} else if (strcmp(select, "10") == 0) {
			ConsoleInput("Unesite ime datoteke: ", tmpBuffer, BUFFER_LENGTH);
			PrintToFile(&Head, tmpBuffer);

		} else if (strcmp(select, "11") == 0) {
			DeleteList(&Head);

		} else if (_stricmp(select, "exit") == 0) {
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

int ConsoleInput(const char *message, char *buffer, size_t bufferSize)
{
	if (message != NULL)
		printf("%s", message);
	memset(buffer, '\0', bufferSize);
	fgets(buffer, bufferSize - 1, stdin);
	strtok(buffer, "\n");

	return SUCCESS;
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

person *InputFromUser()
{
	char name[BUFFER_LENGTH] = { '\0' };
	char lastName[BUFFER_LENGTH] = { '\0' };
	char birthYear[BUFFER_LENGTH] = { '\0' };
	int year = 0;
	person *newPerson = NULL;

	ConsoleInput("Unesite ime: ", name, BUFFER_LENGTH);
	ConsoleInput("Unesite prezime: ", lastName, BUFFER_LENGTH);
	
	//atoi nece prepoznat mjesovitu kombinaciju slova i broeva kao gresku npr 11aa je 11 ili 22aa33 je 22
	do {
		ConsoleInput("Unesite godinu rodjenja: ", birthYear, BUFFER_LENGTH);
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

person *FindByLastName(person *position, char *lastName)
{
	person *tmp = NULL;
	tmp = FindPrevious(position, lastName);
	if (tmp == NULL) return NULL;
	
	tmp = tmp->next;
	return tmp;
}

person *FindPrevious(person *position, char *lastName)
{
	person *tmp = position;
	if (strcmp(tmp->lastName, lastName) == 0)
		return tmp;

	while (tmp->next) {
		if (strcmp(tmp->next->lastName, lastName) == 0)
			return tmp;
		tmp = tmp->next;
	}

	return NULL;
}

person *FindTail(person *head)
{
	person *tmp = head->next;

	if (tmp == NULL) return NULL;
	while (tmp->next)
		tmp = tmp->next;

	return tmp;
}

int NumberOfElements(person *head)
{
	int n = 0;
	person *tmp = head->next;
	while (tmp) {
		n++;
		tmp = tmp->next;
	}
	return n;
}

int InsertNode(person *position, person *nodeToInsert)
{
	if (position == NULL) return FAILURE;

	nodeToInsert->next = position->next;
	position->next = nodeToInsert;

	return SUCCESS;
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

int InsertBefore(person *head, person *nodeToInsert)
{
	char buffer[BUFFER_LENGTH];
	person *tmp = NULL;
	person *prev = NULL;
	
	if (head->next == NULL) {
		PrintError("Can not insert before a preson if the list is empty");
		return SUCCESS;
	}

	ConsoleInput("Unesite prezime osobe prije koje zelite unjeti novu osobu: ",buffer, BUFFER_LENGTH);;
	prev = FindPrevious(head, buffer);
	if (prev == NULL) {
		printf("Ne postoji osoba s prezimenom \"%s\"", buffer);
		return FAILURE;
	}

	if (strcmp(prev->lastName, head->next->lastName) == 0)
		return InsertAtHead(head, nodeToInsert);

	return InsertNode(prev, nodeToInsert);
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

int PrintToFile(person *head, char *fileName)
{
	FILE *fp = NULL;
	person *tmp = head->next;

	if (strstr(fileName, ".txt") == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "w");
	if (fp == NULL) {
		perror("ERROR");
		return FAILURE;
	}

	while (tmp) {
		fprintf(fp, "%s,%s,%d", tmp->name, tmp->lastName, tmp->birthYear);
		tmp = tmp->next;
		if (tmp)
			fprintf(fp, "\n");
	
	}

	fclose(fp);

	return SUCCESS;
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
			exits = 1;
			printf("\nJeste li sigurni da zelite obrisati:");
			PrintPerson(tmp);
			ConsoleInput("\n\tUnesite Y za da, blio koju tipku za ne:\n\tUnos: ", select, BUFFER_LENGTH);
			if (strcmp(select, "Y") == 0) {
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

			} else {
				prev = tmp;
				tmp = tmp->next;
			}

		} else {
			prev = tmp;
			tmp = tmp->next;
		}
	
	}

	if (!exits)
		printf("Ne postoji nit jedna osoba s prezimenom \"%s\"\n", lastName);

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

int SortListByLastName(person *head)
{
	int i = 0, j = 0;
	int n = 0, swapped = 0;
	person **h = NULL;
	person *x = NULL;
	person *y = NULL;

	n = NumberOfElements(head);
	for (i = 0; i < n - 1; i++) {
		h = &(head->next);
		swapped = 0;

		for (j = 0; j < n - i - 1; j++) {
			x = *h;
			y = x->next;
			if (strcmp(x->lastName, y->lastName) > 0) {
				x->next = y->next;
				y->next = x;
				*h = y; // head->next = y ili prethodni->next
				swapped = 1;
			}
			h = &(*h)->next; //za j = 0, *h pokaziva na prvi pravi element tj. Head->next
					 //za  ostale iteraciji se pomicemo mjesto po mjesto od heada prema kraju liste
		}

		if (swapped == 0) // ako se niti jedan element nije zamjeno u jenoj iteraciji to onda nuzno znaci da je lista sortirana
			break; //sto znaci da je funkcija gotova
	}

	return SUCCESS;
}