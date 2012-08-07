#include <linux/fb.h>

int main()
{
    int fbfd = 0;

    struct fb_var_screeninfo vinfo;

    struct fb_fix_screeninfo finfo;

    long int screensize = 0;

    /*打开设备文件*/

    fbfd = open("/dev/fb0", O_RDWR);

    /*取得屏幕相关参数*/

    ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo);

    ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo);

    /*计算屏幕缓冲区大小*/

    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    /*映射屏幕缓冲区到用户地址空间*/

    fbp=(char*)mmap(0,screensize,PROT_READ|PROT_WRITE,MAP_SHARED, fbfd, 0);

    /*下面可通过 fbp指针读写缓冲区*/

    ……

        /*释放缓冲区，关闭设备*/

        munmap(fbp, screensize);

    close(fbfd);

}
