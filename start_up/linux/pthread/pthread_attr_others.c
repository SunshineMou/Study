/*!
 * \file	pthread_attr_others.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-11-29 17:03:39
 */

#include <stdio.h>
#define _GNU_SOURCE
#include <pthread.h>
#include <unistd.h>

static void get_stack(void **stack_addr, size_t *stack_size)
{
    pthread_attr_t attr;
    pthread_getattr_np(pthread_self(), &attr);
    pthread_attr_getstack(&attr, stack_addr, stack_size);
    pthread_attr_destroy(&attr);
}

void *func(void *attr){
    int a1;
    printf("address of a1: %p\n", &a1);
    pthread_exit((void *)0);
}

void *func_1(void *attr){
    int a1;
    printf("address of a1: %p\n", &a1);
    pthread_exit((void *)0);
}

void *func_2(void *attr){
    int a1;
    printf("address of a1: %p\n", &a1);
    pthread_exit((void *)0);
}

int main()
{
    int a1;
    void *stack_addr;
    size_t stack_size;
    pthread_t      tid;
    pthread_t      tid_1;
    pthread_t      tid_2;

    printf("The pthread id is:%d\n", getpid());
    printf("address of a1: %p\n", &a1);
    get_stack(&stack_addr, &stack_size);
    printf("stack start: %p, size: %zu\n", stack_addr, stack_size);
    int a2;
    printf("address of a2: %p\n", &a2);

    pthread_create(&tid, NULL, func, NULL);
    pthread_create(&tid_1, NULL, func_1, NULL);
    pthread_create(&tid_2, NULL, func_2, NULL);

    puts("\n==============================================\n");
    char buf[4096];
    FILE *fp = fopen("/proc/self/maps", "r");
    while (fgets(buf, sizeof(buf), fp))
        printf("%s", buf);
    fclose(fp);

    sleep(2);
    return 0;
}
