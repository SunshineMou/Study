/*!
 * \file	pthread_cancle.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-12-07 08:56:26
 */
#include <stdio.h>
#include <pthread.h>

void *func(void *arg){
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    while(1){
        printf("Waiting for the cancel signal!\n");
        sleep(1);
    }
    pthread_exit((void *)1);
}

int main(int argc, char* argv[])
{
    pthread_t p_id;
    void *tret;

    if(pthread_create(&p_id, NULL, func, NULL) != 0){
        printf("Create pthread error!\n");
        return 0;
    }

    sleep(2);
    pthread_cancel(p_id);
    pthread_join(p_id, &tret);
    /*We can not get the exit code! pthread_exit() had not been carried out!*/
    printf("The created pthread exit code is:%d\n", (int)tret); 
    printf("The create pthread is exit!\n");
    
    while(1){
        sleep(2);
    } 
    return 0;
}

