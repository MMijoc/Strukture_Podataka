/*
 * Napisati program koji omogucava rad s binarnim stablom pretrazivanja.
 * Treba omoguciti unosenje novog elementa u stablo, ispis elemenata, brisanje i pronalazenje nekog elementa.
 */

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Source.h"

int main()
{
	SelectMenu();
	return 	SUCCESS;
}


int PrintMenu()
{
	puts(	"1 - Make new tree with random numbers"
		"\n2 - Insert element"
		"\n3 - Find max value"
		"\n4 - Find min value"
		"\n4 - Delete element by value"
		"\n5 - Delete tree"
		"\nexit - Exit program"
	);

	return SUCCESS;
}

int SelectMenu()
{
	char tmpBuffer[BUFFER_LENGTH] = {'\0'};
	char inputBuffer[BUFFER_LENGTH] = {'\0'};
	char select[BUFFER_LENGTH] = {'\0'};
	int argumentsTaken = 0;

	while (TRUE) {

		PrintMenu();
		argumentsTaken = 0;
		do {
			printf("Choose: ");
			fgets(inputBuffer, BUFFER_LENGTH, stdin);
			argumentsTaken = sscanf(inputBuffer, "%s", select);

		} while (argumentsTaken < 0);


		if (strcmp(select, "1") == 0) {
		

		} else if (strcmp(select, "2") == 0) {
			

		} else if (strcmp(select, "3") == 0) {
		
		} else if (strcmp(select, "4") == 0) {
			

		} else if (strcmp(select, "5") == 0) {
			
		} else if (strcmp(select, "6") == 0) {
			
		} else if (_stricmp(select, "exit") == 0) {
			//free memory
			return SUCCESS;

		} else {
			printf("\n\'%s' is not recognized as an valid command.\n", select);
		}

		printf("\nPress any key to continue . . .");
		fgets(tmpBuffer, BUFFER_LENGTH - 1, stdin);
		system("cls");
	}

}
