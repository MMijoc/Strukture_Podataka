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
	return SelectMenu();
}

int PrintMenu()
{
	puts(	"1 - Fill hash table with test data"
		"\n2 - Insert element to the hash table"
		"\n3 - Print entire hash table"
		"\n4 - Find ID by full name"
		"\nexit - Exit program"
	);

	return SUCCESS;
}

int SelectMenu()
{
	HashTable *hashTable = NULL;
	Person *tmp = NULL;
	char inputBuffer[BUFFER_LENGTH] = {'\0'};
	char select[BUFFER_LENGTH] = {'\0'};
	char tmpFirstName[NAME_LENGTH] = {'\0'};
	char tmpLastName[NAME_LENGTH] = {'\0'};
	char tmpId[ID_LENGTH]  = {'\0'};
	int executionStatus = SUCCESS;
	int argumentsTaken = 0;


	hashTable = CreateHashTable(TABLE_SIZE);
	if (hashTable == NULL) return FAILURE;

	while (TRUE) {

		PrintMenu();
		argumentsTaken = 0;
		do {
			printf("Choose: ");
			fgets(inputBuffer, BUFFER_LENGTH, stdin);
			argumentsTaken = sscanf(inputBuffer, "%s", select);

		} while (argumentsTaken < 0);

		if (strcmp(select, "1") == 0) {
			FillWithTestData(hashTable, TABLE_SIZE);
		} else if (strcmp(select, "2") == 0) {
			printf("\nEnter new person's first name, last name and Id:\n");
			ConsoleInput("First name: ", tmpFirstName, NAME_LENGTH);
			ConsoleInput("Last name: ", tmpLastName, NAME_LENGTH);
			ConsoleInput("Id: ", tmpId, ID_LENGTH);
			HashTableInsert(hashTable, TABLE_SIZE, CreateNewPerson(tmpFirstName, tmpLastName, tmpId));

		} else if (strcmp(select, "3") == 0) {
			PrintTable(hashTable, TABLE_SIZE);
		} else if (strcmp(select, "4") == 0) {
			printf("\nEnter the first and the last name of the person you are searching:\n");
			ConsoleInput("First name: ", tmpFirstName, NAME_LENGTH);
			ConsoleInput("Last name: ", tmpLastName, NAME_LENGTH);
			tmp = HashTableLookup(hashTable, TABLE_SIZE, tmpFirstName, tmpLastName);
			if (tmp)
				PrintPerson(tmp);

		} else if (_stricmp(select, "exit") == 0) {
			FreeHashTable(hashTable, TABLE_SIZE);
			return SUCCESS;

		} else {
			printf("\n\'%s' is not recognized as an valid command.\n", select);
		}

		printf("\nPress any key to continue . . .");
		fgets(select, BUFFER_LENGTH - 1, stdin);
		system("cls");
	}

	FreeHashTable(hashTable, TABLE_SIZE);

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
		strcpy(newPerson->firstName, firstName);
		strcpy(newPerson->lastName, lastName);
		strcpy(newPerson->id, id);
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

	if (key == NULL || strlen(key) == 0 || tableSize <= 0) {
		PrintError("Invalid hash functions parameters");
		return FAILURE;
	}

	for (i = 0; i < CHARS_HASHING && key[i] != '\0'; i++)
		hashValue += key[i];

	return hashValue % tableSize;
}

int HashTableInsert(HashTable *table, int tableSize, Person *toInsert)
{
	int hashValue = -1;

	if (IsNull(2, "Invalid functions arguments", table, toInsert) == TRUE) return FAILURE;

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
		printf("  -->  EMPTY\n");
		return FAILURE;
	}

	while (tmp) {
		printf("  -->  ");
		PrintPerson(tmp->person);
		tmp = tmp->next;
	}
	printf("\n");

	return SUCCESS;
}

int PrintPerson(Person *p)
{
	printf("\033[94m[%s, %s, %s]\033[0m", p->firstName, p->lastName, p->id);
	return SUCCESS;
}

