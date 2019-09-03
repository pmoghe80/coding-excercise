#include <iostream>
#include <atomic>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

using namespace std;

typedef struct Node * Node_t;

struct Node {
     Node_t next;
     int data;
};

atomic<Node_t>   ahead;
Node_t           mhead;
pthread_mutex_t  mlock;
void * AtomicAddNode (void *arg) {
     int data = *(int *)arg;
     Node_t tmp = (Node_t)malloc(sizeof(*tmp));

     tmp->data = data; 
     tmp->next = ahead;

     while (!atomic_compare_exchange_weak(&ahead, &tmp->next, tmp)) {
          
     }
}

void * MutexAddNode (void *arg) {
     int data = *(int *)arg;
     Node_t tmp = (Node_t)malloc(sizeof(*tmp));

     tmp->data = data; 
     tmp->next = ahead;

     pthread_mutex_lock(&mlock);
     tmp->next = mhead;
     mhead = tmp;
     pthread_mutex_unlock(&mlock);
     return NULL;
}


int main() {
    pthread_t apt[10000];
    pthread_t mpt[10000];
    int i=0;
    int arr[10000];
    struct timeval start_tv;
    struct timeval end_tv;
    struct timeval tv;
    long long int start, end;
    long long int start_usec, end_usec;

    //gettimeofday(&start_tv, NULL);
    //start = tv.tv_sec;
    //start_usec = tv.tv_usec; 
    /*while (i < 10000) {
         arr[i] = i;
         pthread_create(&apt[i], NULL, AtomicAddNode, (void *)&arr[i]);
         i++;
    }       
     
    for (i=0; i<10000; i++) {
         pthread_join(apt[i], NULL);
    } */

    //gettimeofday(&end_tv, NULL); 
    //end = tv.tv_sec;
    //end_usec = tv.tv_usec; 
    //timersub(&start_tv, &end_tv, &tv); 
    //printf("Atomic Time taken: %ld, %ld\n", (long int)tv.tv_sec, (long int)tv.tv_usec);

    /******* MUTEX Code Starts ***********/
    //gettimeofday(&start_tv, NULL);
    //start = tv.tv_sec;
    pthread_mutex_init(&mlock, NULL);
    i = 0;
    while (i < 10000) {
         arr[i] = i;
         pthread_create(&mpt[i], NULL, MutexAddNode, (void *)&arr[i]);
         i++;
    }       

    for (i=0; i<10000; i++) {
         pthread_join(mpt[i], NULL);
    } 
    //gettimeofday(&end_tv, NULL); 
    //end = tv.tv_sec;
    //printf("Mutex Time taken: %lld, %lld, %lld\n", end-start, start_usec, end_usec);
    //timersub(&start_tv, &end_tv, &tv); 
    //printf("Mutex Time taken: %ld, %ld\n", (long int)tv.tv_sec, (long int)tv.tv_usec);

    return 0; 
}
   
       
