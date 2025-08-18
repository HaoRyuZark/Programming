#include <arpa/inet.h>
#include <bits/pthreadtypes.h>
#include <bits/types/struct_iovec.h>
#include <limits.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#define SERVERPORT 8989
#define BUFSIZE 4096
#define SOCKETERROR (-1)
#define SERVER_BACKLOG 10
#define THREAD_NUM 20

pthread_t thread_pool[THREAD_NUM];
pthread_mutex_t mutex;
pthread_cond_t cnd;

typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

//Queue
typedef struct Node_t {
    struct Node_t* next;
    int* client_socket;
} Node_t;

typedef struct Server_Queue {
    struct Node_t* first;
    struct Node_t* last;

} Server_Queue;

void enqueue(Server_Queue* self, int* client_socket) {

    Node_t *node = malloc(sizeof(Node_t));
    node->next = NULL;
    node->client_socket = client_socket;

    if (self->last == NULL) {
      self->first = node;
    } else {
      self->last->next = node;
    }

    self->last = node;
}

int* dequeue(Server_Queue* self) {
    if (self == NULL) {
      return NULL;
    }

    int* result = self->first->client_socket;
    Node_t* temp = self->first;
    self->first = self->first->next;
    if (self->first == NULL) {
      self->last = NULL;
    }
    free(temp);

    return result;
}

void* handle_connection(void* p_client_socket);
int check(int exp, const char* msg);
void* thread_function(void* arg);

Server_Queue queue = {
    .first = NULL, 
    .last = NULL
};

int main(int argc, char** argv) {

    int server_socket, client_socket,
        addr_size; // init sockets and the size of the address
    SA_IN server_addr, client_addr;

    for (int i = 0; i < THREAD_NUM; i++) {
      pthread_create(&thread_pool[i], NULL, thread_function, NULL);
    }
    check((server_socket = socket(AF_INET, SOCK_STREAM, 0)), "Failed socket");

    // init address_struct

    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);

    check(bind(server_socket, (SA* )&server_addr, sizeof(server_addr)),
          "Failed to bind");

    check(listen(server_socket, SERVER_BACKLOG), "Listen failed");

    pthread_mutex_init(&mutex, NULL);

    while (true) {
        printf("Waiting for connections");

        addr_size = sizeof(SA_IN);
        check((client_socket = accept(server_socket, (SA* )&client_addr,
                                      (socklen_t* )&addr_size)),"accept failed");
        printf("Connection accepted");
        
        //Pointer to int to store the client_sock
        int* pclient = malloc(sizeof(int)); 
        *pclient = client_socket;
        pthread_mutex_lock(&mutex); //create a mutex for enqueue
        enqueue(&queue, pclient);
        pthread_cond_wait(&cnd, &mutex); //if there is no work wait
        pthread_mutex_unlock(&mutex); //unlock mutex

    }

    return 0;
}

// Error checking function
int check(int exp, const char* msg) {
    if (exp == SOCKETERROR) {
      perror(msg);
    }

    return exp;
}

void* thread_function(void* arg) {
    while(true) {
        int* pclient;

        pthread_mutex_lock(&mutex);
        if((pclient = dequeue(&queue)) == NULL) {
             pthread_cond_wait(&cnd, &mutex); //if there is not work wait

            pclient = dequeue(&queue);

        }
        pthread_mutex_unlock(&mutex);

        if(pclient != NULL) {                   //if there are still pending clients then handle the connection
            handle_connection(pclient);
        }
    }
}

void* handle_connection(void* p_client_socket) {
      int client_socket = *((int *)p_client_socket);
      free(p_client_socket);
      char buffer[BUFSIZE];
      size_t bytes_read;
      int msgsize = 0;
      char actualpath[PATH_MAX + 1];

      // read clients message (file to read)
      while ((bytes_read = read(client_socket, buffer + msgsize,
                                sizeof(buffer) - msgsize - 1)) > 0) {
        msgsize += bytes_read;

        if (msgsize > BUFSIZE - 1 || buffer[msgsize - 1] == '\n') {
          break;
        }
      }

      check(bytes_read, "recv error");
      buffer[msgsize - 1] = 0;

      printf("REQUEST: %s\n", buffer);
      fflush(stdout);

      if (realpath(buffer, actualpath) == NULL) {
        printf("Error, bad path");
        close(client_socket);
        return NULL;
      }

      FILE *fp = fopen(actualpath, "r");
      if (fp == NULL) {
        printf("No File exists\n");
        close(client_socket);
        return NULL;
    }

    // read file contents and send to clients

    while ((bytes_read = fread(buffer, 1, BUFSIZE, fp)) > 0) {
      printf("sendig %zu bytes\n", bytes_read);
      write(client_socket, buffer, bytes_read);
    }

    close(client_socket);
    fclose(fp);
    printf("closing Connection\n");

    return NULL;
}
