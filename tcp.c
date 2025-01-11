#include "tcp.h"

sem_t socket_sem;

int init_server(int port, int *fd)
{
    int ret = 0;
    struct sockaddr_in server_attribute;
    int reuse_address = 1;
    memset(&server_attribute, 0, sizeof(server_attribute));

    ret = socket(AF_INET, SOCK_STREAM, 0);
    if (ret < 0)
    {
        perror("fail to open server");
        return ret;
    }

    server_attribute.sin_addr.s_addr = INADDR_ANY; // 모든 주소 받아들이기
    server_attribute.sin_family = AF_INET;         // inet사용(ipv4)
    server_attribute.sin_port = htons(port);       // 포트 설정 (호스트 비트 정렬 방식 -> 네트워크 비트 정렬 방식으로 변경)

    *fd = ret;

    ret = setsockopt(*fd, SOL_SOCKET, SO_REUSEADDR, &reuse_address, sizeof(reuse_address));
    if(ret < 0)
    {
        perror("fail to set socket option");
        return ret;
    }

    ret = bind(*fd, (struct sockaddr *)&server_attribute, sizeof(server_attribute)); // 서버 속성 설정
    if (ret < 0)
    {
        perror("fail to bind server");
        close(*fd);
        return ret;
    }

    ret = listen(*fd, 10);
    if (ret < 0)
    {
        perror("fail to listen server");
        close(*fd);
        return ret;
    }

    ret = sem_init(&socket_sem, 0, 1);
    if (ret < 0)
    {
        perror("fail to init semaphore server");
        return ret;
    }

    printg("init server complete");
    return 1;
}

int init_client(int port, char *server_ip)
{
    int ret = 0;
    int fd = 0;
    struct sockaddr_in clinet_attribute;
    in_addr_t address = 0;

    memset(&clinet_attribute, 0, sizeof(clinet_attribute));

    ret = socket(AF_INET, SOCK_STREAM, 0);
    if (ret < 0)
    {
        perror("fail to open socket client");
        return ret;
    }

    fd = ret;
    inet_pton(AF_INET, server_ip, &clinet_attribute.sin_addr);
    clinet_attribute.sin_port = htons(port);
    clinet_attribute.sin_family = AF_INET;

    ret = connect(fd, (struct sockaddr *)&clinet_attribute, sizeof(struct sockaddr));
    if (ret < 0)
    {
        perror("fail to connect server");
        return ret;
    }

    printg("init client complete");
    return fd;
}

int accept_server(int fd)
{
    int ret = 0;
    int len = sizeof(struct sockaddr_in);
    struct sockaddr_in client_info;
    memset(&client_info, 0, sizeof(client_info));

    ret = accept(fd, (struct sockaddr *)&client_info, &len);
    if (ret < 0)
    {
        perror("fail to accept client");
        close(fd);
        return ret;
    }

    printg("%s attach to server", inet_ntoa(client_info.sin_addr)); // 주소 변환해서 출력
    return ret;                                                     // 받아들인 클라이언트 소켓의 파일디스크립터
}

int sock_recv(int fd, void *buffer, size_t buffer_size)
{
    int ret = 0;

    sem_post(&socket_sem);
    ret = recv(fd, buffer, buffer_size, 0);
    if (ret < 0)
    {
        perror("recv fail");
    }
    sem_wait(&socket_sem);

    return ret;
}

int sock_send(int fd, void *buffer, size_t buffer_size)
{
    int ret = 0;

    sem_post(&socket_sem);
    ret = send(fd, buffer, buffer_size, 0);
    if (ret < 0)
    {
        perror("recv fail");
    }
    sem_wait(&socket_sem);

    return ret;
}