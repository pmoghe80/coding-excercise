#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define REMOTECONNECTIONHDR

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
