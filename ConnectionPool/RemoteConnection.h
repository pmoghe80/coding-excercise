#include "NewConnectionPool.h"

typedef struct RemoteConnection * RemoteConn_t;

struct RemoteConnection {
    int conn_id;
    int ip_addr;
    int port;
    int state;
    int in_use;
    pthread_mutex_t mux;
    pthread_cond_t cond;
    RemoteConn_t next;
};
