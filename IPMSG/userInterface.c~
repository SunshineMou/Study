/*!
 * \file	userInterface.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-13 19:00:59
 */

#include "userInterface.h"
#include "userManager.h"
#include "sysInfo.h"
#include <sys/wait.h>
#include <pthread.h>
#include "common.h"

/*!
 * \brief 与用户进行交互的应用程序接口
 *
 * \param arg
 *
 * \return 
 */
void * user_interface(void* arg)
{
	char buf[200]="";
    memset(buf, " ", sizeof(buf));

	while(1)
	{
		char *temp[10] = {NULL};
		int i = 0;
		printf("MY_IPMSG>>");
		fgets(buf, sizeof(buf), stdin);
        if(strlen(buf) == 1)
            continue;

		buf[strlen(buf)-1] = '\0';   /*输入的字符串的结尾有一个回车---> "/t" */
		temp[i++] = strtok(buf," ");
		while((temp[i++] = strtok(NULL," ")) != NULL);
		
		if(strcmp(temp[0],"list")==0){
			printf("user list\n");
			user_list();
		}
		else if(strcmp(temp[0], "exit")==0){
			close(get_tcp_fd);
			close(get_udp_fd);
			printf("BYEBYE!\n");	
			pthread_exit((void *)1);
		}
		else if(strcmp(temp[0], "getfile")==0){
			recv_file();	
		}
		else if(strcmp(temp[0],"filelist")==0){
			file_list();
		}
		else if(strcmp(temp[0],"sendfile")==0){
			sendfile(temp);
		}
		else if(strcmp(temp[0], "ls")==0){
			pid_t pid = 0;
			if((pid=fork()) == 0)
			{
				execlp("ls", "ls", NULL);
			}
			waitpid(pid,NULL,WUNTRACED);
		}
		else if(strcmp(temp[0], "say")==0){
			send_msg(temp);
		}
        else{
			printf("The input is empty!!");
		}
	}
	return NULL;
}

