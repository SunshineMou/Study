/*!
 * \file	semaphore_server.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-12-30 11:21:25
 */
#include <stdio.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/ipc.h>

#define SEGSIZE 1024
#define READTIME 1

union semun {
    int      val;
    struct   semid_ds *buf;
    unsigned short *array;
} arg;

int sem_creat(key_t key)
{
    union semun sem;
    int   semid;
    sem.val = 0;
    semid = semget(key, 1, IPC_CREAT | 0666);
    if (-1 == semid){
        printf("create semaphore error\n");
        return -1;
    }
    semctl(semid, 0, SETVAL, sem); /*Set the value of the members*/
    return semid;
}

void del_sem(int semid)
{
    union semun sem;
    sem.val = 0;
    semctl(semid, 0, IPC_RMID, sem);
}


int p(int semid)
{
    /*The thread release the source which protected by the semaphore!*/
    struct sembuf sops={0, +1, IPC_NOWAIT};
    return (semop(semid, &sops, 1));
}

int v(int semid)
{
    /*The thread get the source which protected by the semaphore!*/
    struct sembuf sops={0, -1, IPC_NOWAIT};
    return (semop(semid, &sops, 1));
}

int main()
{
    key_t  key;
    int    shmid,semid;
    char   *shm;
    char   msg[7] = "-data-";
    char   i;
    struct semid_ds buf;

    key = ftok("my_share_mem", 0);
    shmid = shmget(key, SEGSIZE, IPC_CREAT | 0604);
    if (-1 == shmid){
        printf(" create shared memory error\n");
        return -1;
    }
    shm = (char *)shmat(shmid, 0, 0);
    if (-1 == (int)shm){
        printf(" attach shared memory error\n");
        return -1;
    }

    semid = sem_creat(key);
    for (i = 0;i <= 3;i++){
        sleep(1);
        p(semid);
        sleep(READTIME);
        msg[5] = '0' + i;
        memcpy(shm, msg, sizeof(msg));
        sleep(58);
        v(semid);
    }
    
    shmdt(shm);
    shmctl(shmid, IPC_RMID, &buf);
    del_sem(semid);
    return 0;
}
