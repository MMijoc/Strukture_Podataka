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
	CreateNewBinTreeNode(5);
	SelectMenu();
	return 	SUCCESS;
}


int PrintMenu()
{
	puts(	"1 - Make new tree with random numbers"
		"\n2 - Insert element"
		"\n3 - Find max value"
		"\n4 - Find min value"
		"\n5 - Delete element by value"
		"\n6 - Delete tree"
		"\nexit - Exit program"
	);

	return SUCCESS;
}

int SelectMenu()
{
	BinTreeNode *root = NULL;
	char tmpBuffer[BUFFER_LENGTH] = {'\0'};
	char inputBuffer[BUFFER_LENGTH] = {'\0'};
	char select[BUFFER_LENGTH] = {'\0'};
	int argumentsTaken = 0;

	// test data
	int testNumbers[10];
	int i = 0;
	for (i = 0; i < 10; i++)
		testNumbers[i] = rand() % 100;


	while (TRUE) {

		PrintMenu();
		argumentsTaken = 0;
		do {
			printf("Choose: ");
			fgets(inputBuffer, BUFFER_LENGTH, stdin);
			argumentsTaken = sscanf(inputBuffer, "%s", select);

		} while (argumentsTaken < 0);

		if (strcmp(select, "1") == 0) {

			for (i = 0; i < 10; i++)
				printf("%d ", testNumbers[i]);
			puts("");

			for (i = 0; i < 10; i++)
				InsertElement(&root, testNumbers[i]);


			PrintTreeInorder(root);





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

BinTreeNode *CreateNewBinTreeNode(int value)
{
	BinTreeNode *newNode = NULL;

	newNode = (BinTreeNode *)malloc(sizeof(BinTreeNode));
	if (newNode) {
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->value = value;
		return newNode;

	} else {
		PrintError("Memory allocation failed");
		return NULL;
	}
}

int InsertElement(BinTreeNode **node, int valueToInsert)
{
	if (*node == NULL) {
		BinTreeNode *nodeToInsert = NULL;
		nodeToInsert = CreateNewBinTreeNode(valueToInsert);
		if(nodeToInsert == NULL) return FAILURE;
		*node = nodeToInsert;
		return SUCCESS;

	} else if (valueToInsert < (*node)->value) {
		InsertElement(&(*node)->left, valueToInsert);

	} else if (valueToInsert > (*node)->value) {
		InsertElement(&(*node)->right, valueToInsert);

	} else {
		printf("\nElement with the value '%d' already exists in the binary tree!", valueToInsert);
		return FAILURE;
	}
	return SUCCESS;
}

int PrintTreeInorder(BinTreeNode *node)
{
	if (node) {
		PrintTreeInorder(node->left);
		printf(" %d", node->value);
		PrintTreeInorder( node->right);
	}

	return SUCCESS;
}

int PrintError(char *errorMessage)
{
	if (errorMessage == NULL) {
		fprintf(stderr, "\nUnknown Error!");
		return SUCCESS;
	} else {
		fprintf(stderr, "\n");
		fprintf(stderr, errorMessage);
	}

	return SUCCESS;
}