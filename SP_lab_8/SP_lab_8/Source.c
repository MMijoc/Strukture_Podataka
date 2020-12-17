#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

/*
 *Napisati program koji pomocu vezanih listi (stabala) predstavlja strukturu direktorija.
 *Omoguciti unos novih direktorija i pod-direktorija, ispis sadrzaja direktorija i povratak u prethodni direktorij.
 *Tocnije program treba preko menija simulirati koristenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE (-1)

#define BUFFER_LENGTH 1024

int main()
{
	printf("HELLO WORLD\n");
	return SUCCESS;
}