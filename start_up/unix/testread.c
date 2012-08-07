/*!
 * \file	testread.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-08-05 16:29:40
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
 * \brief      练习 系统V共享存储实例
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
    /*shmat:将共享存储段链接到它的地址空间中*/
    p_map = (people *)shmat(shm_id, NULL, 0);
    
    for(i=0; i<10; i++){
        printf("name: %s\n", (*(p_map + i)).name);
        printf("age : %d\n", (*(p_map + i)).age);
    } 
    if(shmdt(p_map) == -1){
        printf("detach error!\n");
        exit(0);
    }
    exit(0);
}

