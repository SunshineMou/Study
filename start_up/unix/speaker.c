/*!
 * \file	speaker.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-09 14:13:54
 */

#include <fcntl.h>
#include <stdio.h>
#include <stat.h>
#include <sys/types.h>
#include <sys/soundcard.h>

int main(int argc, char* argv[])
{
    int  id,  fd,  i,  j;
    /*存储音频数据的缓冲区*/
    char audioBuffer[4096];

    /*打开声卡设备，失败则退出*/
    if((id = open("/dev/audio", O_RDWR)) < 0){
        printf(stderr,"Can't open sound device!\n");
        exit(-1);
    }

    /*打开输出文件，失败则退出*/
    if((fd = open("test.wav", O_RDWR)) < 0){
        fprintf(stderr, "Can't open output file!\n");
    }
     
    return 0;
}

