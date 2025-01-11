#include "tcp.h"
#include "pthread.h"

void thread_client()
{
    char *send_name = "hellow world!\0";
    char recv_buffer[128] = {0, };
    int fd = 0;

    fd = init_client(TCP_PORT, TCP_LOCAL_ADDRESS);

    while(1)
    {
        memset(recv_buffer, 0, sizeof(recv_buffer));

        sock_send(fd, send_name, strlen(send_name));
        sock_recv(fd, recv_buffer, sizeof(recv_buffer));

        printg("client recv : %s", recv_buffer);

        sleep(5);
    }
}

void start_client_thread()
{
    pthread_t pid = 0;
    int ret = pthread_create(&pid, NULL, (void *)&thread_client, NULL);
    if(ret < 0)
    {
        perror("fail to creat client");
        return;
    }

    ret = pthread_detach(pid);
    if(ret < 0)
    {
        perror("fail to detach client");
        return;
    }
}

int main()
{
    start_client_thread();
    while(1)
    {
        sleep(5000);
    }
}