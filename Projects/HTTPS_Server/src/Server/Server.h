#ifndef SERVER_H
#define SERVER_H 

typedef struct Server {

    int port;
    int socket;

    int (*run_func)(); 

} Server;

Server create_server(int port, int protocol, int address_family);

#endif
