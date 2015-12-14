#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"
#include "list.h"

list_t * create_list_of_names(char pSomeNames[][20], int num_elems) {

	int i;
	list_t *pListOfNames;

	// Create a linked list of integers.
	pListOfNames = init_list(compare_strings);
	if (NULL == pListOfNames) {
		printf("Failed ot init list.\n");
	}

	//
	// add a few Names to the list
	//

	// Determine number of items in the list
	for (i=0; i<num_elems; i++) {
		if ( append(pListOfNames, &pSomeNames[i]) ) {
			printf("Failed to append number to list.\n");
		}	
	}

	return pListOfNames;
}

list_t * create_list_of_numbers(int *pSomeNumbers, int num_elems) {

	int i;
	list_t *pListOfNumbers;

	// Create a linked list of integers.
	pListOfNumbers = init_list(compare_ints);
	if (NULL == pListOfNumbers) {
		printf("Failed ot init list.\n");
	}

	//
	// add a few numbers to the list
	//
	for (i=0; i<num_elems; i++) {
		if ( append(pListOfNumbers, &pSomeNumbers[i]) ) {
			printf("Failed to append number to list.\n");
		}	
	}

	return pListOfNumbers;
}

list_t * create_empty_list() {
	list_t *pListEmpty;
	// Create a empty list
	pListEmpty = init_list(compare_ints);
	if (NULL == pListEmpty) {
		printf("Failed ot init list.\n");
	}
	return pListEmpty;
	
}

int main(int argc, char *argv[]) {

	int iRC;

	list_t *pListOfNumbers;
	list_t *pListOfNames;
	list_t *pListEmpty;
	list_t *pListSortedNumbers;
	list_t *pListSortedNames;
	node_t *pNode;


	int pSomeNumbers[] = { 3, 7, 8, 1 , 2, 6, 5, 9, 10, 4 };
	// small test set for gdb int pSomeNumbers[] = { 1 , 2, 3 };
	char pSomeNames[10][20] = { "John", "Fred", "Davis" , "Adam", "Mike",
	                            "Larry", "Charlie", "Baker" , "Dan", "Edwin" };

	iRC=EXIT_SUCCESS;

	if (argc != 1) {
		// one arg fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		fprintf(stderr, "Usage: %s \n", argv[0]);
		iRC=EXIT_FAILURE;
		exit(iRC);
	}



	//
	// Create some lists
	//
	pListOfNumbers = create_list_of_numbers(pSomeNumbers, sizeof pSomeNumbers/sizeof pSomeNumbers[0]);
	pListOfNames = create_list_of_names(pSomeNames, sizeof pSomeNames/sizeof pSomeNames[0]);
	pListEmpty = create_empty_list();
//	pListSortedNumbers = create_empty_list();


	// Test list empty
	if ( is_list_empty(pListOfNumbers) ) {
		printf("FAIL: pListOfNumbers identified as empty but its not.\n");
	} else {
		printf("PASS: pListOfNumbers identified correctly as non-empty.\n");
	}

	if ( is_list_empty(pListOfNames) ) {
		printf("FAIL: pListOfNames identified as empty but its not.\n");
	} else {
		printf("PASS: pListOfNames identified correctly as non-empty.\n");
	}

	if ( is_list_empty(pListEmpty) ) {
		printf("PASS: pListEmpty identified correctly as empty.\n");
	} else {
		printf("FAIL: pListEmpty identified as non-empty but its not.\n");
	}

	//
	// Test merged routine with ints
	//
	// dump the list starting with the head
	printf("list of ints before sort\n");
	pNode = pListOfNumbers->pFirst;
	while ( NULL != pNode) {
			printf("List item as number is %d.\n", * ((int *) pNode->pData));
			pNode = pNode->pNext;
	}
	printf("-----------------\n");
	pListSortedNumbers = merge_sort(pListOfNumbers);
	printf("list of ints after sort\n");
	// dump the list starting with the head
	pNode = pListSortedNumbers->pFirst;
	while ( NULL != pNode) {
			printf("List item as number is %d.\n", * ((int *) pNode->pData));
			pNode = pNode->pNext;
	}

	printf("=================\n");
	//
	// Test merged routine with strings
	//
	// dump the list starting with the head
	pNode = pListOfNames->pFirst;
	while ( NULL != pNode) {
			printf("List item as string is %s.\n",  ((char *) pNode->pData));
			pNode = pNode->pNext;
	}
	printf("-----------------\n");
	pListSortedNames = merge_sort(pListOfNames);
	pNode = pListSortedNames->pFirst;
	while ( NULL != pNode) {
			printf("List item as string is %s.\n",  ((char *) pNode->pData));
			pNode = pNode->pNext;
	}

	// Check out routine
	if (pListSortedNumbers->count == 10) {
		printf("PASS: sorted list element count accurate.\n");
	} else {
		printf("FAIL: sorted list element count mismatch.\n");
	}
		


	exit(iRC);

}



