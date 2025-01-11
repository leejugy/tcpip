#include "tcp.h"
#include "pthread.h"

void thread_client()
{
    char *send_name = "hellow world!\0";
    char recv_buffer[128] = {
        0,
    };
    int fd = 0;
    int ret = 0;
    STEP step = STEP1;

    while (1)
    {
        switch (step)
        {
        case STEP1:
            fd = init_client(TCP_PORT, TCP_SERVER_IP);
            if (fd < 0)
            {
                printr("fail to connect server");
                sleep(1);
            }
            else
            {
                step = STEP2;
            }
            break;
        case STEP2:
            memset(recv_buffer, 0, sizeof(recv_buffer));

            ret = sock_send(fd, send_name, strlen(send_name));
            if(ret < 0)
            {
                printr("fail to send");
                step = STEP1;
                break;
            }

            ret = sock_recv(fd, recv_buffer, sizeof(recv_buffer));
            if(ret < 0)
            {
                printr("fail to recv");
                step = STEP1;
                break;
            }

            printg("client recv : %s", recv_buffer);

            sleep(5);
            break;

        default:
            break;
        }
    }
}

void start_client_thread()
{
    pthread_t pid = 0;
    int ret = pthread_create(&pid, NULL, (void *)&thread_client, NULL);
    if (ret < 0)
    {
        perror("fail to creat client");
        return;
    }

    ret = pthread_detach(pid);
    if (ret < 0)
    {
        perror("fail to detach client");
        return;
    }
}

int main()
{
    start_client_thread();
    while (1)
    {
        sleep(5000);
    }
}