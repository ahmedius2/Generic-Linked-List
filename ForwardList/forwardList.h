
#ifndef FORWARDLIST_H_
#define FORWARDLIST_H_

// because of eclipse :(
typedef unsigned long size_t;

typedef struct fListNode{
	struct fListNode *next;
	unsigned char dataPtr[0]; // flexible array, structure hack
} fListNode_t;

typedef struct fList{
	fListNode_t *head;
	size_t dataSize;
	unsigned long listSize;
} fList_t;

void initialize_flist(fList_t *fl, size_t dataSize);
void display_flist(fList_t *fl, void (*displayFunc)(void *));

fListNode_t *insert_beg(fList_t *fl, void *newNodeData);
fListNode_t *insert_end(fList_t *fl, void *newNodeData);
fListNode_t *insert_before(fList_t *fl,fListNode_t *after, void *newNodeData);
fListNode_t *insert_after(fList_t *fl,fListNode_t *before, void *newNodeData);

void delete_node(fList_t *fl,fListNode_t *nodeToDel);
void delete_beg(fList_t *fl);
void delete_end(fList_t *fl);
void delete_before(fList_t *fl,fListNode_t *nodeAftrToDel);
void delete_flist(fList_t *fl);

void sort_flist_bbl(fList_t *fl,  int (*greaterThanFunc)(void *d1, void *d2));
void sort_flist_ins(fList_t *fl,  int (*greaterThanFunc)(void *d1, void *d2));


#endif
