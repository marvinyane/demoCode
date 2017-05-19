#include <stdio.h>

#define MAX_COUNT (100)

typedef struct
{
    int key;
}SeqList;

typedef int KeyType;

int comp(void* a, void* b)
{
    return ((SeqList*)a)->key - ((SeqList*)b)->key;
}

int BinSearch(SeqList * R, int n,  KeyType k )
{
    int low=0, high=n-1, mid;

#if 0
    int i = 0;
    for(; i < n; i++)
    {
        printf("%d \n", R[i].key);
    }

    printf("search for %d \n", k);
#endif

    if( R[low].key == k )
    {
        return low;
    }

    if( R[high].key == k )
    {
        return high;
    }

    while( low <= high )
    { 
        mid = low + ((high-low)/2);

        if( R[mid].key == k )
        {
            return mid;
        }

        if( R[mid].key > k )
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    if( low > high )
    {
        return -1;
    }
}

int main()
{
    int count = 0;
    int value = 0;

    SeqList* list = malloc(sizeof(SeqList) * MAX_COUNT);

    while(count < MAX_COUNT && scanf("%d", &value) != EOF)
    {
        list[count++].key = value;
    }

    qsort(list, count, sizeof(SeqList), comp);

    while(1)
    {
        int s = 0;
        printf("search for: ");
        scanf("%d", &s);
        int ret = BinSearch(list, count, s);
        printf("result : %d \n", ret);
    }

    return 0;
}
