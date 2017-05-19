#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>

static void* (*real_malloc)(size_t)=NULL;
static void (*real_free)(void*)=NULL;

typedef struct _MemNode {
    void* p;
    void* func;
    size_t size;
    struct _MemNode* next;
} MemNode;

MemNode* nodeHeader = NULL;
MemNode* nodeTailer = NULL;

void insert_node(MemNode* node) 
{
    if (nodeHeader == NULL) {
        nodeHeader = node;
        nodeTailer = nodeHeader;
    }
    else  {
        nodeTailer->next = node;
        nodeTailer = node;
    }
}

void remove_node(void* p) {
    MemNode* tmp = nodeHeader;
    MemNode* parent = NULL;
    while (tmp) {
        if (tmp->p == p) {
            if (parent == NULL) {
                nodeHeader = nodeHeader->next;
            }
            else {
                parent->next = tmp->next;
            }

            real_free(tmp);
            break;
        }

        parent = tmp;
        tmp = tmp->next;
    }
}

void dump_list() {
    MemNode* tmp = nodeHeader;
    while (tmp) {
        fprintf(stderr, "%s alloc size %d -> %p but not free.\n", tmp->func, tmp->size, tmp->p);
        tmp = tmp->next;
    }
}

static void mtrace_init(void)
{
    real_malloc = dlsym(RTLD_NEXT, "malloc");
    real_free = dlsym(RTLD_NEXT, "free");
    if (NULL == real_malloc || NULL == real_free) {
        fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
    }
}

void *malloc(size_t size)
{
    if(real_malloc==NULL) {
        mtrace_init();
    }

    void *p = NULL;
    p = real_malloc(size);
    fprintf(stderr, "real malloc with result %p.\n", p);

    MemNode* node = real_malloc(sizeof(MemNode));
    node->size = size;
    node->func = NULL;

    node->p = p;
    node->next = NULL;

    insert_node(node);

    return p;
}

void free(void* p)
{
    if (real_free == NULL) {
        mtrace_init();
    }

    remove_node(p);

    real_free(p);
}
