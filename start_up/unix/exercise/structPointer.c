/*!
 * \file	structPointer.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-19 15:34:34
 */
#include <stdio.h>
#include <semaphore.h>
typedef struct struct_pointer{
    sem_t  semOpts;
    int    test;
}structPointer;

    sem_t sem;
int main(int argc, char* argv[])
{
    structPointer *ptr = (structPointer *)malloc(sizeof(structPointer));
    /*if(sem_init(&(ptr->semOpts), 0, 1)){*/
    if(sem_init(&sem, 0, 1)){
            printf("Error!\n");
            }
    printf("Success!\n");
    
    return 0;
}

