/*!
 * \file	sendFile.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-08-12 11:21:13
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <errno.h>

#define  path  "/tmp/xiaodong"
/*#define SERVERIP "172.17.184.185"*/
#define SERVERPORT 8000

void printUsage(){
    printf("Usage: ./sendFile  <IP Address>  <FileName>");
}


/*!
 * \brief      编写发送端函数，通过socket将一个文件中的内容发送给接收端；
 *
 * \param argc
 * \param argv[]
 *
 * \return 
 */
int main(int argc, char* argv[])
{
    struct sockaddr_in   dest_addr;
    int    sockfd;
    int    retval;
    char   buffer[256];
    FILE   *fp;

    if(argc<3){       
        printUsage();
        exit(1);
    }
    
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Creat socket error!: %s\n", strerror(errno));
        exit(1);
    }

    unlink(path);
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port   = htons(SERVERPORT);
    dest_addr.sin_addr.s_addr = inet_addr(argv[1]);

    /*if(inet_pton(AF_INET, argv[1], &dest_addr.sin_addr) <= 0) {*/
        /*printf("ERROR: inet_pton error for %s\n", argv[1]);*/
        /*exit(1);*/
    /*}*/
    
    if(connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
        printf("Connect error!\n");
        exit(1);
    }

    if((fp = fopen(argv[2], "r")) == NULL){
        printf("Open %s fail!\n", argv[2]);
        exit(1);
    }
    printf("Start transmiting the %s\n", argv[2]);
    while((fgets((char *)buffer, sizeof(buffer), fp)) != NULL){
        printf("Send:%s\n", buffer);
        send(sockfd, &buffer, strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
        sleep(2);
    }
    return 0;
}

