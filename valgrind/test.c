#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000


void cache()
{
    int array[SIZE][SIZE] = {0};
    int i,j;

#if 0
    for(i = 0; i < SIZE; i++)
    {
        for(j = 0; j < SIZE; j++)
        {
            array[i][j] = i+j;
        }
    }
#else
    for(i = 0; i < SIZE; i++)
    {
        for(j = 0; j < SIZE; j++)
        {
            array[j][i] = i+j;
        }
    }
#endif


}

void memoryleak()
{
    char* p = NULL;
    int i = 0;
    
    for(; i < 100; i++)
    {
        p = malloc(100);
        if(i%2==0)
        {
            free(p);
        }
    }
}

int main()
{
    //cache();

    memoryleak();

    return 0;
}
