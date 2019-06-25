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
     //for (int i=0; i < 5000; i++) {
     Node_t tmp = (Node_t)malloc(sizeof(*tmp));

     tmp->data = data; 
     tmp->next = ahead;

     //srand(1);
     //printf("Adding Node %d\n", data);
     while (!atomic_compare_exchange_weak(&ahead, &tmp->next, tmp)) {
          
     }
      // data++; 
     //}
     //sleep(rand()%30000);
}

void * MutexAddNode (void *arg) {
     int data = *(int *)arg;
     //for (int i=0; i < 5000; i++) {
     Node_t tmp = (Node_t)malloc(sizeof(*tmp));

     tmp->data = data; 
     tmp->next = ahead;

     //srand(1);
     //printf("Mutex Adding Node %d\n", data);
     pthread_mutex_lock(&mlock);
     tmp->next = mhead;
     mhead = tmp;
     pthread_mutex_unlock(&mlock);
     //sleep(rand()%30000);  
      //data++;
    // }
     return NULL;
}


int main() {
    pthread_t apt[30000];
    pthread_t mpt[30000];
    int i=0;
    int arr[30000];
    struct timeval tv;
    long long int start, end;
    long long int start_usec, end_usec;

    //arr[0] = 1;
    //arr[1] = 5000;
    gettimeofday(&tv, NULL);
    start = tv.tv_sec;
    start_usec = tv.tv_usec; 
    while (i < 30000) {
         arr[i] = i;
         pthread_create(&apt[i], NULL, AtomicAddNode, (void *)&arr[i]);
         i++;
    }       
     
    for (i=0; i<30000; i++) {
         pthread_join(apt[i], NULL);
    }  

    gettimeofday(&tv, NULL); 
    end = tv.tv_sec;
    end_usec = tv.tv_usec; 
 
    printf("Atomic Time taken: %lld, %lld, %lld\n", end-start, start_usec , end_usec);

    /******* MUTEX Code Starts ***********/
    gettimeofday(&tv, NULL);
    start = tv.tv_sec;
    pthread_mutex_init(&mlock, NULL);
    i = 0;
    while (i < 30000) {
         arr[i] = i;
         pthread_create(&mpt[i], NULL, MutexAddNode, (void *)&arr[i]);
         i++;
    }       

    for (i=0; i<30000; i++) {
         pthread_join(mpt[i], NULL);
    }  
    gettimeofday(&tv, NULL); 
    end = tv.tv_sec;
    printf("Mutex Time taken: %lld, %lld, %lld\n", end-start, start_usec, end_usec);

    return 0; 
}
   
       
