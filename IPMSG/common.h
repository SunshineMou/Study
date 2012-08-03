/*!
 * \file	userManager.h
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-13 19:49:36
 */

#ifndef  _COMM_H_
#define  _COMM_H_

#include "IPMSG.H"


void *recv_msg(void* arg);
void send_msg(char*argv[]);
void sendfile(char *argv[]);

#endif   //_COMM_H_
