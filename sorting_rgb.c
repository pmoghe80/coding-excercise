#include <stdio.h>
#include <stdlib.h>

int main() {

   //char arr[] = {'g','r','b','r','r','r','r','g','b','g','b','r','b'};
   char arr[] = {'r','r','r','r','r','r','r','g','g','g','b','b','b'};

   int rptr=0;
   int gptr=0;
   int ptr=0;

    while (arr[ptr] == 'r') {
        ptr++;
    }
 
    rptr = ptr+1;
    while (rptr < 13) {
       if (arr[rptr] == 'r') {
           char tmp = arr[ptr];
           arr[ptr++] = arr[rptr];
           arr[rptr++] = tmp;
       }
       while (rptr < 13 && arr[rptr] != 'r') {
           rptr++;
       }
    }

 
    printf("%d %d\n", ptr, rptr);
    while (arr[ptr] == 'g') {
       ptr++;
    }

    rptr = ptr+1;
    while (rptr < 13) {
       if (arr[rptr] == 'g') {
           char tmp = arr[ptr];
           arr[ptr++] = arr[rptr];
           arr[rptr++] = tmp;
       }
       while (rptr < 13 && arr[rptr] != 'g') {
           rptr++;
       }
    }
       
    int i=0;
    while (i < 13) {
       printf("%c ", arr[i++]);
    }
    printf("\n");
    return 0;
}  
             
     
