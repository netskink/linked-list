// This list implementation does not do memory copies. It simply does pointer assignments to existing
// storage.




/*
 record Node {
    data; // The data being stored in the node.  Currently it can be either a string or integer.
    Node next // A reference to the next node, null for last node
 }
 record List {
     Node firstNode // points to first node of list; null for empty list
 }
*/

struct node {
	struct node *pNext;
	void *pData;
};
typedef struct node node_t;

struct list {
	struct node *pFirst;
	int (*pfCompare)(node_t *,node_t *);  // the function used to compare two nodes.
	int count;
};
typedef struct list list_t;

int append(list_t *pList, void *pData);

//list_t *init_list(void);
list_t *init_list(int (*pFunc)(node_t *,node_t *) ) ;

bool is_list_empty(list_t *pList);
bool is_list_singleton(list_t *pList);

list_t * merge_sort(list_t *pList);
list_t * merge(list_t *pListLeft, list_t *pListRight);

int compare_ints(node_t *pNode1, node_t *pNode2);
int compare_strings(node_t *pNode1, node_t *pNode2);
