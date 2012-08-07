/*!
 * \file	pthread_private.c
 * \brief   实现线程的私有数据	
 * \author	SunshineMou
 * contact  qingtianmou@gmail.com
 * \version	0.00
 * \date	12-02-22 15:20:22
 */
#include <stdio.h>
#include <pthread.h>

pthread_key_t   key;

void echomsg(void *t)
{
    printf("destructor excuted in thread %ld,param=%ld\n", pthread_self(), \
            (unsigned long)t);
}

void * child1(void *arg)
{
    pthread_t tid = pthread_self();
    printf("thread %ld enter\n", tid);
    pthread_setspecific(key,(void *)tid);
    sleep(2);
    printf("thread %ld returns %ld\n", tid, (unsigned long)pthread_getspecific(key));
    sleep(5);
}

void * child2(void *arg)
{
    pthread_t tid = pthread_self();
    printf("thread %ld enter\n", tid);
    pthread_setspecific(key,(void *)tid);
    sleep(1);
    printf("thread %ld returns %ld\n", tid, (unsigned long)pthread_getspecific(key));
    sleep(5);
}

int main(void)
{
    pthread_t tid1,tid2;
    printf("hello\n");
    pthread_key_create(&key, echomsg);
    pthread_create(&tid1, NULL, child1, NULL);
    pthread_create(&tid2, NULL, child2, NULL);
    sleep(10);
    pthread_key_delete(key);
    printf("main thread exit\n");
    return 0;
}
