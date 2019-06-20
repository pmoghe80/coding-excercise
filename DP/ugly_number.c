#include <stdio.h>
#include <stdlib.h>

#define MIN(x,y,z) (x <= y ? (x <= z ? x : z) : (y <= z ? y : z))

int GetNthUgly (int n) {

    int *ugly = (int *)malloc(sizeof(int)*n);
    int  i =0, i2 = 0, i3 = 0, i5 = 0;

    int next_multiple_2 = 0;  
    int next_multiple_3 = 0;  
    int next_multiple_5 = 0;  

    ugly[0] = 1;
    next_multiple_2 = 2;    
    next_multiple_3 = 3;    
    next_multiple_5 = 5; 
  
    i = 1;
    while ( i < n ) { 

       ugly[i] = MIN (next_multiple_2, next_multiple_3, next_multiple_5);

       if (next_multiple_2 == ugly[i]) {
           i2 = i2 + 1;
           next_multiple_2 = ugly[i2] * 2;   
       }
       if (next_multiple_3 == ugly[i]) {
           i3 = i3 + 1;
           next_multiple_3 = ugly[i3] * 3;   
       }
       if (next_multiple_5 == ugly[i]) {
           i5 = i5 + 1;
           next_multiple_5 = ugly[i5] * 5;   
       }
       i = i + 1;
    }
    return ugly[i-1];
}

int main () {

    int n = 10;
    printf("%d\n", GetNthUgly(n));
    return 0;
}
