/*!
 * \file	common.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-13 19:49:36
 */

#include "common.h"
#include "sysInfo.h"
#include "userManager.h"
#include "fileManager.h"
#include <sys/stat.h>
#include <pthread.h>

typedef struct pthread_struct{
    pthread_t tid1;
    pthread_t tid2;
}pthreadStruct;


/*!
 * \brief recv_msg为一个线程，用于用户发送的信息的接收
 *
 * \param arg
 *
 * \return 
 */
void *recv_msg(void* arg)
{
	char   buf[1024]        = "";
	struct sockaddr_in      addr;
	addr.sin_family         = AF_INET;
	int    addr_len         = sizeof(addr);
	int    udp_fd           = get_udp_fd();  /*获取UDP套接字的文件描述符*/
	int    i                = 0;
	char   *temp[20]        = {NULL};

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

	while(1)
	{
        pthread_testcancel();
		char *fileopt = NULL;
		recvfrom(udp_fd, buf, sizeof(buf), 0, (struct sockaddr*)&addr, &addr_len);
		fileopt = buf+strlen(buf)+1;
		i = 0;

		temp[i++] = strtok(buf, ":");
		while((temp[i++]=strtok(NULL,":"))!=NULL);

		switch(GET_MODE(atoi(temp[4])))
		{
			case IPMSG_BR_ENTRY:
				add_usr(temp[2], temp[3], inet_ntoa(addr.sin_addr));
				sprintf(buf, "1:%d:%s:%s:%d:%s", time(NULL), user(), host(), IPMSG_ANSENTRY, user());
				sendto(udp_fd, buf, strlen(buf),0,(struct sockaddr*)&addr,sizeof(addr));
				break;
			case IPMSG_BR_EXIT:
				del_usr(inet_ntoa(addr.sin_addr));
				break;
			case IPMSG_ANSENTRY:
				add_usr(temp[2],temp[3],inet_ntoa(addr.sin_addr));	
				break;
			case IPMSG_SENDMSG:
				if(temp[5] != NULL)
				{
					printf("\r[%13s]:%s\n",inet_ntoa(addr.sin_addr),temp[5]);
					printf("MY_IPMSG>>");
					fflush(stdout);
				}			
				if(atoi(temp[4])&IPMSG_SENDCHECKOPT)
				{
					char buf[200]="";
					sprintf(buf, "1:%d:%s:%s:%d:%s", time(NULL), user(), host(), IPMSG_RECVMSG, user());
					sendto(udp_fd, buf, strlen(buf),0,(struct sockaddr*)&addr,sizeof(addr));					
				}
				if(atoi(temp[4])&IPMSG_FILEATTACHOPT)
				{
					printf("\rrecv file!\n");
					printf("MY_IPMSG>>");
					fflush(stdout);
					add_file(temp[1], fileopt, addr);
				}
				break;
			default:
				break;
		}
	}
	return NULL;
}

/*!
 * \brief 发送聊天的消息
 *
 * \param argv[]
 */
void send_msg(char*argv[])
{
	int       uid;
	IPMSG_USE *usr;
	char      buf[1024]     = "";
	int       sockfd        = get_udp_fd();
	struct sockaddr_in addr = {AF_INET};
	if(argv[1]==NULL)
	{
		user_list();
		printf("please select a user:");
		scanf("%d",&uid);
		getchar();
	}	
	else 
		uid = atoi(argv[1]);
	usr = find_user_byid(uid);
	addr.sin_port=htons(2425);
	addr.sin_addr.s_addr = inet_addr(usr->usr_ip);
	sprintf(buf, "1:%d:%s:%s:%d:", time(NULL),user(),host(),IPMSG_SENDMSG|IPMSG_SENDCHECKOPT);
	if(argv[2]==NULL)
	{
		printf("say to %s[%s]:",usr->usr_name, usr->usr_ip);
		fflush(stdout);
		fgets(buf+strlen(buf), sizeof(buf), stdin);
		buf[strlen(buf)-1]='\0';
	}
	else 
	{
		strcat(buf,argv[2]);
	}
	sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&addr, sizeof(addr));
}


/*!
 * \brief 将文件的相关check信息发送过去
 *
 * \param argv[]
 */
void sendfile(char* argv[])
{
	int       uid;
	IPMSG_USE *usr;
	char      filename[20]     = "";
	char      buf[1024]        = "";
	int       sockfd           = get_udp_fd();
	struct    stat             fstat;
	struct    sockaddr_in addr = {AF_INET};
    /*提示用户输入选择操作的用户和要发送的文件*/
	if(argv[1] == NULL)
	{
		user_list();
		printf("please select a user:");
		scanf("%d",&uid);
		getchar();
	}	
	else 
		uid = atoi(argv[1]);
	usr = find_user_byid(uid);
	addr.sin_port=htons(2425);
	addr.sin_addr.s_addr = inet_addr(usr->usr_ip);
	if(argv[2] == NULL)
	{
		printf("input filename to %s[%s]:", usr->usr_name, usr->usr_ip);
		fflush(stdout);
		fgets(filename, sizeof(filename), stdin);
		filename[strlen(filename)-1]='\0';
	}
	else 
	{
		strcpy(filename,argv[2]);
	}

	stat(filename, &fstat);
	strcpy(sfile.name,filename);
	time_t t = time(&t);
	sprintf(sfile.packno,"%x", t);
	strcpy(sfile.fino,"0");
	sfile.size = fstat.st_size;

	sprintf(buf, "1:%d:%s:%s:%d:%c", t, user(), host(), IPMSG_SENDMSG | IPMSG_SENDCHECKOPT | IPMSG_FILEATTACHOPT, 0);
	sprintf(buf+strlen(buf)+1,"0:%s:%x:%x", filename, fstat.st_size, fstat.st_ctime);
	sendto(sockfd, buf, strlen(buf)+strlen(buf+strlen(buf)+1), 0, (struct sockaddr*)&addr, sizeof(addr));
}
