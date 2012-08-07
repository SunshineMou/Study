/*!
 * \file	zombie.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-07 14:24:03
 */

#include "apue.h"
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    pid_t  pid;
    if((pid = fork()) < 0){
        printf("Fork Error:%s\n", strerror(errno));
    }
    if(pid == 0){
        int i;
        exit(0);
    }
    else{
        sleep(2);
        exit(0);
    }     
}

