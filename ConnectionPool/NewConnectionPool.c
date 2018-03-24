#include "NewConnectionPool.h"

ConnPool_t initConnPool () {

    ConnPool_t conn_pool = (ConnPool_t)malloc(sizeof(*conn_pool));
    if (!conn_pool) {
       printf("Conn Pool malloc error\n");
       return NULL;
    }

   conn_pool->pool = (RemoteConn_t)malloc(sizeof(*(conn_pool->pool))*INIT_POOL_SIZE);
   if (!conn_pool->pool) {
      printf("Remote Conn Pool malloc error\n");
      return NULL;
   }
 
   conn_pool->num_conn = 0;

   pthread_mutex_init(&conn_pool->mux, NULL);
   pthread_cond_init(&conn_pool->cond, NULL);

   return conn_pool;
}  
    
RemoteConn_t getConnection (ConnPool_t conn_pool, int ip, int port) {

    if (!conn_pool) {
        printf("%s: Invalid Connection Pool", __func__);
        return NULL;
    }
    
    pthread_mutex_lock(&conn_pool->mux);
    
    for (int i=0; i<conn_pool->num_conn; i++) {
        assert(conn_pool->pool+i);
        if (conn_pool->pool[i]->ip == ip && 
            conn_pool->pool[i]->port == port) {
             RemoteConn_t rem_conn = conn_pool->pool[i];
             pthread_mutex_unlock(&conn_pool->mux);
             pthread_mutex_lock(&rem_conn->mux);
             while (rem_conn->in_use) {
                 pthread_cond_wait(&rem_conn->cond);
             }
             rem_conn->in_use = 1;
             pthread_mutex_unlock(&rem_conn->mux);
             return rem_conn; 
        }
    }

    if (conn_pool->num_conn < MAX_POOL_SIZE) {
        printf("%s: Connection not found in pool, allocating\n", __func__);
        RemoteConn_t rem_conn = (RemoteConn_t)malloc(sizeof(*rem_conn));
        if (!rem_conn) {
           printf("%s: Remote connection memory allocation failed\n", __func__);
           pthread_mutex_unlock(&conn_pool->mux);
           return NULL;
        }
        initRemoteConnection(rem_conn);
        conn_pool->pool[num_conn++] = rem_conn;
        pthread_mutex_unlock(&conn_pool->mux);
        return rem_conn;
    } else {
       reallocConnectionPool(&conn_pool);
       pthread_mutex_unlock(&conn_pool->mux);
       getConnection(conn_pool, ip, port);
       pthread_mutex_lock(&conn_pool->mux);
    }
    return NULL;
}        
    
  

int main() {

  printf("Hello World\n");
  return 0;
}
