#include "tcp.h"
#include "pthread.h"

void thread_server()
{
    char *send_name = "we receive hellow world!\0";
    char recv_buffer[128] = {
        0,
    };
    int socket_fd = 0;
    int client_fd = 0;
    int ret = 0;
    STEP step = STEP1;

    init_server(TCP_PORT, &socket_fd);

    while (1)
    {
        switch (step)
        {
        case STEP1:
            client_fd = accept_server(socket_fd);
            if (client_fd < 0)
            {
                printr("fail to accept");
            }
            else
            {
                step = STEP2;
            }
            break;

        case STEP2:
            memset(recv_buffer, 0, sizeof(recv_buffer));

            ret = sock_recv(client_fd, recv_buffer, sizeof(recv_buffer));
            if(ret < 0)
            {
                printr("fail to recv");
                step = STEP1;
                break;
            }

            printg("server recv : %s", recv_buffer);
            if (!strcmp(recv_buffer, "hellow world!\0"))
            {
                ret = sock_send(client_fd, send_name, strlen(send_name));
                if(ret < 0)
                {
                    printr("fail to send");
                    step = STEP1;
                    break;
                }
            }

            sleep(5);
            break;

        default:
            break;
        }
    }
}

void start_server_thread()
{
    pthread_t pid = 0;
    int ret = pthread_create(&pid, NULL, (void *)&thread_server, NULL);
    if (ret < 0)
    {
        perror("fail to creat server");
        return;
    }

    ret = pthread_detach(pid);
    if (ret < 0)
    {
        perror("fail to detach server");
        return;
    }
}

int main()
{
    start_server_thread();
    while (1)
    {
        sleep(5000);
    }
}