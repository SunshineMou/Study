/*!
 * \file	userManager.h
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-13 19:49:36
 */
#ifndef  _USER_MANNAGER_H_
#define  _USER_MANNAGER_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct usr_date
{
	char usr_name[20];
	char host_name[20];
	char usr_ip[20];
	struct usr_date *next;
}IPMSG_USE;

IPMSG_USE *find_user_byid(int id);
IPMSG_USE *add_usr(char *usr,char *host,char *ip);
IPMSG_USE *del_usr(char *ip);
void usr_list(void);


#endif   //_USER_MANNAGER_H_
