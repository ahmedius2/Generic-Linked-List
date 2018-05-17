/*
 * main.c
 *
 *  Created on: May 12, 2018
 *      Author: asoyyigit
 */

#include <stdio.h>
#include "forwardList.h"

typedef struct mydata{
	int a;
	double b;
	char c;
}mydata_t;

void printInt(void *myInt){
	printf("%d %f -> ",
			((mydata_t*)myInt)->a ,
			((mydata_t*)myInt)->b );
}

int isGreaterInt(void *d1, void *d2){
	return (*((mydata_t*)d1)).a > (*((mydata_t*)d2)).a;
}

int main (int argc, char **argv) {
	fList_t myfl;
	fListNode_t *node;
	int i;
	mydata_t mydat;
	initialize_flist(&myfl, sizeof(mydata_t));

	for(i = 0; i < 50 ; ++i){
		mydat.a=i;
		mydat.b=i + 0.654;
		mydat.c=i+40;
		insert_beg(&myfl, &mydat);
	}

	mydat.a=-123456;
	mydat.b=-342121 + 0.654;
	mydat.c='x';
	node = insert_end(&myfl,&mydat);

	display_flist(&myfl,printInt);

	for(i = 50; i < 150 ; ++i){
		mydat.a=i;
		mydat.b=i + 0.654;
		mydat.c=i+40;
		insert_end(&myfl, &mydat);
	}

	display_flist(&myfl,printInt);

	for(i = 150; i < 200 ; ++i){
		mydat.a=i;
		mydat.b=i + 0.654;
		mydat.c=i+40;
		insert_before(&myfl, node, &mydat);
	}

	display_flist(&myfl,printInt);

	for(i = 250; i < 300 ; ++i){
		mydat.a=i;
		mydat.b=i + 0.654;
		mydat.c=i+40;
		insert_after(&myfl, node, &mydat);
	}

	display_flist(&myfl,printInt);

	sort_flist_bbl(&myfl, isGreaterInt);

	display_flist(&myfl,printInt);
	printf("DELETION STARTS\n");

	for(i=0; i< 25; ++i){
		delete_before(&myfl,node);
	}

	display_flist(&myfl,printInt);

	for(i=0; i< 25; ++i){
		delete_beg(&myfl);
		delete_end(&myfl);
	}

	display_flist(&myfl,printInt);

	delete_node(&myfl,node->next);
	delete_node(&myfl,node);

	display_flist(&myfl,printInt);

	delete_flist(&myfl);

	display_flist(&myfl,printInt);
	printf("Finish");

	return 0;
}
