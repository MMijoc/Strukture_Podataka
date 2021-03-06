/*
 *Napisati program koji pomocu vezanih listi (stabala) predstavlja strukturu direktorija.
 *Omoguciti unos novih direktorija i pod-direktorija, ispis sadrzaja direktorija i povratak u prethodni direktorij.
 *Tocnije program treba preko menija simulirati koristenje DOS naredbi: 1- "md", 2 - "cd" "dir", 3 - "cd..", 4 - "dir" i 5 - izlaz.
 */

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Source.h"


int main()
{
	CommandLine();
	return 	SUCCESS;
}

int CommandLine()
{
	TreeNode rootDirectory = { NULL, NULL, NULL };
	TreeNode *currentDirectory = &rootDirectory;
	StackNode stack = {NULL, NULL};
	int argumentsTaken = 0;
	int offset = 0;
	char *inputBuffer = NULL;
	char *command = NULL;
	char *commandArgument = NULL;
	char *path = NULL;

	if (AllocateBuffers(&path, &inputBuffer, &command, &commandArgument) == FAILURE) return FAILURE;
	SetDirectoryName(&rootDirectory, "C:");
	strcpy(path, "C:\\");

	while (TRUE) {
		memset(inputBuffer, 0, BUFFER_LENGTH);
		memset(command, 0, BUFFER_LENGTH);
		memset(commandArgument, 0, BUFFER_LENGTH);
		argumentsTaken = 0;
		offset = 0;

		printf("%s>", path);
		fgets(inputBuffer, BUFFER_LENGTH, stdin);

		argumentsTaken = sscanf(inputBuffer, "%s %s %n", command, commandArgument, &offset);

		if (_stricmp(command, "help") == 0) {
			if (argumentsTaken == 2)
				PrintHelp(commandArgument);
			else if (argumentsTaken == 1)
				PrintHelp(NULL);
			else
				printf("\nThis command is not supported by the help utility.\n");

		} else if (_stricmp(command, "md") == 0) {
			if (argumentsTaken == 1) {
				puts("The syntax of the command is incorrect.\n");
			} else {
				MakeNewDirectory(currentDirectory, commandArgument);
				while (TRUE) {
					int n = 0;
					argumentsTaken = sscanf((inputBuffer + offset), "%s %n", commandArgument, &n);
					if (argumentsTaken < 0)
						break;
					offset += n;
					MakeNewDirectory(currentDirectory, commandArgument);
				}
			}

		} else if (_stricmp(command, "cd..") == 0) {
			ReturnToPreviousDirectory(&currentDirectory, &rootDirectory, path, &stack);

		} else if (_stricmp(command, "cd") == 0) {
			if (strcmp(commandArgument, "..") == 0)
				ReturnToPreviousDirectory(&currentDirectory, &rootDirectory, path, &stack);
			else if (argumentsTaken == 1)
				printf("%s\n\n", path);
			else
				ChangeDirectory(&currentDirectory, commandArgument, path, &stack);

		} else if (_stricmp(command, "dir") == 0) {
			PrintDirectory(currentDirectory);

		} else if (_stricmp(command, "exit") == 0) {
			free(rootDirectory.directoryName);
			FreeAllMemory(path, inputBuffer, command, commandArgument, &rootDirectory, &stack);
			return SUCCESS;

		} else {
			printf("\n\'%s' is not recognized as an internal or external command, operable program or batch file.\n", command);
		}
	}

}

