#include <stdio.h>

#define GET_BIT_MASK(x, y) (x & (1 << y))
#define SET_BIT_MASK_ON(x, y) (x |= (1 << y) )
#define SET_BIT_MASK_OFF(x, y) (x &= (~(1<<y)))

char *cmd[] = {
    "ls",
    "ld",
    "ln",
    "cmd",
    "chmod",
    "tar",
    "whoami",
    "mount",
    "cat",
    "touch",
    "mkdir",
    NULL
};
int bitmask = -1;
int bitmasktmp = -1;

int main()
{
    char ch = 0;
    int i = 0;
    int tabcnt = 0;
    while(ch = getch()){
    AGAIN:
        if(ch == 13){
            i = 0;
            tabcnt = 0;
            break;
        }
        else if(ch == 8){
            putchar(' ');
            putchar(8);
            i--;
            continue;
        }
        else if(ch == 9){
            int j = 0;
            int k = 0;
            for(; cmd[j]; j++){
                if(GET_BIT_MASK(bitmask, j)){
                    if(++k > tabcnt){
                        for(k = i; k >=0; k--){
                            putchar(8);
                            putchar(' ');
                            putchar(8);
                        }

                        for(i =0; cmd[j][i]; i++)
                            putchar(cmd[j][i]);
                        
                        break;
                    }
                }
            }
            if(k > 0 && k <= tabcnt){
                tabcnt=0;
                goto AGAIN;
            }
            else if(k == 0){
                tabcnt = 0;
                bitmask = bitmasktmp;
                goto AGAIN;
            }
            else
                tabcnt++;
        }
        else{
            int j = 0;
            printf("%c", ch);

            while(cmd[j] && GET_BIT_MASK(bitmask, j)){
                if(cmd[j][i] != ch){
                    SET_BIT_MASK_OFF(bitmask, j);
                }
                j++;
            }
            if(bitmask != 0)
                bitmasktmp = bitmask;
        }
        i++;
    }

    return 0;
}
