/*
 *Napisati kod koji za zadane podatke studenata (maticni broj, ime i prezime) pravi hash tablicu sa zasebnim redovima.
 *Tablica ima 11 mjesta, a funkcija za preslikavanje kljuc racuna da se zbraja ASCII vrijednost prvih pet slova prezimena
 *i zatim racuna ostatak cjelobrojnog dijeljenja te vrijednosti s velicinom tablice.
 *Studenti s istim kljucem se pohranjuju u vezanu listu sortiranu po prezimenima i imenima.
 *Kada se tablica izgradi treba ispisati cijelu tablicu (naglasiti na kojem kljucu se nalaze koji podaci)
 *te ponuditi mogucnost da se za odredjenog studenta (prezime i ime) ispise njegov maticni broj.
 */

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Source.h"

int main()
{
	//HashTable hashTable[TABLE_SIZE];
	//InitHashTable(hashTable, TABLE_SIZE);


	HashTable *hashTable = NULL;
	hashTable = CreateHashTable(TABLE_SIZE);
	if (hashTable == NULL) return FAILURE;



	HashTableInsert(hashTable, TABLE_SIZE, CreateNewPerson("Dennis", "Ritchie", "Dennis-ID"));
	HashTableInsert(hashTable, TABLE_SIZE, CreateNewPerson("Bjarne", "Stroustrup", "Bjarne-ID"));
	HashTableInsert(hashTable, TABLE_SIZE, CreateNewPerson("Linus", "Torvalds", "Linus-ID"));
	HashTableInsert(hashTable, TABLE_SIZE, CreateNewPerson("Alan", "Turing", "Alan-ID"));
	HashTableInsert(hashTable, TABLE_SIZE, CreateNewPerson("John Ronald Reuel", "Tolkien", "JRR-ID"));
	HashTableInsert(hashTable, TABLE_SIZE, CreateNewPerson("Christopher", "Tolkien", "Christopher-ID"));
	HashTableInsert(hashTable, TABLE_SIZE, CreateNewPerson("Floor", "Jansen", "Floor-ID"));
	HashTableInsert(hashTable, TABLE_SIZE, CreateNewPerson("Irene", "Jansen", "Irene-ID"));
	HashTableInsert(hashTable, TABLE_SIZE, CreateNewPerson("Ahsoka", "Tano", "Ahsoka-ID"));
	HashTableInsert(hashTable, TABLE_SIZE, CreateNewPerson("Tommy", "Karevik", "Tommy-ID"));
	HashTableInsert(hashTable, TABLE_SIZE, CreateNewPerson("Quentin", "Tarantino", "Quentin-ID"));
	HashTableInsert(hashTable, TABLE_SIZE, CreateNewPerson("Ardal", "aep Dahy", "Ardal-ID"));

	PrintTable(hashTable, TABLE_SIZE);

	FreeHashTable(hashTable, TABLE_SIZE);
	return SUCCESS;
}

Node *CreateNewNode(Person *person)
{
	Node *newNode = NULL;
	
	newNode = (Node *)malloc(sizeof(Node));
	if (newNode) {
		newNode->next = NULL;
		newNode->person = person;
		return newNode;
	} else {
		PrintError("Memory allocation failed: unable to allocate memory for list node");
		return NULL;
	}
}

Person *CreateNewPerson(char *firstName, char *lastName, char *id)
{
	Person *newPerson = NULL;

	newPerson = (Person *)malloc(sizeof(Person));
	if (newPerson) {
		strncpy(newPerson->firstName, firstName, NAME_LENGTH);
		strncpy(newPerson->lastName, lastName, NAME_LENGTH);
		strncpy(newPerson->id, id, ID_LENGTH);
		return newPerson;
	} else {
		PrintError("Memory allocation failed: unable to allocate memory for person");
		return NULL;
	}
}

HashTable *CreateHashTable(int tableSize)
{
	HashTable *newHashTable = NULL;
	if (tableSize <= 0) {
		PrintError("Invalid table size!");
		return NULL;
	}

	newHashTable = (Node *)malloc(tableSize * sizeof(Node));
	if (newHashTable) {
		InitHashTable(newHashTable, tableSize);
		return newHashTable;
	} else {
		PrintError("Memory allocation failed: unable to allocate memory for the hash table");
		return NULL;
	}
}

