#include <stdio.h>
 #define MAX_STR_SIZE  4
 #define MAX_SIGN_SIZE 4
 
 int sign[MAX_SIGN_SIZE] = {0};
 char str[] = {'a', 'b','c', 'd'};
 
 int count = 0;
 int main()
 {
     int j , k;
     while(1)
     {
         count ++;
         for(j=0; j<MAX_SIGN_SIZE; j++)
         {
             printf("%c", str[sign[j]]);
         }
         printf("\n");
 
         if(++sign[MAX_SIGN_SIZE-1] < MAX_STR_SIZE)
         {
             continue;
         }
 
         for(k=MAX_SIGN_SIZE-1; k>=0; k--)
         {
             if(sign[k] >= MAX_STR_SIZE){
                 sign[k]=0;
                 if(k == 0)
                     goto result;
                 else
                     sign[k-1]++;
             }
             else
             {                                                                                                        
                 break;
             }
         }
 
     }
 
 result:
     printf("count = %d \n", count);
     return 0;
 }
