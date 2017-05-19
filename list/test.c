#include <stdio.h>
#include "struct.h"
#include "define.h"


int main()
{
	bt_status_init();
    
    CREATE_BT_STATUS_STRAT(BT_AVP_STATUS, 1);
        SET_AVP_CONNID_ITEM(12);
    CREATE_BT_STATUS_END();

    int connId = 0;
    GET_BT_AVP_CONNID_STATUS(1, &connId);
	printf("First : %d \n", connId );

    SET_BT_AVP_CONNID_STATUS(1, 34);

    SEARCH_BT_STATUS_START(BT_AVP_STATUS, 1);
        SET_AVP_CONNID_ITEM(56);
    SEARCH_BT_STATUS_END();

    GET_BT_AVP_CONNID_STATUS(1, &connId);
	printf("Second : %d \n", connId );


    REMOVE_BT_STATUS_ENTRY(BT_AVP_STATUS, 1);

    /* remove a node */
    /* modify and notify */
    /* other : get call list by myself*/
    /* why wait for complete*/

	bt_status_deinit();

	return 0;
}
