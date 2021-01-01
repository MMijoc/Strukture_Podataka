#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define SUCCESS 0
#define FAILURE (-1)
#define TRUE 1
#define FALSE 0
#define BUFFER_LENGTH 1024
#define NAME_LENGTH 128
#define ID_LENGTH 32
#define TABLE_SIZE (11)
#define CHARS_HASHING 5

typedef struct _person {
	char firstName[NAME_LENGTH];
	char lastName[NAME_LENGTH];
	char id[ID_LENGTH];
} Person;

typedef struct _node {
	Person *person;

	struct _node *next;
} Node;
typedef Node HashTable;

int PrintMenu();
int SelectMenu();
Node *CreateNewNode(Person *person);
Person *CreateNewPerson(char *firstName, char *lastName, char *id);
HashTable *CreateHashTable(int tableSize);
int InitHashTable(HashTable *table, int tableSize);
int Hash(char *key, int tableSize);
int HashTableInsert(HashTable *table, int tableSize, Person *toInsert);
int SortedInsert(Node *listHead, Person *personToInsert);
int PrintTable(HashTable *table, int tableSize);
int PrintList(Node *listHead);
int PrintPerson(Person *p);
Person *HashTableLookup(HashTable *table, int tableSize, char *firstName, char *lastName);
Person *SearchList(Node *listHead, char *firstName, char *lastName);
int FreeHashTable(HashTable *table, int tableSize);
int FreeList(Node *head);
int PrintError(char *message);
int ConsoleInput(const char *message, char *buffer, size_t bufferSize);
int IsNull(int numberOfPointersPassed, char *errorMessage, ...);
int FillWithTestData(HashTable *hashTable, int tableSize);