int InitHashTable(HashTable *table, int tableSize)
{
	int i = 0;
	for (i = 0; i < tableSize; i++) {
		table[i].person = NULL;
		table[i].next = NULL;
	}

	return SUCCESS;
}

int Hash(char *key, int tableSize)
{
	int hashValue = 0;
	int i = 0;

	if (key == NULL || strlen(key) == 0 || tableSize <= 0)
		return FAILURE;

	for (i = 0; i < CHARS_HASHING && key[i] != '\0'; i++)
		hashValue += key[i];

	return hashValue % tableSize;
}

int HashTableInsert(HashTable *table, int tableSize, Person *toInsert)
{
	int hashValue = 0;

	hashValue = Hash(toInsert->lastName, tableSize);
	if (hashValue < 0) return FAILURE;

	SortedInsert(&(table[hashValue]), toInsert);

	return SUCCESS;
}

int SortedInsert(Node *listHead, Person *personToInsert)
{
	Node *nodeToInsert = NULL;
	Node *tmp = NULL;

	if (IsNull(2, "Invalid function arguments", listHead, personToInsert) == TRUE) return FAILURE;

	nodeToInsert = CreateNewNode(personToInsert);
	if (nodeToInsert == NULL) return FAILURE;

	if (listHead->next == NULL) {
		listHead->next = nodeToInsert;
		return SUCCESS;
	}

	tmp = listHead;
	while (tmp->next != NULL && _stricmp(tmp->next->person->lastName, nodeToInsert->person->lastName) < 0)
		tmp = tmp->next;

	if (tmp->next != NULL && (_stricmp(tmp->next->person->firstName, nodeToInsert->person->firstName) == 0)) {
		while (tmp->next != NULL && (_stricmp(tmp->next->person->firstName, nodeToInsert->person->firstName) < 0))
			tmp = tmp->next;

	}

	nodeToInsert->next = tmp->next;
	tmp->next = nodeToInsert;


	return SUCCESS;
}

int PrintTable(HashTable *table, int tableSize)
{
	int i = 0;

	for (i = 0; i < tableSize; i++) {
		printf("%d\t", i);
		PrintList(&table[i]);
	}

	return SUCCESS;
}

int PrintList(Node *listHead)
{
	Node *tmp = listHead->next;

	if (NULL == tmp) {
		printf("EMPTY\n");
		return FAILURE;
	}

	while (tmp) {
		PrintPerson(tmp->person);
		printf("  -->  ");
		tmp = tmp->next;
	}
	printf("\n");

	return SUCCESS;
}

int PrintPerson(Person *p)
{
	printf("\033[31m[%s - %s - %s]\033[0m", p->firstName, p->lastName, p->id);
	return SUCCESS;
}



int FreeHashTable(HashTable *table, int tableSize)
{
	int i = 0;

	for (i = 0; i < tableSize; i++) {
		FreeList(&table[i]);
	}

	free(table);
	table = NULL;

	return SUCCESS;
}

int FreeList(Node *head)
{
	Node *toFree = NULL;
	Node* tmp = head->next;
	while(tmp) {
		toFree = tmp;
		tmp = tmp->next;
		free(toFree);
	}

	head->next = NULL;
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

int ConsoleInput(const char *message, char *buffer, size_t bufferSize)
{
	char *end;
	if (message != NULL)
		printf("%s", message);
	memset(buffer, '\0', bufferSize);
	fgets(buffer, bufferSize - 1, stdin);
	end = strchr(buffer, '\n');
	if (end)
		*end = '\0';

	return SUCCESS;
}

int IsNull(int numberOfPointersPassed, char *errorMessage, ...)
{
	int i = 0;
	int isNull = FALSE;
	va_list args;

	va_start(args, errorMessage);
	for (i = 0; i < numberOfPointersPassed; i++) {
		void* ptr = va_arg(args, void *);
		if (ptr == NULL) {
			if (errorMessage)
				fprintf(stderr, "\n%s", errorMessage);
			return TRUE;
		}
	}
	va_end(args);

	return FALSE;
}
