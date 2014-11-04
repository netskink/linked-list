// This list implementation does not do memory copies. It simply does pointer assignments to existing
// storage.




/*
 record Node {
    data; // The data being stored in the node
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
};
typedef struct list list_t;

int append(list_t *pList, void *pData);

list_t *init_list(void);

// could use a comparision function as second parameter rather than dedicated function name: ie. _as_number.
list_t *sort_list_as_numbers(list_t *pList);
