#include "Server.h"

Server create_server(int port, int domain, int address_family, int protocol, int socket_type, int interface, 
                     int backlog) {

    Server server;

    server.port = port;
    server.address_family = address_family;
    server.domain = domain;
    server.interface = interface;
    server.backlog = backlog;
    server.protocol = protocol;

    server.server_addr.sin_addr.s_addr = interface;
    server.server_addr.sin_family = address_family;
    server.server_addr.sin_port = htons(port);
    server.socketfd = socket(domain, address_family, protocol);
     
    handle_error_and_exit(server.socketfd, "Could not initialize socket")

    handle_error_and_exit(bind(server.socketfd, (struct sockaddr*) &server.server_addr, sizeof(server.server_addr)), "Could not bind socket")

    handle_error_and_exit(listen(server.socketfd, backlog), "Could not activate the socket for listening for connections")

    return server; 
}



