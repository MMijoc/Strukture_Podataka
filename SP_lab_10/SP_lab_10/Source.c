/*
* Napisati program koji iz datoteke cita postfiks izraz i zatim stvara stablo proracuna.
* Iz gotovog stabla proracuna upisati u datoteku infiks izraz.
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Source.h"

int main()
{
	char fileName[BUFFER_LENGTH];
	char *postifx = NULL;
	BinTreeNode *root = NULL;

	strcpy(fileName, "postfix");
	postifx = GetFileContent(fileName);
	if (postifx == NULL) return FAILURE;

	printf("Postfix expression: %s\n", postifx);
	CreateExpressionTree(&root, postifx);
	printf("Infix expression:   ");
	PrintTreeInorder(root);
	puts("");

	FreeBinTree(root);
	free(postifx);
	return SUCCESS;
}

char *GetFileContent(char *fileName)
{
	char *fileContent = NULL;
	FILE *fp = NULL;
	int length = 0;

	if (strstr(fileName, ".txt") == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		perror("ERROR");
		return NULL;
	}

	fseek(fp, 0, SEEK_END);
	length = ftell(fp) + 1; // +1 for '\0'

	fileContent = (char *)malloc(length * sizeof(char));
	if (fileContent == NULL) {
		fprintf(stderr, "\nMemory allocation failed");
		return NULL;
	}

	fseek(fp, 0, SEEK_SET);
	fgets(fileContent, length, fp);
	fclose(fp);

	return fileContent;
}

BinTreeNode *CreateNewBinTreeNode(char *element)
{
	BinTreeNode *newNode = NULL;

	newNode = (BinTreeNode *)malloc(sizeof(BinTreeNode));
	if (newNode) {
		newNode->left = NULL;
		newNode->right = NULL;
		strcpy(newNode->element, element);
		return newNode;

	} else {
		fprintf(stderr, "\nMemory allocation failed");
		return NULL;
	}
}

int InitStack(Stack *S)
{
	S->binNode = NULL;
	S->next = NULL;

	return SUCCESS;
}

StackNode *CreateNewStackNode(BinTreeNode *binNode)
{
	StackNode *newNode = NULL;

	newNode = (StackNode *)malloc(sizeof(StackNode));
	if (NULL == newNode) {
		perror("Memory allocation failed:");
		return NULL;
	}

	newNode->binNode = binNode;
	newNode->next = NULL;

	return newNode;
}

int Push(StackNode *stackHead, BinTreeNode *binNode)
{
	StackNode *nodeToPush = NULL;
	if (IsNull(2, "Invalid function parameters" ,stackHead, binNode)) return FAILURE;

	nodeToPush = CreateNewStackNode(binNode);
	if (NULL == nodeToPush) return FAILURE;

	nodeToPush->next = stackHead->next;
	stackHead->next = nodeToPush;

	return SUCCESS;
}

int Pop(StackNode *stackHead, BinTreeNode **result)
{
	StackNode *nodeToPop = NULL;

	if (IsNull(2, "Invalid function parameters" ,stackHead, result)) return FAILURE;
	
	nodeToPop = stackHead->next;
	if (NULL == nodeToPop)	return FAILURE;

	*result = nodeToPop->binNode;
	stackHead->next = stackHead->next->next;
	free(nodeToPop);

	return SUCCESS;
}

int CreateExpressionTree(BinTreeNode **root, char *postfix)
{
	int executionStatus = SUCCESS;
	int argTaken = 0, n = 0;
	char element[ELEMENET_SIZE] = {'\0'};
	Stack stack;
	InitStack(&stack);

	while (*postfix != '\0' && executionStatus == SUCCESS) {
		argTaken = sscanf(postfix, "%s%n", element, &n);

		if (argTaken != 1) return FAILURE;

		if (IsNnumber(element)) {
			Push(&stack, CreateNewBinTreeNode(element));
		} else {
			BinTreeNode * operatorNode = NULL;

			argTaken = sscanf(postfix, "%s%n", element, &n);
			

			if (element[0] == ' ') {
				postfix += 1;
				continue;
			}
			if (!IsValidOperator(element[0])) return FAILURE;

			operatorNode = CreateNewBinTreeNode(element); 
			if (operatorNode == NULL) return FAILURE;

			executionStatus = Pop(&stack, &(operatorNode->right));
			executionStatus = Pop(&stack, &(operatorNode->left));

			Push(&stack, operatorNode);
		}

		postfix += n;
	}

	Pop(&stack, root);
	// error checking needs to be fixed
	FreeStack(stack.next);
	return SUCCESS;
}

int PrintTreeInorder(BinTreeNode *node)
{
	if (node) {

		PrintTreeInorder(node->left);
		printf("%s ", node->element);
		PrintTreeInorder( node->right);
	}

	return SUCCESS;
}

int FreeBinTree(BinTreeNode *node)
{
	if (node) {
		FreeBinTree(node->left);
		FreeBinTree(node->right);
	}

	return SUCCESS;
}

int FreeStack(Stack *S)
{
	if (S == NULL) return SUCCESS;
	FreeStack(S->next);
	free(S);

	return SUCCESS;
}

int IsNnumber(char *element)
{
	int argumentsTaken = 0;
	double dummy1;
	char dummy2[ELEMENET_SIZE];
	argumentsTaken = sscanf(element, "%lf%s", &dummy1, dummy2);
	if (argumentsTaken != 1)
		return FALSE;
	else
		return TRUE;
}

int IsValidOperator(char operation)
{
	switch (operation)
	{
	case '+':
		break;
	case '-':
		break;
	case '*':
		break;
	case '/':
		break;
	default:
		printf("Invalid operation");
		return FALSE;
	}

	return TRUE;
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