int PrintHelp(char *command)
{
	if (command == NULL) {
		puts(   "\nFor more information on a specific command, type HELP command - name"
			"\nCD             Displays the name of or changes the current directory."
			"\nDIR            Displays a list of files and subdirectories in a directory."
			"\nHELP           Provides Help information for Windows commands."
			"\nMD             Creates a directory.\n"
		);
		return SUCCESS;

	} else if (_stricmp(command, "cd") == 0) {
		puts(	"\nDisplays the name of or changes the current directory.\n"
			"CD[directory name]\nCD[..]\n"
			"\n  ..   Specifies that you want to change to the parent directory.\n"
			"\nType CD without parameters to display the current drive and directory.\n"
		);
		return SUCCESS;

	} else if (_stricmp(command, "dir") == 0) {
		puts(   "\nDisplays a list of files and subdirectories in a directory.\n");
		return SUCCESS;

	} else if (_stricmp(command, "help") == 0) {
		puts(	"\nProvides help information for Windows commands.\n"
			"\nHELP [command]\n"
			"\n    command - displays help information on that command.\n\n"
		);
		return SUCCESS;

	} else if (_stricmp(command, "md") == 0) {
		puts(   "\nCreates a directory.\n"	
			"\nMKDIR [drive:]path\nMD[drive:]path\n\n"
		);
		return SUCCESS;

	} else {
		puts(   "\nThis command is not supported by the help utility.\n");
		return FAILURE;
	}
}

int MakeNewDirectory(TreeNode *currentDirectory, char *newDirectoryName)
{
	TreeNode *newDirectory = NULL;
	TreeNode **tmp = NULL;

	if (FindDirectory(currentDirectory, newDirectoryName) != NULL) {
		printf("A subdirectory or file %s already exists.\n", newDirectoryName);
		return FAILURE;
	}

	newDirectory = CreateNewTreeNode(); if (NULL == newDirectory) return FAILURE;
	if (SetDirectoryName(newDirectory, newDirectoryName) == FAILURE) return FAILURE;

	if (currentDirectory->child == NULL) {
		currentDirectory->child = newDirectory;
		return SUCCESS;
	}

	tmp = &currentDirectory->child;
	while (*tmp != NULL && _stricmp((*tmp)->directoryName, newDirectoryName) < 0)
		tmp = &(*tmp)->nextSibling;

	newDirectory->nextSibling = *tmp;
	*tmp = newDirectory;

	return SUCCESS;
}

int SetDirectoryName(TreeNode *directory, char *directoryName)
{
	if (ValidatePointer(2, "Invalid function arguments", directory, directoryName)) return FAILURE;

	directory->directoryName = (char *)malloc((strlen(directoryName) + 1) * sizeof(char));
	if (ValidatePointer(1, "Failed to allocate memory for directory name", directory->directoryName)) return FAILURE;

	strcpy(directory->directoryName, directoryName);

	return SUCCESS;
}

int PrintDirectory(TreeNode *currentDirectory)
{
	TreeNode *tmp = NULL;
	int numDir = 0;

	if (currentDirectory->child == NULL) {
		printf("\n\t\t0 Dir(s)\n\n");
		return SUCCESS;
	}

	tmp = currentDirectory->child;
	
	printf("\n");
	while (tmp) {
		printf("<DIR>          %s\n", tmp->directoryName);
		numDir++;
		tmp = tmp->nextSibling;
	}
	printf("\t\t%d Dir(s)\n\n", numDir);
	
	return SUCCESS;
}

int ChangeDirectory(TreeNode **currentDirectory, char *directoryName, char *path, StackNode *stackHead)
{
	TreeNode *tmp = NULL;

	tmp = FindDirectory(*currentDirectory, directoryName);
	if (tmp == NULL) {
		printf("\nThe system cannot find the path specified.\n\n");
		return FAILURE;
	}

	if (Push(stackHead, tmp) == FAILURE) return FAILURE;
	*currentDirectory = tmp;
	if (path[strlen(path) - 1] != '\\')
		strcat(path, "\\");
	strcat(path, directoryName);

	return SUCCESS;
}

int ReturnToPreviousDirectory(TreeNode **currentDirectory, TreeNode *rootDirectory, char *path, StackNode *stackHead)
{
	char *endOfPath = NULL;
	TreeNode *dummy = NULL;
	TreeNode *newCurrentDirectory = NULL;

	Pop(stackHead, &dummy);
	if(Pop(stackHead, &newCurrentDirectory) == FAILURE) {
		*currentDirectory = rootDirectory;
		strcpy(path, rootDirectory->directoryName);
		strcat(path, "\\");
		return SUCCESS;
	}
	*currentDirectory = newCurrentDirectory;
	endOfPath = strrchr(path, '\\');
	*endOfPath = '\0';

	return SUCCESS;
}

