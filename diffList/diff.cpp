#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define DEBUG (1)
typedef struct 
{
    unsigned int ssid;
    char        mac[7];

}list;

typedef struct
{
    unsigned int count;
    list* l;
}data;

data d_new, d_old;

int comp(const void* a, const void* b)
{
    return strncmp((( list*)a)->mac, ((list*)b)->mac, 6);
}

int main()
{
    int i = 0;
    int count = 0;
    scanf("%d", &count);
    d_new.count = count;
    d_new.l = (list*)malloc(d_new.count * sizeof(list));

    for(i=0; i < count; i++)
    {
        scanf("%d %s",&d_new.l[i].ssid, d_new.l[i].mac);
#if DEBUG
        printf("%d %s\n", d_new.l[i].ssid, d_new.l[i].mac);
#endif
    }

    qsort(d_new.l, d_new.count, sizeof(list), comp);
#if DEBUG
    printf("after sort \n");

    for(i=0; i < count; i++)
    {
        printf("%d %s\n", d_new.l[i].ssid, d_new.l[i].mac);
    }
#endif

#if DEBUG
    printf("\n\n");
#endif
    scanf("%d", &count);

    d_old.count = count;
    d_old.l = (list*)malloc(d_old.count * sizeof(list));

    for(i=0; i < count; i++)
    {
        scanf("%d %s",&d_old.l[i].ssid, d_old.l[i].mac);
#if DEBUG
        printf("%d %s\n", d_old.l[i].ssid, d_old.l[i].mac);
#endif
    }

    qsort(d_old.l, d_old.count, sizeof(list), comp);

#if DEBUG
    printf("after sort \n");

    for(i=0; i < count; i++)
    {
        printf("%d %s\n", d_old.l[i].ssid, d_old.l[i].mac);
    }
#endif

    int new_sign = 0;
    int old_sign = 0;

    while(1)
    {
        if(new_sign >= d_new.count)
        {
            /**/
            for(; old_sign < d_old.count; old_sign++)
            {
                printf("%s is delete\n", d_old.l[old_sign].mac);
            }
            break;
        }

        if(old_sign >= d_old.count)
        {
            /**/
            for(; new_sign < d_new.count; new_sign++)
            {
                printf("%s is new\n", d_new.l[new_sign].mac);
            }
            break;
        }

        int ret = comp(&d_new.l[new_sign], &d_old.l[old_sign]);

        if(ret == 0)
        {
            /**/
            new_sign++;
            old_sign++;
            continue;
        }

        if(ret > 0)
        {
            /*new > old */
            printf("%s is delete\n", d_old.l[old_sign].mac);
            old_sign++;
            continue;
        }

        if(ret < 0)
        {
            /*old > new*/
            printf("%s is new \n", d_new.l[new_sign].mac);
            new_sign++;
            continue;
        }
    }

    printf("Done ! \n");
    return 0;

}
