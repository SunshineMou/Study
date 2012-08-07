/*!
 * \file	testwrite.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-08-05 16:02:50
 */

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct {
    char name[4];
    int  age;
}people;

/*!
 * \brief      练习系统V 共享内存范例  ---现在需要以root权限来执行才可以，否则会发生shmat函数错误
 *
 * \param argc
 * \param argv[]
 *
 * \return 
 */
int main(int argc, char* argv[])
{
    int     shm_id, i;
    key_t   key;    /*System V IPC 使用key_t作为它们的名字*/
    char    temp;
    people  *p_map;
    char *  name  =  "/tmp/test_shm";
    
    /*ftok把一个以存在的路径名和一个整数标识转换成一个key_t值，成为IPC键*/
    key = ftok(name, 0);
    if(key == -1){
        printf("ftok error!\n");
        /*exit(0);*/
    }
    /*取得一个共享存储段的标识符，也就是创建一个共享存储段*/
    shm_id = shmget(key, 4096, IPC_CREAT);
    if(shm_id == -1){
        printf("shmget error!\n");
        exit(0);
    }

    printf("shmid共享内存分配成功，共享内存识别代号为：%d。\n",shm_id);

    /*shmat:将共享存储段链接到它的地址空间中*/
    p_map = (people *)shmat(shm_id, NULL, 0);
    printf("Here\n");
    temp = 'a';
    for(i=0; i<10; i++){
        temp += 1;
        memcpy((*(p_map)).name, &temp, 1);
        (*(p_map)).age = 20 + i;
    }
    /*解除共享存储段与地址空间的链接，注意：这并不意味着从系统中删除共享存储段的标识符及其数据结构*/
    if(shmdt(p_map) == -1){
        printf("detach error!\n");
        exit(0);
    }
    exit(0);
}

