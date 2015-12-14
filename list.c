#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"
#include "list.h"


/*
Traversal of a singly linked list is simple, 
beginning at the first node and following each next link until we come to the end:

 node := list.firstNode
 while node not null
     (do something with node.data)
     node := node.next
*/
int append(list_t *pList, void *pData) {

	node_t *pTip;
	node_t *pNewNode;



	// Creat the new node
	pNewNode = malloc(sizeof(node_t));
	if (NULL == pNewNode) {
		return(-1);
	}

	// Add the data;
	pNewNode->pData = pData;
	pNewNode->pNext = NULL;


	if (NULL == pList->pFirst) {
		pList->pFirst = pNewNode;
	} else {
		pTip = pList->pFirst;
		// Find the last node
		while(NULL != pTip->pNext ) {
			pTip = pTip->pNext;
		}
		pTip->pNext = pNewNode;
	}
	pList->count++;

	return(0);
}


list_t *init_list(int (*pFunc)(node_t *,node_t *) ) {

	list_t *pList;
	pList = malloc(sizeof(list_t));
	if (NULL == pList) {
		return(NULL);
	}

	pList->pFirst = NULL;
	pList->pfCompare = pFunc;
	pList->count = 0;

	return (pList);
}

int compare_strings(node_t *pNode1, node_t *pNode2) {
	char *pchBuf1 = (char *) pNode1->pData;
	char *pchBuf2 = (char *) pNode2->pData;

	return strcmp(pchBuf1,pchBuf2);
}
int compare_ints(node_t *pNode1, node_t *pNode2) {

	int val1 = * (int *) pNode1->pData;
	int val2 = * (int *) pNode2->pData;

	if (val1 < val2) {
		return -1;
	} else if (val1 == val2) {
		return 0;
	} else {
		return 1;
	}
}

bool is_list_empty(list_t *pList) {

	if (NULL == pList->pFirst) {
		return true;
	}
	return false;
}

bool is_list_singleton(list_t *pList) {

	if (NULL == pList->pFirst->pNext) {
		return true;
	}
	return false;
}


/* Rather than use stdlib qsort() (quicksort), implement merge sort based upon 
   wikipedia pseudo code entry.
   https://en.wikipedia.org/wiki/Merge_sort
  
   General idea
   Recursively divide the list into smaller sublists 
   until the sublists are trivially sorted and then
   merge the sublists.
*/
list_t *merge_sort(list_t *pList) {

	list_t *pListLeft;
	list_t *pListRight;
	int i=0;
	node_t *pNode;

	// Base case.  A zero or one element list is sorted by definition
	if (is_list_empty(pList)) {
		return pList;
	}
	if (is_list_singleton(pList)) {
		return pList;
	}

	// The wikipedia entry assumes the number of items in the list
	// is maintained and uses a for loop.  It still requires
	// the list to be iterated.  I'm simply using a while not 
	// empty as I build the sublists. 

	//
	// Create the two sublists
	//
//	int (*pfCompare)(node_t,node_t);
	pListLeft = init_list(pList->pfCompare);
	if (NULL == pListLeft) {
		printf("Failed to init left sublist.\n");
	}
	pListRight = init_list(pList->pfCompare);
	if (NULL == pListRight) {
		printf("Failed to init right sublist.\n");
	}


	// alternatively add each item of the list to the sublists.
	pNode = pList->pFirst;
	while ( NULL != pNode) {
		if (i % 2) {
			if ( append(pListLeft, pNode->pData) ) {
				printf("Failed to append number to left list.\n");
			}	
		} else {
			if ( append(pListRight, pNode->pData) ) {
				printf("Failed to append number to right list.\n");
			}	
		}
		pNode = pNode->pNext;
		i++;
	}

	// Recursively sort both sublists
	pListLeft = merge_sort(pListLeft);
	pListRight = merge_sort(pListRight);

	return ( merge(pListLeft,pListRight) );
	
}

list_t * merge(list_t *pListLeft, list_t *pListRight) {

	list_t *pListMerged;
	node_t *pHeadLeft;
	node_t *pHeadRight;


	//
	// Create the merged list
	//
	pListMerged = init_list(pListLeft->pfCompare);
	if (NULL == pListMerged) {
		printf("Failed to init Merged list.\n");
	}


	// iterate the two lists appending the values to the
	// merged list
	pHeadLeft = pListLeft->pFirst;
	pHeadRight = pListRight->pFirst;
	while ( NULL != pHeadLeft && NULL != pHeadRight ) {
		//if ( *(int *) pHeadLeft->pData <=  *(int *) pHeadRight->pData) {
		if ( pListLeft->pfCompare(pHeadLeft, pHeadRight) < 0) {
			if ( append(pListMerged, pHeadLeft->pData) ) {
				printf("Failed to append left side element to merged.\n");
			}	
			pHeadLeft = pHeadLeft->pNext;
		} else {
			if ( append(pListMerged, pHeadRight->pData) ) {
				printf("Failed to append right side element to merged.\n");
			}	
			pHeadRight = pHeadRight->pNext;
		}
	}

	// Either left or right may have elements left, consume them
	// (only one of the following loops will actually be entered)
	while ( NULL != pHeadLeft ) {
		if ( append(pListMerged, pHeadLeft->pData) ) {
			printf("Failed to append left side element to merged.\n");
		}	
		pHeadLeft = pHeadLeft->pNext;
	}
	while ( NULL != pHeadRight ) {
		if ( append(pListMerged, pHeadRight->pData) ) {
			printf("Failed to append right side element to merged.\n");
		}	
		pHeadRight = pHeadRight->pNext;
	}

	return ( pListMerged );
}

