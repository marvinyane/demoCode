#define DEBUG
#ifdef DEBUG
#include<stdio.h>
#include<Stdlib.h>
#include<string.h>
#include<math.h>
#endif
#define IS_EXE_FATHER_FUNC int
#define SET_EXE_PARENT_FUNC(x,f) (x |= 1 << ((int)&(((Fops*)0)->f) / sizeof(void*)))
typedef enum _Status{
    NONE,
    INIT,
    UPDATA,
    LOOP,
    SHUTDOEN
}PROCESS_STATUS_ENUM;

typedef struct _Fops{
    void (*init)(void);
    void (*update)(void);
    void (*loop)(void);
}Fops;

typedef struct _State{
    PROCESS_STATUS_ENUM status;
    IS_EXE_FATHER_FUNC  bit;
    Fops* my_fops;
}State;

typedef struct _Context{
    State* state;

    Fops* parent_fops;
}Context;

void parent_init(){
    printf("this is parent init...\n");
}

void parent_updata(){
    printf("this is parent updata...\n");
}

void parent_loop(){
    printf("this is parent loop...\n");
}
Fops parent_fops = {
    parent_init,
    parent_updata,
    parent_loop
};

State state = {
    INIT,
    NULL
};

Context context = {
    &state,
    &parent_fops
};

int main(){
    int ram = rand();
    int now_state = ram % 3;
    int bits = 0;
    SET_EXE_PARENT_FUNC(bits, loop);
    printf("%d\n", bits);
    
    return 0;
}
