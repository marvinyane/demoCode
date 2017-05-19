#include <stdio.h>

int main()
{
    void* p = malloc(20);
    free(p);

    return 0;
}
