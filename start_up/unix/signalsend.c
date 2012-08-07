/*!
 * \file	signalsend.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-08-12 10:41:00
 */

#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    pid_t  pid;
    int    signum;
    union  sigval  mysigval;
    signum = atoi(argv[1]);
    pid    = (pid_t)atoi(argv[2]);
    mysigval.sival_int = 8;
    if(sigqueue(pid, signum, mysigval) == -1)
        printf("Send error!\n")
    sleep(2);
    exit(0);
}

