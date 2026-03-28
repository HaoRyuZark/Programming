#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Socket Includes
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main() {

    int sockfd; // Socket file descriptor

    //Port range
    int start_port;
    int end_port;   
    
    //IP buffer
    char ip[16];
    
    //User Input
    printf("Target Ip: ");
    scanf("%s", ip); // Add security 

    printf("\nStarting port: ");
    scanf("%d", &start_port);

    printf("\nEnd port: ");
    scanf("%d", &end_port);

    // Socket Setup 
    struct sockaddr_in sr_addr;
    sr_addr.sin_family = AF_INET;
    sr_addr.sin_addr.s_addr = inet_addr(ip);

    int result;

    for (int i = start_port; i <= end_port; i++) {

        sr_addr.sin_port = htons(i);
        sockfd = socket(AF_INET, SOCK_STREAM, 0);

        result = connect(sockfd, (struct sockaddr*) &sr_addr, sizeof(sr_addr));

        if (result >= 0) {
            printf("\nOpen port %d", result);
        }

        close(sockfd);
    }

    
    return 0;
}
