#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LIMIT 1000000

int power (int x, int y) {
   int tmp = 1;
   int i   = 0;
   while (i < y) {
       tmp = tmp * x;
       i++;
   }
   //printf("Power %d to %d is %d", y, x, tmp);
   return tmp;
}

void RabinKarp(char *T, char *P, int radix, int prime) {
   int tlen = strlen(T);
   int plen = strlen(P);
   if (P[plen-1] == '\n') { 
       plen = plen - 1;
   }
   int h   = (int)(power(radix, plen-1)) % prime;
   int p   = 0;
   int t   = 0;
   int i   = 0;

   while (i < plen) {
       p = ((radix*p) + P[i]) % prime;
       t = ((radix*t) + T[i]) % prime;
       i++;
   }

   for (i=0; i < (tlen-plen);i++) {
       if (p == t) {
	  printf("Found Equal Hash at %d\n", i);     
          int j  = 0;
	  int eq = 1; 
          while (j < plen) {
	     if (P[j] != T[i+j]) {
	        eq = 0;
                break;
             }
	     j++;
          } 
          if (eq) {
	     printf("Pattern found at shift %d\n", i);
          }
       }
       if ( i < (tlen-plen) ) {
           t = ((radix*(t - (h*T[i]))) + T[i+plen]) % prime;   
	   if (t < 0) {
               t = t + prime;
           }
       }	   
    }    
}

int main() {
    char *text = malloc(sizeof(char)*MAX_LIMIT);
    char *pattern = malloc(sizeof(char)*5);
    int  prime = 29;
    int  radix = 256;

    printf("Enter Text\n");
    fgets(text, MAX_LIMIT, stdin);  

    printf("Enter Pattern\n");
    fgets(pattern, 5, stdin);
    RabinKarp(text, pattern, radix, prime);
    return 0; 
} 
