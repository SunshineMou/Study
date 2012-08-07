/*!
 * \file	qqServer.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-08-19 19:32:39
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

#define  SERVER_PORT    8000
#define  MAX_QUENE      10

void printUsage(){
    printf("Usage: ./qqServer  <IP Address>\n");
}

int main(int argc, char* argv[])
{
    struct  sockaddr_in serverAddr;
    struct  sockaddr_in   dest_addr;
    int     serverfd, newfd, destfd;
    int     ssize;
    pid_t   clientPid;
    int     maxfd, sockfd[2];
    char    buffer[256];
    int     recNum;
    fd_set  catch_fd_set;
    fd_set  watchset;
    int     status;
 
    if(argc<2){       
        printUsage();
        exit(1);
    }

    if(socketpair(AF_UNIX, SOCK_STREAM, 0, sockfd) < 0){
        printf("Socketpair error!\n");
        exit(-1);
    }

    if((clientPid = fork()) == 0){
        /*
         * 此处子进程接收另一个client发送过来的数据，并将对应的数据输出显示;
         *
         * fork的一个特性是父进程的所有打开文件描述符都被复制到子进程中；父子进程
         * 的每个相同的打开描述符共享一个文件表项
         */

        printf("Child-->Now it's child process, sendsock is: %d\n", sockfd[1]);
        close(sockfd[0]);
        serverfd = socket(AF_INET, SOCK_STREAM, 0);
        memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family        = AF_INET;
        serverAddr.sin_port          = htons(SERVER_PORT);
        serverAddr.sin_addr.s_addr   = INADDR_ANY;

        if(bind(serverfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1){
            printf("Child-->Socket bind error:%s\n", strerror(errno));
            exit(-1);
        } 
        printf("Child-->Socket bind success!\n");

        if(listen(serverfd, MAX_QUENE) == -1){
            printf("Child-->Socket listen error: %s\n", strerror(errno));
            exit(-1);
        }
        printf("Child-->Socket listen success!\n");

        ssize = sizeof(struct sockaddr_in);

        /*在没有客户端连接时，accept会一直阻塞*/
        if((newfd = accept(serverfd, (struct sockaddr*)&serverAddr, &ssize)) == -1){
            printf("Child-->Socket accept error: %s\n", strerror(errno));
            exit(-1);
        }
        printf("Child-->Socket accept success!\n");
        
        FD_ZERO( &watchset );
        FD_SET(newfd, &watchset);
        maxfd = newfd;
        FD_SET(sockfd[1], &watchset);
        if(sockfd[1] > maxfd)
            maxfd = sockfd[1];
        while(1){
            catch_fd_set = watchset; /*===*/
            if(select(maxfd+1, &catch_fd_set, NULL, NULL, NULL) == -1){
                printf("Child-->Select error!\n");
                exit(-1);
            }
            if(FD_ISSET(sockfd[1], &catch_fd_set)){
                if((recNum = recv(sockfd[1], &buffer, sizeof(buffer), 0)) == -1) {
                    printf("Child-->Receive Error\n");
                    exit(-1);
                }
                if(strlen(buffer) == 2){
                    if(buffer[0] == 0x40){
                        printf("Child-->Done!\n");
                        exit(0);
                    }
                }
                printf("Child-->Receive(parent):%s, Length:%d\n", buffer, strlen(buffer));
            }
            if(FD_ISSET(newfd, &catch_fd_set)){
                if((recNum = recv(newfd, &buffer, sizeof(buffer), 0)) == -1) {
                    printf("Child-->Receive Error\n");
                    exit(-1);
                }
                /*if(strlen(buffer) == 2){*/
                /*if(buffer[0] == 0x40){*/
                /*printf("Child-->Done!\n");*/
                /*exit(0);*/
                /*}*/
                /*}*/
                printf("Child-->Receive(destination):%s, Length:%d\n", buffer, strlen(buffer));
            }
        }
    }
    else{
        /*
         * 父进程负责获取用户的输入操作，将用户的输入发送给另一个client，
         * 并将用户的输入送据送入子进程，子进程负责父进程输入数据的输出；
         * 连接另一端的套接字，将用户输入的数据发送过去；
         */
        printf("recieve sock is: %d\n", sockfd[0]);
        close(sockfd[1]);
        if((destfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            printf("Creat socket error!: %s\n", strerror(errno));
            exit(1);
        }

        memset(&dest_addr, 0, sizeof(dest_addr));
        dest_addr.sin_family      = AF_INET;
        dest_addr.sin_port        = htons(SERVER_PORT);
        dest_addr.sin_addr.s_addr = inet_addr(argv[1]);

        /*parent的发送程序会将输入时的回车也发送过去*/
        while(1){
            printf("sunshine@:");
            fgets(buffer, 256, stdin);
            printf("The size is:%d, buffer[0] is:%d\n", strlen(buffer), buffer[0]);
            if(strlen(buffer) == 2){
                if(buffer[0] == 0x24){
                    printf("Communication start!\n");
                    if(connect(destfd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
                        printf("Connect error!\n");
                        exit(1);
                    }
                    else{
                        status = 1;
                        continue;
                    }
                }
                if(buffer[0] == 0x40)
                    send(destfd, &buffer, strlen(buffer), 0);
                    if((write(sockfd[0], buffer, sizeof(buffer))) <= 0)
                        printf("Parent-->Child:write failed.\n");
                    if(wait(NULL) == clientPid){
                        printf("Communication over!\n");
                        close(destfd);
                        exit(0); 
                    }
            }
            if(status == 1){
                send(destfd, &buffer, strlen(buffer), 0);
                if((write(sockfd[0], buffer, sizeof(buffer))) <= 0)
                    printf("Parent-->Child:write failed.\n");
            }
            memset(buffer, 0, sizeof(buffer));
        }
    }
}

