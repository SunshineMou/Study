/*!
 * \file	pthreadTest.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-08-08 14:37:17
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFSIZE  4
#define NUMBER   8

int     sum_of_number = 0;

/*可读和可写的资源数*/
sem_t   write_res_number; /*写信号量*/
sem_t   read_res_number;  /*读信号量*/

/*循环队列*/
struct  recycle_buffer {
    int buffer[BUFSIZE];
    int head, tail;
}re_buf;

/*用于实现临界区的互斥锁，我们对其初始化*/
pthread_mutex_t  buffer_mutex = PTHREAD_MUTEX_INITIALIZER;

static void *producer(void *arg){
    int    i;
    for(i=0; i<=NUMBER; i++){
        /*减少可写的资源数*/
        sem_wait(&write_res_number);   /*无可写资源时，会阻塞直到consumer的for循环增加可写资源数*/

        /*进入互斥区*/
        pthread_mutex_lock(&buffer_mutex);

        /*将数据复制到缓冲区的尾部*/
        re_buf.buffer[re_buf.tail] = i;
        re_buf.tail = (re_buf.tail + 1)%BUFSIZE;
        printf("producer %d write %d.\n", (unsigned int)pthread_self(), i);   /*pthread_self(): 获得线程自身的ID*/

        /*离开互斥区*/
        pthread_mutex_unlock(&buffer_mutex);

        /*增加可读资源数*/
        sem_post(&read_res_number);
    }
    /*线程终止，如果有线程等待它们结束，则把NULL作为其结果的返回值*/
    return NULL;
}

static void *consumer(void *arg) {
    int   i, num;
    for(i=0; i<=NUMBER; i++){
        /*减少可读资源数*/
        sem_wait(&read_res_number);   /*无可读资源时，会阻塞直到producer的for循环增加可读资源数*/

        /*进入互斥区*/
        pthread_mutex_lock(&buffer_mutex);

        /*从缓冲区的头部获取数据*/
        num = re_buf.buffer[re_buf.head];
        re_buf.head = (re_buf.head +1)%BUFSIZE;
        printf("consumer %d read %d.\n", (unsigned int)pthread_self(),num);

        /*离开互斥区*/
        pthread_mutex_unlock(&buffer_mutex);
        sum_of_number += num;

        /*增加可写资源数*/
        sem_post(&write_res_number);
    }
    /*线程终止，如果有线程等待它们结束，则把NULL作为等待结果的返回值*/
    return NULL;
}

int main(int argc, char* argv[])
{
    /*用于保存线程的线程号*/
    pthread_t  p_tid;
    pthread_t  c_tid;
    int        i;

    re_buf.head = 0;
    re_buf.tail = 0;
    for(i=0; i<BUFSIZE; i++)
        re_buf.buffer[i] = 0;

    /*初始化可写资源数为循环队列的单元数*/
    sem_init(&write_res_number, 0, BUFSIZE); /*这里限定了可写的BUFSIZE，当写线程写满buf时，会阻塞，等待读进程读取*/

    /*初始化可读的资源数为0*/
    sem_init(&read_res_number, 0, 0);

    /*创建两个线程，线程函数分别是：producer和consumer*/
    /*这两个线程将使用系统的缺省线程的设置，如线程的堆栈大小，线程的调度策略和相应的优先级*/
    pthread_create(&p_tid, NULL, producer, NULL);
    pthread_create(&c_tid, NULL, consumer, NULL);

    /*等待两个线程完成退出*/
    pthread_join(p_tid, NULL);      /*等待直到指定的线程终止*/
    pthread_join(c_tid, NULL);

    printf("The sun of number is: %d\n", sum_of_number);
    exit(0);
}

