/*!
 * \file	fileManager.h
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-13 19:49:36
 */

#ifndef  _FILE_MANNAGER_H_
#define  _FILE_MANNAGER_H_
#include <netinet/in.h>
#include <arpa/inet.h>

/*用于保存所传输的文件的信息的结构体--会形成一个链表*/
typedef struct file_info {
	char packno[20];
	char fino[5];
	char name[20];
	unsigned size;
	struct sockaddr_in addr;
	struct file_info *next;
}FILE_INFO,*PFILE_INFO;

extern FILE_INFO sfile;

void add_file(char *packno, char *fileopt, struct sockaddr_in addr);
void file_list(void);
void *send_file_thread(void *arg);


#endif   //_FILE_MANNAGER_H_
