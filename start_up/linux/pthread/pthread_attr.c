/*!
 * \file	pthread_attr.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-11-29 16:34:49
 */
#include <stdio.h>
#include <pthread.h>

void *func(void *attr);

int main(int argc, char* argv[])
{
    pthread_attr_t attr;
    pthread_t      tid;

    if(pthread_attr_init(&attr) != 0){
        printf("Init Error!\n");
        return 0;
    }

    if(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0){
        printf("Set attr Error!\n");
        return 0; 
    }

    pthread_create(&tid, &attr, func, (void *)&attr);

    if(pthread_attr_destroy(&attr) != 0){
        printf("Destroy Error!\n");
        return 0;
    }
     
    sleep(5);

    return 0;
}

void *func(void *attr){
    int a1;
    printf("address of a1: %p\n", &a1);
    size_t         size;
    void           *address;
    if(pthread_attr_getstack((pthread_attr_t *)attr, &address, &size) != 0){
        printf("Get attr Error!\n");
        return 0;
    }
    printf("The address of the stack is:%p\n", address);
    printf("The size of the stack is:%zu\n", size);
    pthread_exit((void *)0);

    char buf[4096];
    FILE *fp = fopen("/proc/self/maps", "r");
    while (fgets(buf, sizeof(buf), fp))
        fprintf(stderr, "%s", buf);
}
