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
	return SUCCESS;
}

int PrintMenu()
{
	puts(	"1 - Add 10 random numbers to the tree"
		"\n2 - Insert element"
		"\n3 - Find max value"
		"\n4 - Find min value"
		"\n5 - Find element by value"
		"\n6 - Delete element by value"
		"\n7 - Print tree preorder"
		"\n8 - Print tree inorder"
		"\n9 - Print tree postorder"
		"\n10 - Delete tree"
		"\nexit - Exit program"
	);

	return SUCCESS;
}

int SelectMenu()
{
	BinTreeNode *root = NULL;
	BinTreeNode *tmp = NULL;
	char inputBuffer[BUFFER_LENGTH] = {'\0'};
	char select[BUFFER_LENGTH] = {'\0'};
	int inputNumber = 0;
	int argumentsTaken = 0;
	int testNumbers[10] = {0};
	int i = 0;

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
				testNumbers[i] = rand() % 100;
			for (i = 0; i < 10; i++)
				printf("%d ", testNumbers[i]);
			puts("");

			for (i = 0; i < 10; i++)
				root = InsertElement(root, testNumbers[i]);

		} else if (strcmp(select, "2") == 0) {
			inputNumber = InputIntegerFromUser("Enter the number you want to insert: ");
			root = InsertElement(root, inputNumber);

		} else if (strcmp(select, "3") == 0) {
			tmp = FindMaxValue(root);
			if (tmp)
				printf("Max value in this binary tree is: %d", tmp->value);
			else
				printf("Binary tree is empty!");
		
		} else if (strcmp(select, "4") == 0) {
			tmp = FindMinValue(root);
			if (tmp)
				printf("Min value in this binary tree is: %d", tmp->value);
			else
				printf("Binary tree is empty!");
			
		} else if (strcmp(select, "5") == 0) {
			inputNumber = InputIntegerFromUser("Enter the value you want to search: ");
			tmp = FindByValue(root, inputNumber);
			if (tmp)
				printf("Element with the value %d exists and it's address is %p", tmp->value, tmp);
			else
				printf("Element with the value '%d' does not exist in this binary tree!", inputNumber);

		} else if (strcmp(select, "6") == 0) {
			inputNumber = InputIntegerFromUser("Enter the value of the node you want to delete: ");
			if (root)
				root = DeleteNode(root, inputNumber);
			else
				printf("The tree is empty!");

		} else if (strcmp(select, "7") == 0) {
			if (root) {
				printf("Preorder print:");
				PrintTreePreorder(root);
			} else {
				printf("The tree is empty!");
			}

		} else if (strcmp(select, "8") == 0) {
			if (root) {
				printf("Inorder print:");
				PrintTreeInorder(root);
			} else {
				printf("The tree is empty!");
			}

		} else if (strcmp(select, "9") == 0) {
			if (root) {
				printf("Postorder print:");
				PrintTreePostorder(root);
			} else {
				printf("The tree is empty!");
			}

		} else if (strcmp(select, "10") == 0) {
			FreeBinTree(root);
			root = NULL;

		} else if (_stricmp(select, "exit") == 0) {
			FreeBinTree(root);
			return SUCCESS;

		} else {
			printf("\n\'%s' is not recognized as an valid command.\n", select);
		}

		printf("\nPress any key to continue . . .");
		fgets(select, BUFFER_LENGTH - 1, stdin);
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

BinTreeNode *FindMaxValue(BinTreeNode *node)
{
	if (NULL == node) return NULL;
	while (node->right)
		node = node->right;

	return node;
}

BinTreeNode *FindMinValue(BinTreeNode *node)
{
	if (NULL == node) return NULL;
	while (node->left)
		node = node->left;

	return node;
}

BinTreeNode *FindByValue(BinTreeNode *node, int valueToFind)
{
	if (node) {
		if (node->value == valueToFind) {
			return node;
		} else if (valueToFind > node->value) {
			return FindByValue(node->right, valueToFind);
		} else if (valueToFind < node->value) {
			return FindByValue(node->left, valueToFind);
		} else {
			return NULL;
		}
	}

	return NULL;
}

BinTreeNode* InsertElement(BinTreeNode *node, int valueToInsert)
{
	if (NULL == node) {
		BinTreeNode *nodeToInsert = NULL;

		nodeToInsert = CreateNewBinTreeNode(valueToInsert);
		if(nodeToInsert == NULL)
			return NULL;

		return nodeToInsert;

	} else if (valueToInsert < node->value) {
		node->left = InsertElement(node->left, valueToInsert);

	} else if (valueToInsert > node->value) {
		node->right = InsertElement(node->right, valueToInsert);

	} else {
		printf("\nElement with the value '%d' already exists in the binary tree!", valueToInsert);
	}

	return node;
}

BinTreeNode *DeleteNode(BinTreeNode *node, int value)
{
	if (node == NULL) {
		printf("Element with the value '%d' does not exist ins this tree", value);
		return node;
	} else if (value > node->value) {
		node->right = DeleteNode(node->right, value);
	} else if (value < node->value) {
		node->left = DeleteNode(node->left, value);
	} else {
		BinTreeNode* tmp = NULL;

		if (node->left && node->right) {
			tmp = FindMinValue(node->right);
			node->value = tmp->value;
			node->right = DeleteNode(node->right, tmp->value);

		} else {
			tmp = node;
			if (node->right == NULL)
				node = node->left;
			else
				node = node->right;
			
			free(tmp);
		}

	}

	return node;
}

int PrintTreePreorder(BinTreeNode *node)
{
	if (node)
	{
		printf(" %d", node->value);
		PrintTreePreorder(node->left);
		PrintTreePreorder(node->right);
	}

	return SUCCESS;
}

int PrintTreePostorder(BinTreeNode *node)
{
	if (node)
	{
		PrintTreePostorder(node->left);
		PrintTreePostorder(node->right);
		printf(" %d",node->value);
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

int InputIntegerFromUser(char *message)
{
	int argumentsTaken = 0;
	char inputBuffer[BUFFER_LENGTH];
	int inputNumber = 0;

	do {
		if (message && strlen(message) > 0)
			printf("%s", message);
		fgets(inputBuffer, BUFFER_LENGTH, stdin);
		argumentsTaken = sscanf(inputBuffer,  "%d%s", &inputNumber, inputBuffer);
	} while (argumentsTaken != 1);

	return inputNumber;
}

int FreeBinTree(BinTreeNode *node)
{
	if (node) {
		FreeBinTree(node->left);
		FreeBinTree(node->right);
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
