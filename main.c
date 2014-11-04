#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "list.h"



int main(int argc, char *argv[]) {

	int iRC;

	list_t *pListOfNumbers;
	list_t *pListOfNames;

	int pSomeNumbers[] = { 3, 7, 8, 1 , 2, 6, 5, 9, 10, 4 };
	char pSomeNames[10][20] = { "John", "Fred", "Davis" , "Adam", "Mike",
	                            "Larry", "Charlie", "Baker" , "Dan", "Edwin" };

	node_t *pValue;
	int i;

	iRC=EXIT_SUCCESS;

	if (argc != 1) {
		// one arg fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		fprintf(stderr, "Usage: %s \n", argv[0]);
		iRC=EXIT_FAILURE;
		exit(iRC);
	}


	//
	// Demo the list with a list of integers
	//
	

	// Create a linked list of integers.
	pListOfNumbers = init_list();
	if (NULL == pListOfNumbers) {
		printf("Failed ot init list.\n");
	}

	// add a few numbers to the list
	for (i=0; i<10; i++) {
		if ( append(pListOfNumbers, &pSomeNumbers[i]) ) {
			printf("Failed to append number to list.\n");
		}	
	}

	// dump the list starting with the head
	pValue = pListOfNumbers->pFirst;
	while ( NULL != pValue) {
			printf("List item as number is %d.\n", * ((int *) pValue->pData));
			pValue = pValue->pNext;
	}

	//
	// Demo the list with a list of strings
	//
	
#ifdef thomas
#endif	

	// Create a linked list of names.
	pListOfNames = init_list();
	if (NULL == pListOfNames) {
		printf("Failed ot init list.\n");
	}

	// add a few numbers to the list
	for (i=0; i<10; i++) {
		if ( append(pListOfNames, &pSomeNames[i][0]) ) {
			printf("Failed to append number to list.\n");
		}	
	}

	// dump the list starting with the head
	pValue = pListOfNames->pFirst;
	while ( NULL != pValue) {
			printf("List item as string is %s.\n",  ((char *) pValue->pData));
			pValue = pValue->pNext;
	}

	//
	// Sort the list of integers and dump them
	//
	sort_list_as_int(pListOfNumbers);

	exit(iRC);

}



