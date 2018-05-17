/*
 ============================================================================
 Name        : DoublyLinkedList.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include "doublyLinkedList.h"

typedef struct mydata{
	int a;
	double b;
	char c;
}mydata_t;

void printInt(void *myInt){
	printf("%d ",
			((mydata_t*)myInt)->a);// ,
			//((mydata_t*)myInt)->b );
}

int isGreaterInt(void *d1, void *d2){
	return (*((mydata_t*)d1)).a > (*((mydata_t*)d2)).a;
}

int main (int argc, char **argv) {
	dllist_t myfl;
	dllistNode_t *node;
	int i;
	mydata_t mydat;
	initialize_dllist(&myfl, sizeof(mydata_t));

	for(i = 0; i < 500 ; ++i){
		mydat.a=i;
		mydat.b=i + 0.654;
		mydat.c=i+40;
		insert_beg(&myfl, &mydat);
	}

	mydat.a=-123456;
	mydat.b=-342121 + 0.654;
	mydat.c='x';
	node = insert_end(&myfl,&mydat);

	display_dllist(&myfl,printInt);

	for(i = 500; i < 1500 ; ++i){
		mydat.a=i;
		mydat.b=i + 0.654;
		mydat.c=i+40;
		insert_end(&myfl, &mydat);
	}

	display_dllist(&myfl,printInt);

	for(i = 1500; i < 2000 ; ++i){
		mydat.a=i;
		mydat.b=i + 0.654;
		mydat.c=i+40;
		insert_before(&myfl, node, &mydat);
	}

	display_dllist(&myfl,printInt);

	for(i = 2500; i < 3000 ; ++i){
		mydat.a=i;
		mydat.b=i + 0.654;
		mydat.c=i+40;
		insert_after(&myfl, node, &mydat);
	}

	display_dllist(&myfl,printInt);

	sort_dllist_ins(&myfl, isGreaterInt);

	display_dllist(&myfl,printInt);

	printf("DELETION STARTS\n");

	display_dllist(&myfl,printInt);

	for(i=0; i< 250; ++i){
		delete_beg(&myfl);
		delete_end(&myfl);
	}

	display_dllist(&myfl,printInt);

	delete_node(&myfl,myfl.head->next->next->next);
	delete_node(&myfl,myfl.head->next->next->next->prev);
	delete_node(&myfl,myfl.head->next->prev->next);
	delete_node(&myfl,myfl.head->next->next->next->prev->prev);

	display_dllist(&myfl,printInt);

	delete_flist(&myfl);

	display_dllist(&myfl,printInt);
	printf("Finish");

	return 0;
}
