/*!
 * \file	fileManager.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-13 19:16:13
 */

#include "fileManager.h"
#include <fcntl.h>
#include "IPMSG.H"
#include "sysInfo.h"
#include <string.h>
#include <pthread.h>

FILE_INFO file;

FILE_INFO sfile;

/*!
 * \brief 将所传输的文件信息数据写入到链表中
 *
 * \param packno
 * \param fileopt
 * \param addr
 */
void add_file(char *packno, char *fileopt, struct sockaddr_in addr)
{
	char *temp[10] = {NULL};
	char hex[20]   = "";
	int  i         = 0;

	temp[i++] = strtok(fileopt,":");
	while((temp[i++] = strtok(NULL,":"))!=NULL);
	
	sscanf(temp[2], "%x", &(file.size));
	sprintf(hex, "%x", atoi(packno));
	strcpy(file.packno, hex);
	strcpy(file.fino, temp[0]);
	strcpy(file.name, temp[1]);
	file.addr = addr;
}

void file_list(void)
{
	printf("name:%s   [%s]\n",file.name, inet_ntoa(file.addr.sin_addr));	
}

/*!
 * \brief 接收文件
 */
void recv_file(void)
{
	char buf[1024] = "";
	int  sockfd    = 0;
	unsigned int filesize = file.size;

    /*向对方套接字发出连接*/
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0)
	{
		perror("recv file socket");
		exit(1);
	}
	if(connect(sockfd, (struct sockaddr*)&(file.addr), sizeof(struct sockaddr))!=0)
	{
		perror("connect");
		exit(1);
	}
	sprintf(buf, "1:%d:%s:%s:%d:%s:%s:0",time(NULL),user(),host(),IPMSG_GETFILEDATA,file.packno, file.fino);
	send(sockfd, buf, strlen(buf), 0);

    /*按照check信息建立相同文件名的文件*/
	int fd;
	if((fd=open(file.name,O_RDWR|O_CREAT,0666))<0)
	{
		perror("open");
		exit(1);
	}

    /*利用一个while循环来接收数据*/
	while(filesize!=0)
	{
		int len = recv(sockfd, buf,sizeof(buf),0);
		write(fd, buf, len);
		filesize -= len;
	}

    /*关闭对应的文件描述符*/
	close(fd);
	close(sockfd);
}

/*!
 * \brief 通过这个函数来发送数据
 *
 * \param arg
 *
 * \return 
 */
void *send_file_thread(void *arg)
{
	int tcp_fd = get_tcp_fd();  /*获取TCP套接字的文件描述符*/

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    /*此程序是一个单独的线程，所以使用一个while循环让程序停留在此处*/
	while(1)
	{
        pthread_testcancel();
		int    cfd              = 0;
		struct sockaddr_in addr = {AF_INET};
		int    addrlen          = sizeof(addr);
		char   buf[1024]        = "";
		int    fd = 0;

        /*调用accept时，程序会阻塞到直到某个客户端程序发出了连接*/
		if((cfd = accept(tcp_fd, (struct sockaddr*)&addr, &addrlen)) < 0)
		{
			perror("accpet");
			exit(1);
		}

		recv(cfd, buf, sizeof(buf),0);
	
        /*以只读的形式打开所要发送的文件*/        
		if((fd = open(sfile.name, O_RDONLY)) < 0)
		{
			perror("open sendfile");
			exit(1);
		}
        
        /*利用一个while循环来发送数据*/
		while(sfile.size != 0)
		{
			int len = read(fd, buf, sizeof(buf));
			send(cfd, buf, len,0);
			sfile.size -= len;
		}
		close(cfd);
		close(fd);
	}
    return NULL;
}

