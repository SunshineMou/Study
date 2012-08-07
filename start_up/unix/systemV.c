/*!
 * \file	systemV.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-08-06 10:26:03
 */
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

/*!
 * \brief        父子进程间使用共享内存，----需要以root权限来执行，否则会发生shmat错误
 *
 * \param argc
 * \param argv[]
 *
 * \return 
 */
int main(int argc, char* argv[])
{
    int pid,shmid;//后者为共享内存识别代号
    char *write_address;
    char *read_address;
    struct shmid_ds dsbuf; 

    if((shmid=shmget(IPC_PRIVATE,32,0))<0)//分配共享内存
    {
        printf("shmid共享内存分配出现错误。\n");
        exit(1);
    }
    else
        printf("shmid共享内存分配成功，共享内存识别代号为：%d。\n",shmid);
    if((pid=fork())<0)
    {
        printf("fork函数调用出现错误！\n");
        exit(1);
    }
    else if(pid>0)//父进程，向共享内存中写入数据
    {
        printf("父进程的ID是：%d\n",getpid());
        write_address=(char *)shmat(shmid,NULL,0);//连接共享内存
        if((int)write_address==-1)
        {
            printf("shmat连接共享内存错误。\n");
            exit(1);
        }
        else
        {
            printf("shmat连接共享内存成功。\n");
            strcpy(write_address,"我是写入共享内存的测试数据");//将数据写入共享内存
            printf("写入共享内存的信息为“%s”。\n",write_address);
            if((shmdt((void *)write_address))<0)//断开与共享内存的连接
                printf("shmdt共享内存断开错误。\n");
            else
                printf("shmdt共享内存断开成功。\n");
            sleep(2);
            return;
        }
    }
    else//子进程，从共享内存中读取数据
    {
        sleep(2);//等待父进程写入共享内存完毕
        printf("子进程ID是：%d\n",getpid());
        if((shmctl(shmid,IPC_STAT,&dsbuf))<0)
        {
            printf("shmctl获取共享内存数据结构出现错误。\n");
            exit(1);
        }
        else
        {
            printf("shmctl获取共享内存数据结构成功。\n建立这个共享内存的进程ID是：%d\n",dsbuf.shm_cpid);
            printf("该共享内存的大小为：%d\n",dsbuf.shm_segsz);
            if((read_address=(char *)shmat(shmid,0,0))<0)//连接共享内存
            {
                printf("shmat连接共享内存出现错误。\n");
                exit(1);
            }
            else
            {
                printf("自共享内存中读取的信息为：“%s”。\n",read_address);
                printf("最后一个操作该共享内存的进程ID是：%d\n",dsbuf.shm_lpid);
                if((shmdt((void *)read_address))<0)//断开与共享内存的连接
                {
                    printf("shmdt共享内存断开错误。\n");
                    exit(1);
                } 
                else
                    printf("shmdt共享内存断开成功。\n");
                if(shmctl(shmid,IPC_RMID,NULL)<0)//删除共享内存及其数据结构
                {
                    printf("shmctl删除共享内存及其数据结构出现错误。\n");
                    exit(1);
                }
                else
                    printf("shmctl删除共享内存及其数据结构成功。\n");
                exit(0); 
            }
        }
    }      
    exit(0);
}