TreeNode *FindDirectory(TreeNode *currentDirectory, char *directoryName)
{
	TreeNode *tmp = NULL;

	tmp = currentDirectory->child;
	while (tmp) {
		if (_strcmpi(tmp->directoryName, directoryName) == 0)
			return tmp;

		tmp = tmp->nextSibling;
	}

	return NULL;
}

TreeNode *CreateNewTreeNode()
{
	TreeNode *newNode = NULL;

	newNode = (TreeNode *)malloc(sizeof(TreeNode));
	if (newNode == NULL) {
		PrintError("Tree node memory allocation failed!");
		return NULL;
	}

	newNode->child = NULL;
	newNode->nextSibling = NULL;
	newNode->directoryName = NULL;

	return newNode;
}

StackNode *CreateNewStackNode()
{
	StackNode *newNode = NULL;

	newNode = (StackNode*)malloc(sizeof(StackNode));
	if (newNode == NULL) {
		PrintError("Stack node memory allocation failed!");
		return NULL;
	}

	newNode->treeNode = NULL;
	newNode->next = NULL;

	return newNode;
}

int Push(StackNode *stackHead, TreeNode *treeNode)
{
	StackNode *nodeToPush = NULL;

	nodeToPush = CreateNewStackNode();
	if (NULL == nodeToPush) return FAILURE;

	nodeToPush->treeNode = treeNode;

	nodeToPush->next = stackHead->next;
	stackHead->next = nodeToPush;

	return SUCCESS;
}

int Pop(StackNode *stackHead, TreeNode **result)
{
	StackNode *nodeToFree = NULL;

	if (NULL == stackHead->next)
		return FAILURE; // stack is empty

	*result = stackHead->next->treeNode;
	nodeToFree = stackHead->next;
	stackHead->next = stackHead->next->next;

	free(nodeToFree);
	return SUCCESS;
}

int AllocateBuffers(char **path, char **inputBuffer, char **command, char **commandArgument)
{
	*path = (char *)malloc(BUFFER_LENGTH * sizeof(char));
	*inputBuffer = (char *)malloc(BUFFER_LENGTH * sizeof(char));
	*command = (char *)malloc(BUFFER_LENGTH * sizeof(char));
	*commandArgument = (char *)malloc(BUFFER_LENGTH * sizeof(char));
	
	return ValidatePointer(4, "Memory allocation failed: failed to allocate memory for buffers", *path, *inputBuffer, *command, *commandArgument);
}

int FreeBuffers(char *path, char *inputBuffer, char *command, char *commandArgument)
{
	free(path);
	free(inputBuffer);
	free(command);
	free(commandArgument);

	return SUCCESS;
}

int FreeTree(TreeNode *T)
{
	if (T == NULL) return SUCCESS;
	FreeTree(T->child);
	FreeTree(T->nextSibling);
	free(T->directoryName);
	free(T);

	return SUCCESS;
}

int FreeStack(StackNode *S)
{
	if (S == NULL) return SUCCESS;
	FreeStack(S->next);
	free(S);

	return SUCCESS;
}

int FreeAllMemory(char* path, char* inputBuffer, char* command, char* commandArgument, TreeNode *root, StackNode* stackHead)
{
	FreeBuffers(path, inputBuffer, command, commandArgument);
	FreeStack(stackHead->next);
	FreeTree(root->child);

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

int ValidatePointer(int numberOfPointersPassed, char *errorMessage, ...)
{
	int i = 0, numOfNulls = 0;
	va_list args;

	va_start(args, errorMessage);
	for (i = 0; i < numberOfPointersPassed; i++) {
		void* ptr = va_arg(args, void *);
		if (ptr == NULL) {
			numOfNulls++;
		}
	}
	va_end(args);

	if (numOfNulls != 0) {
		PrintError(errorMessage);
		fprintf(stderr, " (%d null pointers passed)", numOfNulls);
		return FAILURE;
	}

	return SUCCESS;
}
