#include <stdio.h>
#include <stdbool.h>
#include "struct.h"

bt_status_t btStatus[BT_STATUS_MAX];


void bt_status_init()
{
	int i = 0;
	memset(btStatus, 0, sizeof(btStatus));

	for(; i < BT_STATUS_MAX; i++){
		INIT_LIST_HEAD( &btStatus[i].list );
		pthread_mutex_init(&btStatus[i].mutex, NULL);
	}
}

void bt_status_deinit()
{
	/* the memory saved in the status entry should be freed before this !
		this function will destroy all the links
	*/

	int i = 0;

	for(; i < BT_STATUS_MAX; i++){
		struct list_head* tmpptr = NULL;
		bt_status_base* entry = NULL;

		list_for_each( tmpptr, &( btStatus[i].list ) ){
			entry = list_entry(tmpptr, bt_status_base , list);
			free(entry);
		}

		pthread_mutex_destroy(&btStatus[i].mutex);
	}
}

void* get_bt_status_entry(int sign, int id)
{
	struct list_head* ptr = NULL;
	bt_status_base* entry = NULL;

	list_for_each( ptr, &( btStatus[sign].list ) ){
		entry = list_entry(ptr, bt_status_base , list);
		if(entry->id == id){
			return entry;
		}
	}

	return NULL;
}

void* create_bt_status_entry(int sign, int id, int size)
{
	bt_status_base* entry = malloc(size);
	memset(entry, 0, size);

	entry->id = id;
	INIT_LIST_HEAD(&entry->list);

	list_add_tail(&(entry->list), &(btStatus[sign].list));

	return entry;
}

bool remove_bt_status_entry(int sign, int id)
{
	bt_status_base* entry = get_bt_status_entry(sign, id);
	if(entry == NULL){
		return false;
	}
	list_del(&entry->list);

	free(entry);

	return true;
}