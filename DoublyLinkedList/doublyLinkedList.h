/*
 * doublyLinkedList.h
 *
 *  Created on: May 13, 2018
 *      Author: asoyyigit
 */

#ifndef DOUBLYLINKEDLIST_H_
#define DOUBLYLINKEDLIST_H_

typedef struct dllistNode{
	struct dllistNode *next, *prev;
	unsigned char dataPtr[0]; // flexible array, structure hack
} dllistNode_t;

typedef struct dllist{
	dllistNode_t *head, *tail;
	size_t dataSize;
	unsigned long listSize;
} dllist_t;

void initialize_dllist(dllist_t *fl, size_t dataSize);
void display_dllist(dllist_t *fl, void (*displayFunc)(void *));

dllistNode_t *insert_beg(dllist_t *fl, void *newNodeData);
dllistNode_t *insert_end(dllist_t *fl, void *newNodeData);
dllistNode_t *insert_before(dllist_t *fl,
		dllistNode_t *after, void *newNodeData);
dllistNode_t *insert_after(dllist_t *fl,
		dllistNode_t *before, void *newNodeData);

void delete_node(dllist_t *fl,dllistNode_t *nodeToDel);
void delete_beg(dllist_t *fl);
void delete_end(dllist_t *fl);
void delete_flist(dllist_t *fl);

void sort_dllist_bbl(dllist_t *fl,  int (*greaterThanFunc)(void *d1, void *d2));
dllistNode_t *max_node(dllist_t *fl, int (*greaterThanFunc)(void *d1, void *d2));
void sort_dllist_ins(dllist_t *fl,  int (*greaterThanFunc)(void *d1, void *d2));

#endif /* DOUBLYLINKEDLIST_H_ */
