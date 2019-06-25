#include <iostream>
#include <atomic>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>


#define RANGE 10000
using namespace std;

volatile atomic<long int> mutex_sum_val;
volatile atomic<long int> atomic_sum_val;
long int arr[RANGE];

pthread_mutex_t sum_lock;

struct myrange {
    int start;
    int end;
};


//Function to compute sum using atomic global sum variable
void * atomic_sum (void *arg) {
     struct myrange *range = (struct myrange *)arg;
     int i = range->start; 
     while (i <= range->end) {
        atomic_fetch_add(&atomic_sum_val, arr[i]);
        i++;
     }
     return NULL; 
}

//Function to compute sum using mutex for global sum variable.
void * mutex_sum (void *arg) {
     int local_sum = 0;
     struct myrange *range = (struct myrange *)arg;
     int i = range->start; 
     while (i <= range->end) {
          local_sum = local_sum + arr[i];
          i++;
     }
     pthread_mutex_lock(&sum_lock);
      mutex_sum_val = mutex_sum_val + local_sum;
     pthread_mutex_unlock(&sum_lock);
     return NULL;
}

int main() {

    struct timeval tm; 
    int start_usec;
    int end_usec;

    pthread_t atomic_pt[2];
    pthread_t mutex_pt[2];
    int j=0;
    int i=0;

    for (i = 0; i < RANGE; i ++) {
        arr[i] = i+1;
    }
    
    struct myrange range[2];
         
    gettimeofday(&tm, NULL);
    start_usec = tm.tv_usec;

    for (i=0; i < 2; i++) {
       //struct myrange rang =  { .start = j, .end = j+99 }; 
       range[i] = { .start = j, .end = j+4999 };
       pthread_create (&atomic_pt[i], NULL, atomic_sum, (void *)&range[i]);
       j = j + 5000;
    }

    for (i=0; i < 2; i++) {
        pthread_join(atomic_pt[i], NULL);
    }
    gettimeofday(&tm, NULL);
    end_usec = tm.tv_usec;

    //cout << "Sum is " << atomic_sum_val << endl;
    cout << "Time take to compute(Atomic) " << end_usec - start_usec << "usec" << endl;

    gettimeofday(&tm, NULL);
    start_usec = tm.tv_usec;

    /************* MUTEX PART OF CODE ****************/
    pthread_mutex_init(&sum_lock, NULL);
    j = 0;
    struct myrange mrange[2];
    for (i=0; i < 2; i++) {
       mrange[i] = { .start = j, .end = j+4999 };
       pthread_create (&mutex_pt[i], NULL, mutex_sum, (void *)&mrange[i]);
       j = j + 5000;
    }

    for (i=0; i < 2; i++) {
        pthread_join(mutex_pt[i], NULL);
    }
    gettimeofday(&tm, NULL);
    end_usec = tm.tv_usec;

    //cout << "Sum is " << mutex_sum_val << endl;
    cout << "Time take to compute(Mutex) " << end_usec - start_usec << "usec" << endl;
    return 0;
}     
