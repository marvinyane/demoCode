#include <stdio.h>
#include "struct.h"


int main()
{
	struct list_head head;
	INIT_LIST_HEAD(&head);
	
	bt_status_entry* e1 = malloc(sizeof(bt_status_entry));
	memset(e1, 0, sizeof(bt_status_entry));
	e1->id = 1;
	INIT_LIST_HEAD(&e1->list);

	bt_status_entry* e2 = malloc(sizeof(bt_status_entry));
	memset(e2, 0, sizeof(bt_status_entry));
	e2->id = 2;
	INIT_LIST_HEAD(&e2->list);

	list_add(&e2->list, &e1->list);

	bt_status_entry* e3 = malloc(sizeof(bt_status_entry));
	memset(e3, 0, sizeof(bt_status_entry));
	e3->id = 2;
	INIT_LIST_HEAD(&e3->list);

	list_add(&e3->list, &e1->list);

	struct list_head* tmpptr = NULL;
	bt_status_entry* entry = NULL;

	list_for_each( tmpptr, &( e1->list ) ){
		entry = list_entry(tmpptr, bt_status_entry , list);
		printf("fuck!!!! \n");
	}

	return 0;


}