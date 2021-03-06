/*!
 * \file	sysInfo.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-13 19:40:14
 */

#include "sysInfo.h"
#include <time.h>
#include "IPMSG.H"

#define  BroadCastAddress  "255.255.255.255"
#define  ServerPort        2425

static char sys_user[20]="";
static char sys_host[20]="";
int tcp_fd = 0;
int udp_fd = 0;

char * user(void)
{
	return sys_user;
}

char * host(void)
{
	return sys_host;
}

/*!
 * \brief 将用户的一些基本信息通过广播的形式发送出去;
 *
 * \param sockfd
 * \param user
 * \param host
 */
void login(int sockfd,char *user, char *host)
{
	char buf[200]           = "";
	struct sockaddr_in      addr;
	addr.sin_family         = AF_INET;
	/*addr.sin_addr.s_addr    = inet_addr("192.168.220.255");*/
	addr.sin_addr.s_addr    = inet_addr(BroadCastAddress);
    /*addr.sin_port           = htons(2425);*/
    addr.sin_port           = htons(ServerPort);
	sprintf(buf, "1:%d:%s:%s:%d:%s", time(NULL), user, host, IPMSG_BR_ENTRY, user);
	sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&addr, sizeof(addr));
}

/*!
 * \brief 创建一个TCP套接字和一个UDP套接字
 *
 * \param user
 * \param host
 */
void sys_init(char *user, char *host)
{
	struct sockaddr_in addr;
	int br_en = 1;
	
	addr.sin_family      = AF_INET;
	addr.sin_port        = htons(2425);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	strcpy(sys_user, user);		
	strcpy(sys_host, host);		
	
	if((udp_fd = socket(AF_INET, SOCK_DGRAM, 0))<0)
	{
		perror("create udp");
		exit(1);
	}
	if(bind(udp_fd, (struct sockaddr*)&addr, sizeof(addr))!=0)
	{
		perror("bind udp");
		exit(1);
	}
	setsockopt(udp_fd, SOL_SOCKET, SO_BROADCAST, &br_en, sizeof(br_en));

	if((tcp_fd = socket(AF_INET, SOCK_STREAM, 0))<0)
	{
		perror("create udp");
		exit(1);
	}
	if(bind(tcp_fd, (struct sockaddr*)&addr, sizeof(addr))!=0)
	{
		perror("bind tcp");
		exit(1);
	}
	listen(tcp_fd, 10);
	login(udp_fd, user,host);
	return ;
}

int get_tcp_fd(void)
{
	return tcp_fd;
}

int get_udp_fd(void)
{
	return udp_fd;
}

