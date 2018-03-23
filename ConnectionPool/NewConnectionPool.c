#include "NewConnectionPool.h"

ConnPool_t initConnPool () {

    ConnPool_t conn_pool = (ConnPool_t)malloc(sizeof(*conn_pool));
    if (!conn_pool) {
       printf("Conn Pool malloc error\n");
       return NULL;
    }

   conn_pool->pool = (RemoteConn_t)malloc(sizeof(RemoteConn_t)*INIT_POOL_SIZE);
   if (!conn_pool->pool) {
      printf("Remote Conn Pool malloc error\n");
      return NULL;
   }
 
   conn_pool->num_conn = 0;

   pthread_mutex_init(&conn_pool->mux, NULL);
   pthread_cond_init(&conn_pool->cond, NULL);

   return conn_pool;
}  
    
int getConnection (ConnPool_t conn_pool) {

    if (!conn_pool) {
        printf("%s: Invalid Connection Pool", __FUNC__);
        return 0;
    }
    
    for (int i=0; i<conn_pool->num_conn; i++) {
        if (conn
    
  

int main() {

  printf("Hello World\n");
  return 0;
}
