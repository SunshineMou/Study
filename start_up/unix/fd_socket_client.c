/*!
 * \file	fd_socket_client.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-08-03 13:40:56
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/un.h>

#define SLEEPTIME  3
#define ARGLEN     20
#define CONTROLLEN CMSG_LEN(sizeof(int))

int func_recv_fd(int recv_sock, int *recvfd, void *data, int bytes){
    struct msghdr msg;
    struct iovec  passdata[1];
    int    ret;
    int    temp;
    int    newfd;

    struct cmsghdr *cmptr = NULL;

    memset(&msg, 0, sizeof(msg));

    /*同func_send_fd,填充所需要的结构*/
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    passdata[0].iov_base = data;
    passdata[0].iov_len  = bytes;
    
    msg.msg_iov          = passdata;
    msg.msg_iovlen       = 1;

    msg.msg_control     = cmptr;
    msg.msg_controllen  = CONTROLLEN;

    if((ret = recvmsg(recv_sock, &msg, 0)) < 0){
        printf("In func_recv_fd, recvmsg failed.\n");
        return -1;
    }

    recvfd = (int *)CMSG_DATA(cmptr);
    close(recv_sock);
    exit(0);
}

int main(int argc, char* argv[])
{
    int    sockfd, recvfd, ret, length, buflen;
    struct sockaddr_un addr_client;
    char   data[20];
    ssize_t size;
    const   char path[] = "xiaodong";
    char    buf[] = "This is client process.\n";

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sockfd == -1)
        printf("Client creat socket error! errno is: %d\n", errno);
    addr_client.sun_family = AF_UNIX;
    strcpy(addr_client.sun_path, path);
    length = sizeof(addr_client.sun_family) + sizeof(addr_client.sun_path);

    ret = connect(sockfd, (struct sockaddr *)&addr_client, length);
    if(ret == -1){
        printf("In client connect error! errno is: %d\n", errno);
        close(sockfd);
        exit(0);
    }

    ret = func_recv_fd(sockfd, &recvfd, data, sizeof(data));
    if(ret == -1){
        printf("In client func_recv_fd failed! errno is: %d\n", errno);
        close(sockfd);
        exit(0);
    }

    size = -1;
    buflen =sizeof(buf);

    if((size = write(recvfd, buf, buflen)) <= 0)
        printf("In openfileprog, write failed\n");
    printf("Client write over!\n");
    close(sockfd);
    exit(0);
}

