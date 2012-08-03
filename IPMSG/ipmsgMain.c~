/*!
 * \file	ipmsgMain.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-13 18:58:39
 */

#include "sysInfo.h"
#include "userManager.h"
#include "userInterface.h"
#include "fileManager.h"
#include "common.h"
#include <pthread.h>

int main(int argc, char* argv[])
{
	pthread_t r_tid;
	pthread_t ui_tid;
	pthread_t sf_tid;

	sys_init("Sunshine", "XiaodongMou");

	pthread_create(&r_tid,  NULL, recv_msg,         NULL);
	pthread_create(&ui_tid, NULL, user_interface,   NULL);
	pthread_create(&sf_tid, NULL, send_file_thread, NULL);
    pthread_join(ui_tid, NULL);
    printf("Pthread --ui_tid-- stop normally!\n");
    pthread_cancel(r_tid);
    pthread_join(r_tid,  NULL);
    pthread_cancel(sf_tid);
    printf("Pthread --r_tid-- stop normally!\n"); 
	pthread_join(sf_tid, NULL); 
    printf("Pthread --sf_tid-- stop normally!\n"); 
    
    printf("The process is exit normally!\n");    
	return 0;
}

