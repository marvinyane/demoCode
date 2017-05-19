#include <stdio.h>

typedef struct
{
    int head;
    int tail;
    int size;
    char buffer[1];
}RINGBUFFER, *RING_HANDLER;

static int getRingBufferLength(RING_HANDLER ptr)
{
    if (ptr->head <= ptr->tail)
    {
        return ptr->tail - ptr->head;
    }
    else
    {
        return ptr->size - ptr->head + ptr->tail + 1;
    }
}

RING_HANDLER ring_init(int size)
{
    RING_HANDLER ptr = malloc(sizeof(RING_HANDLER) + size);
    memset(ptr, 0, sizeof(RING_HANDLER) + size);

    ptr->head = 0;
    ptr->tail = 0;
    ptr->size = size;

    return ptr;
}

void ring_deinit(RING_HANDLER ptr)
{
    free(ptr);
}

int ring_read(RING_HANDLER ptr, char* buf, int size)
{
    int len = 0;

    if (ptr->tail >= ptr->head)
    {
        len = ptr->tail - ptr->head;
        if (len < size)
        {
            len = size;
        }

        memcpy(buf, ptr->buffer + ptr->head, len);
        // modify header
    }
    else
    {
        if (len <= (ptr->size - ptr->head + 1))
        {
            memcpy(buf, ptr->buffer + ptr->head, len);
            // modify header
        }
        else
        {

        }
    }
}

int ring_write(RING_HANDLER ptr, char* buf, int size)
{

}
