/*
 *Napisati program koji prvo procita koliko redaka ima datoteka, tj. koliko ima studenata zapisanih u datoteci.
 *Nakon toga potrebno je dinamicki alocirati prostor za niz struktura studenata (ime, prezime, bodovi)
 *i ucitati iz datoteke sve zapise. Na ekran ispisati ime, prezime,apsolutni i relativni broj bodova.
 *Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
 *relatvan_br_bodova = br_bodova/max_br_bodova*100
 */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_LENGTH 1024
#define ERROR INT_MIN
#define MAX_SCORE 100 //max br bodova

typedef struct _student {
	char name[BUFFER_LENGTH];
	char lastName[BUFFER_LENGTH];
	int score;
} student;


int NumberOfStudents(char *file_name);
bool InputFromFile(char *fileName, student *list, int numStudents);
bool PrintStudents(student *list, int num);
float RelativeScore(int points, int max_points);

int main()
{
	int n = 0;
	bool isError = false;
	student *studentList = NULL;
	char fileName[BUFFER_LENGTH];

	strcpy(fileName, "studenti");

	//printf("Unesite ime datoteke: ");
	//scanf(" %s", fileName);

	n = NumberOfStudents(fileName);
	if (n < 0) return EXIT_FAILURE;

	studentList = (student *)malloc(n * sizeof(student));
	if (studentList == NULL)
		return -1;

	isError = InputFromFile("studenti.txt", studentList, n);
	if (isError) return EXIT_FAILURE;
	PrintStudents(studentList, n);

	free(studentList);
	return EXIT_SUCCESS;
}

int NumberOfStudents(char *fileName)
{
	FILE *fp = NULL;
	int result = 0;

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		perror("ERROR");
		return ERROR;
	}

	while (!feof(fp)) {
		fscanf(fp, "%*s %*s %*d");
		result++;
	}

	fclose(fp);
	return result;
}

bool InputFromFile(char *fileName, student *list, int numStudents)
{
	FILE *fp = NULL;

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		perror("ERROR");
		return EXIT_FAILURE;
	}

	for (int i = 0; i < numStudents; i++)
		fscanf(fp, "%s %s %d", list[i].name, list[i].lastName, &list[i].score);

	fclose(fp);
	return EXIT_SUCCESS;
}

bool PrintStudents(student *list, int num)
{
	printf("%-16s %-16s %-8s %-8s", "Name", "Last Name", "Score", "Relativ Score\n");
	for (int i = 0; i < num; i++)
		printf("%-16s %-16s %-8d %8.2f\n", list[i].name, list[i].lastName, list[i].score, RelativeScore(list[i].score, MAX_SCORE));

	return EXIT_SUCCESS;
}

float RelativeScore(int points, int maxPoints)
{
	return (points / (float)maxPoints) * 100;
}