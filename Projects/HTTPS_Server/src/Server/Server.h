#ifndef SERVER_H
#define SERVER_H 

#include <sys/socket.h>
#include <netinet/in.h>
#include <net/ethernet.h>
#include "../Common/Error_Handling.h"

typedef struct Server {

    int port;
    int socketfd;
    int backlog;
    int interface;
    int address_family;
    int domain;
    int protocol;
    struct sockaddr_in server_addr;

    int (*run_func)(); 

} Server;

Server create_server(int port, int domain, int address_family, int protocol, int socket_type, int interface, 
                     int backlog); 
#endif
