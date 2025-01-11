#include "tcp.h"
#include "pthread.h"

void thread_server()
{
    char *send_name = "we receive hellow world!\0";
    char recv_buffer[128] = {0, };
    int socket_fd = 0;
    int client_fd = 0;

    init_server(TCP_PORT, &socket_fd);
    client_fd = accept_server(socket_fd);

    while(1)
    {
        memset(recv_buffer, 0, sizeof(recv_buffer));

        sock_recv(client_fd, recv_buffer, sizeof(recv_buffer));
        printg("server recv : %s", recv_buffer);
        if(!strcmp(recv_buffer, "hellow world!\0"))
        {
            sock_send(client_fd, send_name, strlen(send_name));
        }

        sleep(5);
    }
}

void start_server_thread()
{
    pthread_t pid = 0;
    int ret = pthread_create(&pid, NULL, (void *)&thread_server, NULL);
    if(ret < 0)
    {
        perror("fail to creat server");
        return;
    }

    ret = pthread_detach(pid);
    if(ret < 0)
    {
        perror("fail to detach server");
        return;
    }
}

int main()
{
    start_server_thread();
    while(1)
    {
        sleep(5000);
    }
}