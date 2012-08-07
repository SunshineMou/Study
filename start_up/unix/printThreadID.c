/*!
 * \file	printThreadID.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-07-19 11:47:30
 */
#include "apue.h"
#include <pthread.h>

pthread_t ntid;

void printids(const char *s){
    pid_t     pid;
    pthread_t tid;
    pid  = getpid();
    tid  = pthread_self();
    printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid, (unsigned int)tid, (unsigned int)tid);
}
void *thr_fn(void *arg){
    printids("new thread: ");
    return ((void *) 0);
}
int main(int argc, char* argv[])
{
    int err;
    err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if(err != 0){
        err_quit("can not creat thread : %s\n",strerror(err));
    }
    printids("main thread:");
    sleep(1);
    exit(0);
}

