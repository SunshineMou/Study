/*!
 * \file	fd_socket_parent.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-08-03 09:52:37
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <sys/un.h>

#define CONTROLLEN CMSG_LEN(sizeof(int))
#define SLEEPTIME  3
#define ARGLEN     20
#define MODE       S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH    /* -rw-rw-rw- : 110110110 -> 0x1B6 -> 438*/
#define PERMIT     O_RDWR | O_APPEND | O_CREAT                                  /* if the file not exit ,creat it , data written to it append */

int func_send_fd(int send_sock, int send_fd, void *data, int bytes){
    struct  msghdr msg;
    static  struct cmsghdr *cmptr = NULL;
    struct  iovec  passdata[1];
    int     ret;

    /*填充msghead结构*/
    msg.msg_name     = NULL;
    msg.msg_namelen  = 0;
    passdata[0].iov_base = data;
    passdata[0].iov_len  = bytes;
    msg.msg_iov      = passdata;
    msg.msg_iovlen   = 1;

    /*if(send_fd <0){*/
        /*msg.msg_control    = NULL;*/
        /*msg.msg_controllen = 0;*/
    /*}*/
    /*else{*/
        if(cmptr == NULL && (cmptr = malloc(CONTROLLEN)) == NULL)
            return (-1);
        cmptr -> cmsg_level = SOL_SOCKET;
        cmptr -> cmsg_type  = SCM_RIGHTS;
        cmptr -> cmsg_len   = CONTROLLEN;
        msg.msg_control     = cmptr;
        msg.msg_controllen  = CONTROLLEN;
        *(int *)CMSG_DATA(cmptr) = send_fd;
    /*}*/
    if(sendmsg(send_sock, &msg, 0) <= 0)
        return (-1);
    close(send_sock);
    return 0;
}
int func_recv_fd(int recv_sock, int *recvfd, void *data, int bytes){
    struct msghdr msg;
    struct iovec  passdata[1];
    int    ret;

    static struct cmsghdr *cmptr = NULL;

    memset(&msg, 0, sizeof(msg));

    /*同func_send_fd,填充所需要的结构*/
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    passdata[0].iov_base = data;
    passdata[0].iov_len  = bytes;
    
    msg.msg_iov          = passdata;
    msg.msg_iovlen       = 1;

    if(cmptr == NULL && (cmptr = malloc(CONTROLLEN)) == NULL)  /*在&&操作中，在第一个条件为真，会继续判定下一个条件；第一个为假的话，后面不需在执行*/
        return (-1);

    msg.msg_control     = cmptr;
    msg.msg_controllen  = CONTROLLEN;
    
    if((ret = recvmsg(recv_sock, &msg, 0)) < 0){
        printf("In func_recv_fd, recvmsg failed.\n");
        return -1;
    }

    *recvfd = *(int *)CMSG_DATA(cmptr);
    /*printf("The received fd is: %d\n", *recvfd);*/
    /*printf("The received data is: %s\n", (char *)passdata[0].iov_base);*/
    close(recv_sock);
    return (0);
}

