#ifndef SERVER_H
#define SERVER_H 

#include <sys/socket.h>
#include <netinet/in.h>
#include <net/ethernet.h>
#include "../Common/Error_Handling.h"

typedef struct Server {

    int port;                       // port for the os to refidirect the traffic
    int socketfd;                   // file descriptor for the socket
    int backlog;                    // number of simultaneous connnections
    int interface;                  // this holds the actual IP address for the socket
    int address_family;             // socket address family 
    int domain;                     // communication domain, version of IP
    int protocol;                   // Data transfer protocol
    struct sockaddr_in server_addr; // Describes an IPv4 Internet domain socket address
    
    int (*run_func)(); 

} Server;

Server create_server(int port, int domain, int address_family, int protocol, int socket_type, int interface, 
                     int backlog); 
#endif
