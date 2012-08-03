/*!
 * \file	sysInfo.h
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-13 19:49:36
 */

#ifndef  _SYS_INFO_H_
#define  _SYS_INFO_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void sys_init(char *user, char *host);
int get_tcp_fd(void);
int get_udp_fd(void);
char * user(void);
char * host(void);

#endif   //_SYS_INFO_H_