int main(int argc, char* argv[])
{
    int     status, sockfd[2];
    char    permit[ARGLEN];
    char    mode[ARGLEN];
    char    argsockfd[ARGLEN];
    int     recvfd;
    char    data[10];
    int     bytes;
    int     ret, i;
    ssize_t size;        /*表示可以被执行读写操作的数据块的大小*/
    int     buflen;
    pid_t   pid,childpid;

    /*以下几行是使用域套接字必要变量*/
    int     fdsock, fdaccept;
    struct  sockaddr_un  addr_server;
    int     len;
    const   char  path[] = "xiaodong";

    /*以下是父进程写入文件的内容*/
    char    buf[] = "Parent process write  data.\n";

    /*父进程同时向client发送的数据*/
    char    datasend[] = "Send by myopen";

    memset(permit, '0', sizeof(permit));
    memset(mode, '0', sizeof(mode));
    memset(argsockfd, '0', sizeof(argsockfd));
    memset(data, '0', sizeof(data));

    printf("Now it's parent process, now will fork a child process.\n");
    sleep(SLEEPTIME);

    /*==========设置文件权限和打开模式==========*/
    snprintf(permit, sizeof(permit), "%d", PERMIT);   /* %d:为什么要以这个形式？*/
    snprintf(mode, sizeof(mode), "%d", MODE);

    /*printf("The permit is: %s\n",permit);*/
    /*printf("The mode is: %s\n",mode);*/
    /*printf("The permit is: %d\n",atoi(permit));*/
    /*printf("The mode is: %d\n",atoi(mode));*/

    /*建立和子进程通信的socket套接字管道*/
    ret = socketpair(AF_UNIX, SOCK_STREAM, 0, sockfd);
    if(ret < 0)
        printf("Craet socket failed, errno is %d\n", errno);

    /*fork 子进程*/
    if((childpid = fork()) == 0){
        printf("Now it's child process, sendsock is: %d\n", sockfd[1]);
        close(sockfd[0]);
        snprintf(argsockfd, sizeof(argsockfd), "%d", sockfd[1]);
        
        /*子进程中执行新程序openfile*/
        execl("./openfile", "openfile", permit, mode, argsockfd, (char *)NULL);
        printf("Execl failed, permit is %s, mode is %s\n", permit, mode);
        exit(-1);       
    }

    pid = wait(&status);
    if((status = WEXITSTATUS(status)) == 0)
        printf("Child %d process terminate, now parent will write file...\n", pid);

    /*从子进程取得文件描述符*/
    recvfd = -1;
    printf("recieve sock is: %d\n", sockfd[0]);
    bytes = sizeof(data);
    printf("bytes:%d\n",bytes);
    ret = func_recv_fd(sockfd[0], &recvfd, data, bytes);
    if(ret < 0){
        printf("Parent recv failed.\n");
        exit(-1);
    }
    else
        printf("fd: %d, parent recv %d bytes data is: %s\n", recvfd, strlen(data), data);
    
    /*父进程向子进程传递的文件描述符中写入数据*/
    size = -1;
    buflen = strlen(buf) - 1;

    if((size = write(recvfd, buf, buflen)) <= 0)
        printf("In openfileprog, write failed.\n");
    
    /*父进程作为server建立套接字，等待client连接*/
    printf("Parent write over! Accept other process......\n");

    fdsock = socket(AF_UNIX, SOCK_STREAM, 0);
    printf("Parent socket fd is: %d\n", fdsock);
    if(fdsock == -1)
        printf("myopen creat socket error! errno is: %d\n",errno);

    unlink(path); /*防止它已经存在导致错误*/

    memset(&addr_server, 0, sizeof(addr_server));
    addr_server.sun_family = AF_UNIX;
    strcpy(addr_server.sun_path, path);
    /*len = offsetof(struct sockaddr_un, sun_path) + strlen(path);*/
    len = sizeof(addr_server);

    ret = bind(fdsock, (struct sockaddr *)&addr_server, len);
    if(ret == -1){
        printf("In myopen bind error, errno is: %s\n", strerror(errno));
        close(fdsock);
        unlink(path);
        exit(0);
    }
    
   /*printf("The fdsock is:%d\n", fdsock); */
    /* listen: error */
    ret = listen(fdsock, 1);
    if(ret = -1){
        printf("In myopen listen error, errno is: %s\n", strerror(errno));
        close(fdsock);
        unlink(path);
        exit(0);
    }

    fdaccept = accept(fdsock, (struct sockaddr *)&addr_server, &len);
    if(fdaccept == -1){
        printf("In myopen accept error, errno is: %s\n", strerror(errno));
        close(fdsock);
        unlink(path);
        exit(0);
    }

    /*向已经连接的client传递文件描述符*/
    ret = func_send_fd(fdaccept, recvfd, datasend, sizeof(datasend));
    if(ret <0)
        printf("in myopen, func_send_fd() failed.\n");
    close(recvfd);
    printf("Send fd over! Will sleep 10s.\n");
    sleep(10);
    exit(0);
}

