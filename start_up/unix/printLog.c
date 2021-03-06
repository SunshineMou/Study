/*!
 * \file	printLog.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-08-19 11:00:33
 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int  fbfd = 0;
    char *fbp;
    FILE *fp;

    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;

    long int screensize = 0;
    char content[1024];

    /*打开设备文件*/
    fbfd = open("/dev/fb0", O_RDWR);

    /*取得屏幕相关参数*/
    ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo);
    ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo);

    /*计算屏幕缓冲区大小*/
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
    printf("The buffer size is: %ld\n", screensize);
    /*映射屏幕缓冲区到用户地址空间*/
    fbp = (char*)mmap(NULL, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);

    close(fbfd);

    /*下面可通过 fbp指针读写缓冲区*/
    /*fp = fopen("/home/sunshie/log.png", "r");*/
    /*while(fread(content, sizeof(content), 1, fp) != sizeof(content)){*/
    /*printf("Here\n");*/
        /*strcpy(fbp, content);*/
    /*}*/

    /*释放缓冲区，关闭设备*/
    munmap(fbp, screensize);

    return 0;
}
