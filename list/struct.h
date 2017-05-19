#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include "pthread.h" /* for lock */

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

#define BT_STATUS_STRUCT_HEAD uint32 id; struct list_head list

typedef struct
{
	BT_STATUS_STRUCT_HEAD;
}bt_status_base;

enum{
	BT_PAIRED_STATUS = 0,
	BT_CONNECT_STATUS = 1,
    BT_AVP_STATUS = 2,

	BT_STATUS_MAX
};

typedef struct{
	uint8 count;
	struct list_head list;
	pthread_mutex_t mutex;
}bt_status_t;

extern bt_status_t btStatus[BT_STATUS_MAX];

#define MIN(a,b) ((a)>(b)?(b):(a))

/* set item - used in create or search or foreach entrys */
#define SET_ITEM(name, value) entry->name = value
#define COPY_ITEM(name, value, len) memcpy(&(entry->name), value, MIN(len, sizeof(entry->name)))

/*release item - used in search or foreach or release entrys */
#define RELEASE_ITEM(name) \
	if(entry->name) free(entry->name)


/*get item - used in search or foreach or release entrys */
#define GET_ITEM_VALUE(name, valuePtr) *(valuePtr) = entry->name
#define GET_ITEM_COPY(name, buffer, len) memcpy(value, &(entry->name), len)


/*search item*/
#define SEARCH_BT_STATUS_START(module, p_id) \
do{\
	int _sign = module;\
	int _pid = p_id;\
	module##_T* entry = NULL;\
	pthread_mutex_lock(&btStatus[_sign].mutex);\
	entry = get_bt_status_entry(_sign, _pid);\
	if(entry == NULL)\
		break;

#define SEARCH_BT_STATUS_END() \
	pthread_mutex_unlock(&btStatus[_sign].mutex);\
}while(0)


/* release item */
#define RELEASE_BT_STATUS_START(module, p_id) \
SEARCH_BT_STATUS_START(module, p_id);\

#define RELEASE_BT_STATUS_END() \
remove_bt_status_entry(_sign, _pid);\
SEARCH_BT_STATUS_END()

#define REMOVE_BT_STATUS_ENTRY(module, p_id) \
do{\
	pthread_mutex_lock(&btStatus[module].mutex);\
	remove_bt_status_entry(module, p_id);\
	pthread_mutex_unlock(&btStatus[module].mutex);\
}while(0)



/* foreach item */
#define FOREACH_BT_STATUS_START(module) \
do{ \
	int _sign = module;\
	pthread_mutex_lock(&btStatus[module].mutex);\
	struct list_head* _listHeadPtr = NULL;\
	list_for_each( _listHeadPtr, &( btStatus[module].list ) ){\
		module##_T* entry = list_entry(_listHeadPtr, module##_T , list);\

#define FOREACH_BT_STATUS_END() \
	} \
	pthread_mutex_unlock(&btStatus[_sign].mutex);\
}while(0)

/* create item */
#define CREATE_BT_STATUS_STRAT(module, p_id) \
do {\
	int _sign = module;\
	pthread_mutex_lock(&btStatus[module].mutex);\
	module##_T* entry = create_bt_status_entry(module, p_id, sizeof(module##_T))

#define CREATE_BT_STATUS_END() \
	pthread_mutex_unlock(&btStatus[_sign].mutex);\
}while(0)

/* set item once */
#define SET_BT_STATUS(module, id, name, value) \
SEARCH_BT_STATUS_START(module, id); \
SET_ITEM(name, value);\
SEARCH_BT_STATUS_END()

#define COPY_BT_STATUS(module, id, name, value, len) \
SEARCH_BT_STATUS_START(module, id); \
COPY_ITEM(name, value, len);\
SEARCH_BT_STATUS_END()

/* get item once */
#define GET_BT_VALUE_STATUS(module, id, name, valuePtr) \
SEARCH_BT_STATUS_START(module, id); \
GET_ITEM_VALUE(name, valuePtr);\
SEARCH_BT_STATUS_END()

#define GET_BT_COPY_STATUS(module, id, name, buffer, len) \
SEARCH_BT_STATUS_START(module, id); \
GET_ITEM_COPY(name, buffer, len);\
SEARCH_BT_STATUS_END()

/* defines */
void bt_status_init(void);
void bt_status_deinit(void);
void* get_bt_status_entry(int sign, int id);
void* create_bt_status_entry(int sign, int id, int size);
bool remove_bt_status_entry(int sign, int id);
