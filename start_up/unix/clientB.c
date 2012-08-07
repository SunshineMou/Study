/*!
 * \file	clientB.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-08-02 10:13:01
 */

#include <stdio.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int    client_sockfd;
    int    len;
    struct sockaddr_un server_sockaddr, cli_sockaddr;
    int    result;
    char   dst_module_id = 'A';
    char   ch = '2';
    char   src_module_id;

    client_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

    cli_sockaddr.sun_family = AF_UNIX;
    strcpy(cli_sockaddr.sun_path, "A");
    bind(client_sockfd, (struct sockaddr *)&cli_sockaddr, sizeof(cli_sockaddr));
    server_sockaddr.sun_family =AF_UNIX;
    strcpy(server_sockaddr.sun_path,"server_socket");
    len = sizeof(server_sockaddr);

    result = connect(client_sockfd, (struct sockaddr *)&server_sockaddr, len);
    if(result < 0){
        printf("ClientB:: error on connecting \n");
        return -1;
    }

    printf("ClientB:: Succeed in connecting with server\n");
    sleep(10);
    write(client_sockfd, &dst_module_id, 1);
    write(client_sockfd, &ch, 1);
    read(client_sockfd, &src_module_id, 1);
    read(client_sockfd, &ch, 1);
    printf("ClentB:: char from Client %c = %c\n", src_module_id, ch); /*将从服务器接收的信息打印出来*/
    close(client_sockfd);
     
    return 0;
}