Person *HashTableLookup(HashTable *table, int tableSize, char *firstName, char *lastName)
{
	int hashValue = -1;

	if (IsNull(3, "Invalid functions arguments", table, firstName, lastName) == TRUE || tableSize < 0) return NULL;
	if (strlen(firstName) == 0 ||strlen(lastName) == 0) {
		printf("First and last name can not be empty!");
		return NULL;
	}

	hashValue = Hash(lastName, tableSize);
	if (hashValue < 0) return NULL;

	return SearchList(&table[hashValue], firstName, lastName);
}

Person *SearchList(Node *listHead, char *firstName, char *lastName)
{
	Node *tmp = NULL;

	if (IsNull(3, "Invalid functions arguments", listHead, firstName, lastName) == TRUE) return NULL;

	tmp = listHead->next;
	while (tmp)
	{
		if(_strcmpi(tmp->person->lastName, lastName) == 0 &&
		   _strcmpi(tmp->person->firstName, firstName) == 0)
			return tmp->person;

		tmp = tmp->next;
	}

	printf("Person '%s %s' does not exit in this table", firstName, lastName);
	return NULL;
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
	Node* tmp = head;

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
		fprintf(stderr, "\033[31m\nUnknown error occurred!\033[0m");
		return SUCCESS;
	}
	fprintf(stderr, "\033[31m\n%s\033[0m", message);

	return SUCCESS;
}

int ConsoleInput(const char *message, char *buffer, size_t bufferSize)
{
	char *end = NULL;
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
				fprintf(stderr, "\033[31m\n%s\033[0m", errorMessage);
			return TRUE;
		}
	}
	va_end(args);

	return FALSE;
}

int FillWithTestData(HashTable *hashTable, int tableSize)
{
	if (hashTable == NULL ||tableSize <= 0) {
		PrintError(NULL);
		return FAILURE;
	}

	HashTableInsert(hashTable, tableSize, CreateNewPerson("Dennis", "Ritchie", "Dennis-ID"));
	HashTableInsert(hashTable, tableSize, CreateNewPerson("Bjarne", "Stroustrup", "Bjarne-ID"));
	HashTableInsert(hashTable, tableSize, CreateNewPerson("Linus", "Torvalds", "Linus-ID"));
	HashTableInsert(hashTable, tableSize, CreateNewPerson("Alan", "Turing", "Alan-ID"));
	HashTableInsert(hashTable, tableSize, CreateNewPerson("John Ronald Reuel", "Tolkien", "JRR-ID"));
	HashTableInsert(hashTable, tableSize, CreateNewPerson("Christopher", "Tolkien", "Christopher-ID"));
	HashTableInsert(hashTable, tableSize, CreateNewPerson("Floor", "Jansen", "Floor-ID"));
	HashTableInsert(hashTable, tableSize, CreateNewPerson("Irene", "Jansen", "Irene-ID"));
	HashTableInsert(hashTable, tableSize, CreateNewPerson("Ahsoka", "Tano", "Ahsoka-ID"));
	HashTableInsert(hashTable, tableSize, CreateNewPerson("Tommy", "Karevik", "Tommy-ID"));
	HashTableInsert(hashTable, tableSize, CreateNewPerson("Quentin", "Tarantino", "Quentin-ID"));
	HashTableInsert(hashTable, tableSize, CreateNewPerson("Ardal", "aep Dahy", "Ardal-ID"));
	HashTableInsert(hashTable, tableSize, CreateNewPerson("Aurelije", "Augustin", "Aurelije-ID"));
	HashTableInsert(hashTable, tableSize, CreateNewPerson("Hansi", "Kursch", "Hansi-ID"));
	HashTableInsert(hashTable, tableSize, CreateNewPerson("Anthony Arjen", "Lucassen", "Anthony-ID"));
	HashTableInsert(hashTable, tableSize, CreateNewPerson("James", "LaBrie", "James-ID"));
	HashTableInsert(hashTable, tableSize, CreateNewPerson("Pierre", "de Fermat", "Pierre-ID"));
	HashTableInsert(hashTable, tableSize, CreateNewPerson("Garrus", "Vakarian", "Garrus-ID"));
	HashTableInsert(hashTable, tableSize, CreateNewPerson("Christoph", "Waltz", "Christoph-ID"));
	HashTableInsert(hashTable, tableSize, CreateNewPerson("Piet", "Mondrian", "Piet-ID"));

	printf("Hash table successfully filed with 20 samples");

	return SUCCESS;
}
