/*!
 * \file	semaphore_client.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-12-30 13:41:00
 */
#include <stdio.h>
#include <string.h>
#include <sys/sem.h>
#include <time.h>
#include <sys/ipc.h>

#define SEGSIZE 1024
#define READTIME 1

union semun {
    int      val;
    struct   semid_ds *buf;
    unsigned short *array;
} arg;

void out_time(void)
{
    static long start = 0;
    time_t tm;
    if (0 == start){
        tm = time(NULL);
        start = (long)tm;
        printf(" now start ...\n");
    }
    printf(" second: %ld \n",(long)(time(NULL)) - start);
}

int new_sem(key_t key)
{
    union semun sem;
    int   semid;
    sem.val = 0;
    semid = semget(key, 0, 0);
    if (-1 ==  semid){
        printf("create semaphore error\n");
        return -1;
    }
    return semid;
}

void wait_v(int semid)
{
    struct sembuf sops={0, 0, 0};
    semop(semid, &sops, 1);
}

int main(void)
{
    key_t key;
    int   shmid,semid;
    char  *shm;
    char  msg[100];
    char  i;

    key = ftok("my_share_mem", 0);
    shmid = shmget(key, SEGSIZE, 0);

    if(-1 == shmid){
        printf(" create shared memory error\n");
        return -1;
    }
    shm = (char *)shmat(shmid, 0, 0);
    if (-1 == (int)shm){
        printf(" attach shared memory error\n");
        return -1;
    }
    semid = new_sem(key);
    for (i = 0; i < 3; i ++){
        sleep(2);
        wait_v(semid);
        printf("Message geted is: %s \n", shm + 1);
        out_time();
    }

    shmdt(shm);
    return 0;
}
