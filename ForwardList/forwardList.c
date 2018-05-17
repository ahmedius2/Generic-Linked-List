#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>

#include "forwardList.h"

static fListNode_t *create_node(fList_t *fl, void *dataPtr){
	fListNode_t *newNode;
	newNode = (fListNode_t*)malloc(sizeof(fListNode_t) + fl->dataSize);
	memcpy(newNode->dataPtr, dataPtr, fl->dataSize);
	return newNode;
}

void initialize_flist(fList_t *fl, size_t dataSize){
	fl->dataSize = dataSize;
	fl->head = NULL;
	fl->listSize = 0;
}

void display_flist(fList_t *fl, void (*displayFunc)(void *)){
	fListNode_t *node;

	printf("List size: %lu\n", fl->listSize );
	node = fl->head;
	while(node != NULL){
		displayFunc(node->dataPtr);
		node = node->next;
	}
	printf("\n");
}

fListNode_t *insert_beg(fList_t *fl, void *newNodeData){
	fListNode_t *newNode = create_node(fl, newNodeData);
	newNode->next = fl->head;
	fl->head = newNode;
	++(fl->listSize);
	return newNode;
}

fListNode_t *insert_end(fList_t *fl, void *newNodeData){
	return insert_before(fl,NULL,newNodeData);
}

// it is against the philosophy that the nodeBef can be NULL
fListNode_t *insert_before(fList_t *fl,fListNode_t *after, void *newNodeData){
	fListNode_t **nodePtr;

	nodePtr = &(fl->head);

	while((*nodePtr) != after)
		nodePtr = &((*nodePtr)->next);

	*nodePtr = create_node(fl, newNodeData);
	(*nodePtr)->next = after;
	++(fl->listSize);
	return *nodePtr;
}

fListNode_t *insert_after(fList_t *fl,fListNode_t *before, void *newNodeData){
	fListNode_t *newNode;

	newNode = create_node(fl, newNodeData);
	newNode->next = before->next;
	before->next = newNode;
	++(fl->listSize);
	return newNode;

}

void delete_node(fList_t *fl,fListNode_t *nodeToDel){
	fListNode_t **nodePtr;

	assert(fl->head != NULL);

	nodePtr = &(fl->head);

	while((*nodePtr) != nodeToDel)
		nodePtr = &((*nodePtr)->next);

	*nodePtr = (*nodePtr)->next;
	free(nodeToDel);
	--(fl->listSize);
}

void delete_beg(fList_t *fl){
	fListNode_t *node;

	assert(fl->head != NULL);

	node = fl->head->next;
	free(fl->head);
	fl->head = node;

}

void delete_end(fList_t *fl){
	delete_before(fl, NULL);
}

void delete_before(fList_t *fl,fListNode_t *nodeAftrToDel) {
	fListNode_t **nodePtr;

	assert(fl->head != NULL);

	nodePtr = &(fl->head);

	while((*nodePtr)->next != nodeAftrToDel)
		nodePtr = &((*nodePtr)->next);

	free(*nodePtr);
	(*nodePtr) = nodeAftrToDel;
	--(fl->listSize);
}


void delete_flist(fList_t *fl){
	while(fl->head != NULL)
		delete_beg(fl);
}

// comparator, returns true if d1 > d2
// Bubble sort
// if data is big, overhead will be big ...
void sort_flist_bbl(fList_t *fl,  int (*greaterThanFunc)(void *d1, void *d2)){
	unsigned long i;
	void *tempDataPtr = malloc(fl->dataSize);
	fListNode_t *node;

	for(i=1; i<fl->listSize; ++i){
		node = fl->head;
		while(node->next != NULL){
			if(greaterThanFunc(node->dataPtr, node->next->dataPtr)){
				// swap data
				memcpy(tempDataPtr, node->dataPtr, fl->dataSize);
				memcpy(node->dataPtr, node->next->dataPtr, fl->dataSize);
				memcpy(node->next->dataPtr, tempDataPtr, fl->dataSize);
			}
			node = node->next;
		}
	}

	free(tempDataPtr);
}

// comparator, returns true if d1 > d2
// Insertion sort, find the biggest, insert it at the new list beginning
// do this for all nodes.
void sort_flist_ins(fList_t *fl,  int (*greaterThanFunc)(void *d1, void *d2)){
	fListNode_t *newHead=NULL, *node, **nodeMax;
	unsigned long i;

	for(i=0; i<fl->listSize; ++i){
		// find the greatest
		nodeMax = &(fl->head);
		node = fl->head;
		while(node->next != NULL){
			if(greaterThanFunc(node->next->dataPtr, (*nodeMax)->dataPtr))
				nodeMax = &(node->next);
			node = node->next;
		}

		// insert greatest to beginning new list
		node = *nodeMax;
		*nodeMax = (*nodeMax)->next;
		node->next = newHead;
		newHead = node;
	}

	fl->head = newHead;
}
