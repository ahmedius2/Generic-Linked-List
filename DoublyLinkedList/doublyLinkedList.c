#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>

#include "doublyLinkedList.h"


static dllistNode_t *create_node(dllist_t *fl, void *dataPtr){
	dllistNode_t *newNode;

	newNode = (dllistNode_t*)malloc(sizeof(dllistNode_t) + fl->dataSize);
	memcpy(newNode->dataPtr, dataPtr, fl->dataSize);

	return newNode;
}

void initialize_dllist(dllist_t *fl, size_t dataSize){
	fl->dataSize = dataSize;
	fl->head = NULL;
	fl->tail = NULL;
	fl->listSize = 0;
}

void display_dllist(dllist_t *fl, void (*displayFunc)(void *)){
	dllistNode_t *node;

	printf("List size: %lu\n", fl->listSize );
	node = fl->head;
	while(node != NULL){
		displayFunc(node->dataPtr);
		node = node->next;
	}
	printf("\n");
}

dllistNode_t *insert_beg(dllist_t *fl, void *newNodeData){
	dllistNode_t *newNode = create_node(fl, newNodeData);
	if(fl->head == NULL){
		fl->head = fl->tail = newNode;
		newNode->next = NULL;
		newNode->prev = NULL;
	}
	else{
		newNode->prev = NULL;
		newNode->next = fl->head;
		newNode->next->prev = newNode;
		fl->head = newNode;
	}
	++(fl->listSize);
	return newNode;
}

dllistNode_t *insert_end(dllist_t *fl, void *newNodeData){
	dllistNode_t *newNode = create_node(fl, newNodeData);
	if(fl->tail == NULL){
		fl->head = fl->tail = newNode;
		newNode->next = NULL;
		newNode->prev = NULL;
	}
	else{
		newNode->next = NULL;
		newNode->prev = fl->tail;
		newNode->prev->next = newNode;
		fl->tail = newNode;
	}
	++(fl->listSize);
	return newNode;
}

dllistNode_t *insert_before(dllist_t *fl,dllistNode_t *after, void *newNodeData){
	dllistNode_t *before = create_node(fl, newNodeData);

	before->next = after;
	before->prev = after->prev;
	if(before->prev != NULL)
		before->prev->next = before;
	else
		fl->head = before;
	before->next->prev = before;
	++(fl->listSize);
	return before;
}


dllistNode_t *insert_after(dllist_t *fl,dllistNode_t *before, void *newNodeData){
	dllistNode_t *after = create_node(fl, newNodeData);

	after->next = before->next;
	after->prev = before;
	if(after->next != NULL)
		after->next->prev = after;
	else
		fl->tail = after;
	before->next = after;
	++(fl->listSize);
	return after;
}

// i am here
void delete_node(dllist_t *fl,dllistNode_t *nodeToDel){
	assert(fl->head != NULL);

	if(nodeToDel->prev == NULL){
		//delete_beg
		fl->head = nodeToDel->next;
		if(fl->head != NULL)
			fl->head->prev = NULL;
	}
	else if(nodeToDel->next == NULL){
		//delete_end
		fl->tail = nodeToDel->prev;
		if(fl->tail != NULL)
			fl->tail->next = NULL;
	}
	else{
		//delete middle
		nodeToDel->prev->next = nodeToDel->next;
		nodeToDel->next->prev = nodeToDel->prev;
	}

	free(nodeToDel);

	if(--(fl->listSize) == 0){
		fl->head = fl->tail = NULL;
	}
}

void delete_beg(dllist_t *fl){
	delete_node(fl, fl->head);
}

void delete_end(dllist_t *fl){
	delete_node(fl, fl->tail);
}

void delete_flist(dllist_t *fl){
	while(fl->head != NULL)
		delete_node(fl, fl->head);
}

// comparator, returns true if d1 > d2
// Bubble sort
// if data is big, overhead will be big ...
void sort_dllist_bbl(dllist_t *fl,  int (*greaterThanFunc)(void *d1, void *d2)){
	unsigned long i;
	void *tempDataPtr = malloc(fl->dataSize);
	dllistNode_t *node;

	assert(fl->head != NULL);

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

dllistNode_t *max_node(dllist_t *fl, int (*greaterThanFunc)(void *d1, void *d2)){
	dllistNode_t *nodeMax, *node;

	nodeMax = fl->head;
	node = fl->head->next;
	while(node != NULL){
		if(greaterThanFunc(node->dataPtr, nodeMax->dataPtr))
			nodeMax = node;
		node = node->next;
	}

	return nodeMax;
}

// BURADAYIM

// comparator, returns true if d1 > d2
// Insertion sort, find the biggest, insert it at the new list beginning
// do this for all nodes.
void sort_dllist_ins(dllist_t *fl,  int (*greaterThanFunc)(void *d1, void *d2)){
	dllistNode_t *newHead=NULL, **nodeMaxPtr, *node;
	unsigned long i;

	for(i=0; i<fl->listSize; ++i){
		// find the greatest
		nodeMaxPtr = &(fl->head);
		node = fl->head;
		while(node->next != NULL){
			if(greaterThanFunc(node->next->dataPtr, (*nodeMaxPtr)->dataPtr))
				nodeMaxPtr = &(node->next);
			node = node->next;
		}
		// remove greatest from old list
		node = *nodeMaxPtr;
		*nodeMaxPtr = (*nodeMaxPtr)->next;
		// insert greatest to beginning new list
		// i need to get rid of this if for performance
		if(newHead != NULL)
			newHead->prev = node;
		else
			fl->tail = node;
		node->next = newHead;
		newHead = node;
	}
	fl->head = newHead;
	fl->head->prev = NULL;
}


