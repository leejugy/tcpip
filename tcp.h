#ifndef __TCP__
#define __TCP__

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <semaphore.h> 

#define TCP_LOCAL_ADDRESS "127.0.0.1"
#define TCP_PORT 1972

#define printg(fmt, ...) printf("[\x1b[33m%s\x1b[0m]" fmt "\n", __FUNCTION__, ##__VA_ARGS__)
#define printr(fmt, ...) printf("[\x1b[31m%s\x1b[0m]" fmt "\n", __FUNCTION__, ##__VA_ARGS__)

int init_server(int port, int *fd);
int accept_server(int fd);
int init_client(int port, char *server_ip);
int sock_recv(int fd, void *buffer, size_t buffer_size);
int sock_send(int fd, void *buffer, size_t buffer_size);


#endif