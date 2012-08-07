/*!
 * \file	pthread_queue.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-11-25 15:45:54
 */
#include <stdio.h>
#include <pthread.h>
#include <errno.h>

pthread_t p_id_1;
pthread_t p_id_2;

void printids(const char *s)
{
    pid_t       pid;
    pthread_t   tid;

    pid = getpid();
    tid = pthread_self();
    printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid,
            (unsigned int)tid, (unsigned int)tid);
}

void *pthread_1(void *arg)
{
    printids("new thread: ");
    return((void *)0);
}

int main(void)
{
    int     err;

    err = pthread_create(&p_id_1, NULL, pthread_1, NULL);
    if (err != 0){
        fprintf(stderr, "can't create thread: %d\n", strerror(errno));
        return -1;
    }
    printids("main thread:");
    sleep(1);
    return 0;
}
