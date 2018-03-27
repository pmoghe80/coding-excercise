#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>

#include "RemoteConnection.h"

#define MAX_POOL_SIZE     100
#define INIT_POOL_SIZE     10
#define BATCH_POOL_SIZE    10

typedef struct ConnectionPool * ConnPool_t;

struct ConnectionPool {
     RemoteConn_t *pool;
     int num_conn;
     pthread_mutex_t mux;
     pthread_cond_t cond;
};

struct ConnectionArgs {
   ConnPool_t conn_pool;
   int ip;
   int port;
};

ConnPool_t initConnPool ();
int putConnection (RemoteConn_t remConn);
RemoteConn_t getConnection ();
int getConnectionIndex ();

     
 

