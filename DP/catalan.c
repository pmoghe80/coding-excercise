#include <stdio.h>
#include <stdlib.h>


int catalan (int *arr, int n) {

    if (arr[n]) {
        return arr[n];
    }
    
    if (n == 0) {
        arr[n] = 1;
        return arr[n];
    } else if (n == 1) {
        arr[n] = 1;
        return arr[n];
    }   

    int cat = 0;
    int i = 0;

    while (i < n) {
       cat = cat + catalan(arr, i)*catalan(arr, (n-1)-i);
       i++;
    }   
    arr[n] = cat;                    
    return cat;
}

int main() {

    int n = 90;
    int *arr = (int *)malloc(sizeof(int)*n);
    int j=0;
    while (j < n) {
        arr[j++] = 0;
    }
    printf("Catlan Number: %d\n" , catalan(arr, n));
    return 0;
}
