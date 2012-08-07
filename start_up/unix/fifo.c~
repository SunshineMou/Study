/*!
 * \file	fifo.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-10-19 08:25:11
 */
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

int creatFiFo(void);
int writeFiFo(int *fd);
int readFiFo(int *fd);

/*
 * 1.没有指定O_NONBLOCK:  只读open要阻塞到摸个其他进程为写而打开此FIFO;
 *                        类似，只写open要阻塞到某个其他程序为只读而打开它。
 *
 * 2.指定了  O_NONBLOCK:  则只读open立即返回。但是，如果没有进程已经为读而打开一个FIFO，
 *                        那么只写open将出错返回-1，其返回值是ENXIO.
 */

int main(int argc, char* argv[])
{
    int fifoFd;
    creatFiFo();
    readFiFo(&fifoFd);
    writeFiFo(&fifoFd);
     
    return 0;
}

int creatFiFo(void){
    umask(00);
    if(mkfifo("/tmp/test.fifo", 0666) == -1){
        printf("Creat FIFO error!\n");
        return 0;
    }
    printf("Creat FIFO success!\n");
    return 1;
}

int readFiFo(int *fd){
    if((*fd = open("/tmp/test.fifo", O_RDONLY | O_NONBLOCK)) == -1){
        printf("Open FIFO --RDONLY-- error!\n");
        return 0;
    }
    printf("Open FIFO --RDONLY-- success!\n");
    return 1;
}

int writeFiFo(int *fd){
    if((*fd = open("/tmp/test.fifo", O_WRONLY | O_NONBLOCK)) == -1){
        printf("Open FIFO --WRONLY-- error!\n");
        return 0;
    }
    printf("Open FIFO --WRONLY-- success!\n");
    return 1;
}

