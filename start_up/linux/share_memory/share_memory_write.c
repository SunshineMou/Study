/*!
 * \file	share_memory_write.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-12-23 16:25:36
 */
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct{
    char name[4];
    int age;
}people;

main(int argc, char** argv)
{
    int shm_id,i;
    key_t key;
    char temp;
    void *shared_memory;
    people *p_map;

    char* name = "myshm";
    key = ftok(name,0);
    if(key==-1)
        perror("ftok error");

    shm_id=shmget(key, 4096, IPC_CREAT);
    if(shm_id==-1)
    {
        perror("shmget error");
        return;
    }
    shared_memory = shmat(shm_id, NULL, 0);

    p_map = (people *)shared_memory;
    printf("Shared Memory attached from %p to %p!\n", p_map, p_map + 4096);

    temp = 'a';
    for(i=0; i<10; i++)
    {
        temp+=1;
        strncpy((*(p_map+i)).name, &temp, 1);
        printf("Debug!\n");
        (*(p_map+i)).age = 20 + i;
    }

    if(shmdt(p_map)==-1)
        perror(" detach error ");
}
