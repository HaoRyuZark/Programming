#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/time.h>
#include <errno.h>
#include <signal.h>

#define PKT_SIZE 64
#define TIMEOUT_SEC 5

int sock = -1;
int tx_count = 0;
int rx_count = 0;
unsigned int dest_addr;

// Parity check for data integrity
unsigned short in_cksum(unsigned short* addr, int count) {

    // Standard internet check sum algorithm
    unsigned long sum = 0;

    while (count > 0) {
        sum += *addr;
        count -= 2;
    }
    
    if (count > 0) {
        sum += *(unsigned char*) addr;
    }

    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);

    return (~sum);
}

// Raw Socket with timeout
int init_socket() {
    
    int s = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    
    if (s < 0) {
        perror("Socket error");
        return -1;
    }

    struct timeval tv_out;
    
    tv_out.tv_sec = TIMEOUT_SEC;
    tv_out.tv_usec = 0;

    if (setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &tv_out, sizeof(tv_out)) < 0) {
        perror("No response");
        return -1;
    }

    return s;
}

// Preparing ICMP packet  (echo)
void prep_packet(char* sendbuf, int seq) {
   
    memset(sendbuf, 0, PKT_SIZE);
    struct icmp* icmp_pkt = (struct icmp*)sendbuf;

    icmp_pkt->icmp_type = ICMP_ECHO;
    icmp_pkt->icmp_code = 0;
    icmp_pkt->icmp_id = getpid() & 0xFFFF;
    icmp_pkt->icmp_seq = seq;

    memset(sendbuf + sizeof(struct icmphdr), 0x42, PKT_SIZE);

    icmp_pkt->icmp_cksum = 0;
    icmp_pkt->icmp_cksum = in_cksum((unsigned short*)icmp_pkt, PKT_SIZE);
}

int send_packet(int sock, char* sendbuf, struct sockaddr_in* dest) {
    
    int bytes = sendto(sock, sendbuf, PKT_SIZE, 0, (struct sockaddr*)dest, sizeof(*dest));
    
    if (bytes < 0) {
        perror("Could not send packet");
    }

    return bytes;
}

int receive_packet(int sock, char* recvbuf, size_t bufsize, struct sockaddr_in* from) {

    socklen_t fromlen = sizeof(*from);

    int bytes = recvfrom(sock, recvbuf, bufsize, 0, (struct sockaddr*)from, &fromlen);

    return bytes;
}

void process_reply(char* recvbuf, int bytes, struct sockaddr_in* from, int seq, struct timeval* tv_start, struct timeval* tv_end) {

    struct ip* ip_hdr = (struct ip*)recvbuf;
    int hlen = ip_hdr->ip_hl << 2;
    struct icmp* icmp_reply = (struct icmp*)(recvbuf + hlen);

    if (icmp_reply->icmp_type == ICMP_ECHOREPLY && icmp_reply->icmp_id == (getpid() & 0xFFFF)) {

        rx_count++;

        double rtt = (tv_end->tv_sec - tv_start->tv_sec) * 1000.0 + (tv_end->tv_usec - tv_start->tv_usec) / 1000.0;

        printf("%d bytes from %s: icmp_seq=%d ttl=%d time+=%.3f ms\n", bytes - hlen, inet_ntoa(from->sin_addr), icmp_reply->icmp_seq, ip_hdr->ip_ttl, rtt);
    }

}

void cleanup(int sig) {
    
    printf("\n--- %s ping statistics ---\n", inet_ntoa(*(struct in_addr*)&dest_addr));

    float loss = 0.0;
    
    if (tx_count > 0) {
        loss = 100.0 * (tx_count - rx_count) / tx_count;
    }

    printf("%d packets transmitted, %d received, %.1F%% packet loss\n", tx_count, rx_count, loss);

    if (sock > 0) {
        close(sock);
    }

    exit(0);
}

int ping_loop(int sock, struct sockaddr_in* dest) {
    
    char sendbuf[PKT_SIZE];
    char recvbuf[PKT_SIZE + sizeof(struct ip)];

    struct sockaddr_in from;
    struct timeval tv_start, tv_send;
    int bytes;

    while (1) {

        prep_packet(sendbuf, tx_count++);
        gettimeofday(&tv_start, NULL);
        
        bytes = send_packet(sock, sendbuf, dest);
        
        if (bytes < 0) {

            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                printf("Request timeout for icmp_seq=%d\n", tx_count - 1);
            }
            else {
                perror("recvfrom error");
            }
        }
        else {
            process_reply(recvbuf, bytes, &from, tx_count - 1, &tv_start, &tv_send);
        }

        sleep(1);
    }

    return EXIT_SUCCESS;
}

int main (int argc, char** argv) {
    
    if (argc != 2) {
        fprintf(stderr, "Provide only a host name");
        return EXIT_FAILURE;
    }

    if (inet_pton(AF_INET, argv[1], &dest_addr) <= 0) {
        fprintf(stderr, "Bad address");
        return EXIT_FAILURE;
    }

    signal(SIGINT, cleanup);

    sock = init_socket();
    
    if (sock < 0) {
        return EXIT_FAILURE;
    }

    struct sockaddr_in dest;
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = dest_addr;
    dest.sin_family = AF_INET;

    printf("PING %s (%s): %ld data bytes\n", argv[1], inet_ntoa(*(struct in_addr*)&dest_addr), PKT_SIZE - sizeof(struct icmphdr));

    return ping_loop(sock, &dest);
}
