#include "NewConnectionPool.h"

ConnPool_t initConnPool () {

    ConnPool_t conn_pool = (ConnPool_t)malloc(sizeof(*conn_pool));
    if (!conn_pool) {
       printf("Conn Pool malloc error\n");
       return NULL;
    }

   conn_pool->pool = (RemoteConn_t *)malloc(sizeof(RemoteConn_t)*INIT_POOL_SIZE);
   if (!conn_pool->pool) {
      printf("Remote Conn Pool malloc error\n");
      return NULL;
   }
 
   conn_pool->num_conn = 0;

   pthread_mutex_init(&conn_pool->mux, NULL);
   pthread_cond_init(&conn_pool->cond, NULL);

   return conn_pool;
}  

int initRemoteConnection(RemoteConn_t rem_conn, int ip, int port) {
     if (!rem_conn) {
        printf("%s: Invalid Remote Connection\n", __func__);
        return 0;
     }
     rem_conn->ip = ip;
     rem_conn->port = port;
     rem_conn->in_use = 0;
     rem_conn->state = 0;
     rem_conn->next = NULL;
     pthread_mutex_init(&rem_conn->mux, NULL);
     pthread_cond_init(&rem_conn->cond, NULL);
}
    
RemoteConn_t * reallocConnectionPool(ConnPool_t conn_pool) {
    if (!conn_pool) {
        printf("%s: Invalid connection pool\n", __func__);
        return NULL;
    }

    int new_pool_size = conn_pool->num_conn + BATCH_POOL_SIZE;
    RemoteConn_t * rem_conn = (RemoteConn_t *)malloc(sizeof(RemoteConn_t)*new_pool_size);
    if (!rem_conn) {
       printf("%s: Remote Connection Pool memory allocation failed\n", __func__);
       return NULL;
    }
    for (int i=0; i < new_pool_size; i++) {
        if (i < conn_pool->num_conn) {
           rem_conn[i] = conn_pool->pool[i];
        } else {
           rem_conn[i] = NULL;
        }
    }
    return  rem_conn;  
}

RemoteConn_t getConnection (ConnPool_t conn_pool, int ip, int port) {

    if (!conn_pool) {
        printf("%s: Invalid Connection Pool", __func__);
        return NULL;
    }
    
    pthread_mutex_lock(&conn_pool->mux);
    
    for (int i=0; i<conn_pool->num_conn; i++) {
        assert(conn_pool->pool+i);
        if ((conn_pool->pool[i])->ip == ip && 
             conn_pool->pool[i]->port == port) {
             printf("%s: Found connection in pool for IP %d and Port %d\n", __func__ , ip, port);
             RemoteConn_t rem_conn = conn_pool->pool[i];
             pthread_mutex_unlock(&conn_pool->mux);
             pthread_mutex_lock(&rem_conn->mux);
             while (rem_conn->in_use) {
                 pthread_cond_wait(&rem_conn->cond, &rem_conn->mux);
             }
             rem_conn->in_use = 1;
             pthread_mutex_unlock(&rem_conn->mux);
             return rem_conn; 
        }
    }

    if (conn_pool->num_conn < MAX_POOL_SIZE) {
        printf("%s: Connection not found in pool for IP %d and Port %d, allocating\n", __func__, ip, port);
        RemoteConn_t * rem_conn = (RemoteConn_t *)malloc(sizeof(*rem_conn));
        if (!rem_conn) {
           printf("%s: Remote connection memory allocation failed\n", __func__);
           pthread_mutex_unlock(&conn_pool->mux);
           return NULL;
        }
        initRemoteConnection(*rem_conn, ip, port);
        conn_pool->pool[conn_pool->num_conn++] = *rem_conn;
        pthread_mutex_unlock(&conn_pool->mux);
        return *rem_conn;
    } else {
       RemoteConn_t * tmp_rem_conn_pool = reallocConnectionPool(conn_pool);
       free(conn_pool->pool);
       conn_pool->pool = tmp_rem_conn_pool;
       RemoteConn_t * rem_conn = (RemoteConn_t *)malloc(sizeof(*rem_conn)); 
       initRemoteConnection(*rem_conn, ip, port);
       conn_pool->pool[conn_pool->num_conn++] = *rem_conn; 
       pthread_mutex_unlock(&conn_pool->mux);
       return *rem_conn;
    }

    pthread_mutex_unlock(&conn_pool->mux);
    return NULL;
}        
    
int ReleaseConnection (ConnPool_t conn_pool, int ip, int port) {
    if (!conn_pool) {
        printf("%s: Invalid Connection Pool\n", __func__);
        return 0;
    }

    for (int i=0; i < conn_pool->num_conn; i++) {
         if (conn_pool->pool[i]->ip == ip &&
             conn_pool->pool[i]->port == port) {
              RemoteConn_t rem_conn = conn_pool->pool[i];
              pthread_mutex_unlock(&conn_pool->mux);
              pthread_mutex_lock(&rem_conn->mux);
              rem_conn->in_use = 0;
              pthread_mutex_unlock(&rem_conn->mux);
              return 1;
         }
    }
    printf("%s: Invalid Connection, could not find in pool\n", __func__);
    return 0;
}  

void * ConnectionThr (void *args) {

    struct ConnectionArgs *conn_args = (struct ConnectionArgs *)args; 
    getConnection(conn_args->conn_pool, conn_args->ip, conn_args->port);
}

int main() {

  ConnPool_t conn_pool = initConnPool();
  int port = 10;
  int ip = 100;

  int i=0;
  
  while (i<10) {
    pthread_t thr;
    struct ConnectionArgs args;
    args.conn_pool = conn_pool;
    args.ip = ip;
    args.port = port;
    pthread_create(&thr, NULL, ConnectionThr, (void *)&args);
    port = port+10;
    ip = ip + 100;
    i++;
  }    
  return 0;
}
