#include <stdio.h>

#include <tpl.h>

typedef struct
{
    int status;
    int opcode;
    int c;
    int d;
}TEST_T;

int main()
{

    void* store_mem = NULL;
    int   store_len = 0;

    tpl_node* tn;

    TEST_T test;
    memset(&test, 0, sizeof(TEST_T));
    test.status = 1;
    test.opcode = 2;
    test.c = 0x45;
    test.d = 0x32;

    tn = tpl_map("S(iiii)", &test);
    tpl_pack(tn, 0);
    tpl_dump(tn, TPL_MEM, &store_mem, &store_len);
    tpl_free(tn);

    int i = 0;
    for (; i < store_len; i++)
    {
        printf("%d - 0x%.2x\n", i, ((char*)store_mem)[i]);
    }

    printf("pack success total length is %d, and now start unpack\n", store_len);

    TEST_T test1;
    memset(&test1, 0, sizeof(TEST_T));

    tn = tpl_map("S(iiii)", &test1);
    tpl_load(tn, TPL_MEM, store_mem, store_len);
    tpl_unpack(tn, 0);
    tpl_free(tn);

    free(store_mem);

    printf("unpack status %d, opcode %d, c is 0x%.2x, d is 0x%.2x\n", test1.status, test1.opcode,  test1.c, test1.d);


    return 0;
}
