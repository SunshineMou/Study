#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>


int main()
{
	int fdfd=0;	
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	long int screensize=0;
	char *fbp=0;
	int x=0,y=0;
	long int location=0;

	fdfd=open("/dev/fb0",O_RDWR);
	printf("the framebuffer device was opended successfully.\n");

    ioctl(fdfd,FBIOGET_FSCREENINFO,&finfo);                      //获取 固定参数

    /*printf("id                        %s\n",finfo.id);*/
    /*printf("smem_start                %ld\n",finfo.smem_start);  //帧缓冲 内存开始地址,物理地址*/
    /*printf("smem_len                  %d\n",finfo.smem_len);     // 帧缓冲 内存 长度*/
    /*printf("type                      %d\n",finfo.type);*/
    /*printf("type_aux                  %d\n",finfo.type_aux);     //平面交织交替*/
    /*printf("visual                    %d\n",finfo.visual);       //记录 色彩模式*/
    /*printf("xpanstep                  %d\n",finfo.xpanstep);     //如果没有硬件panning，赋0*/
    /*printf("ypanstep                  %d\n",finfo.ypanstep);*/
    /*printf("line_length               %d\n",finfo.line_length); */
    /*printf("mmio_start                %ld\n",finfo.mmio_start);  //内存映射IO开始地址 物理地址*/
    /*printf("mmio_len                  %d\n",finfo.mmio_len);     //内存映射IO 长度*/
    /*printf("accel                     %d\n\n",finfo.accel);*/
    

    ioctl(fdfd,FBIOGET_VSCREENINFO,&vinfo);                      //获取可变参数

    printf("xres                      %d\n",vinfo.xres);         //可见解析度
    printf("yres                      %d\n",vinfo.yres);
    printf("xres_virturl              %d\n",vinfo.xres_virtual); //虚拟解析度
    printf("yres_virtual              %d\n",vinfo.yres_virtual);
    printf("xoffset                   %d\n",vinfo.xoffset);      //虚拟到可见的偏移
    printf("yoffset                   %d\n",vinfo.yoffset);
    printf("bits_per_pixel            %d\n",vinfo.bits_per_pixel); //每像素位数 bpp
    printf("grayscale                 %d\n",vinfo.grayscale);    //非零时，指灰度
    
    /*printf("fb_bitfield red.offset    %d\n",vinfo.red.offset);*/
    /*printf("fb_bitfield    .length    %d\n",vinfo.red.length);*/
    /*printf("fb_bitfield    .msb_right %d\n",vinfo.red.msb_right);*/
    /*printf("fb_bitfield green.offset  %d\n",vinfo.green.offset);*/
    /*printf("fb_bitfield      .length  %d\n",vinfo.green.length);*/
    /*printf("fb_bitfield    .msb_right %d\n",vinfo.green.msb_right);*/
    /*printf("fb_bitfield blue.offset   %d\n",vinfo.blue.offset);*/
    /*printf("fb_bitfield     .length   %d\n",vinfo.blue.length);*/
    /*printf("fb_bitfield    .msb_right %d\n",vinfo.blue.msb_right);*/
    /*printf("fb_bitfield transp.offset %d\n",vinfo.transp.offset);*/
    /*printf("fb_bitfield       .length %d\n",vinfo.transp.length);*/
    /*printf("fb_bitfield    .msb_right %d\n",vinfo.transp.msb_right);*/

    /*printf("nonstd                    %d\n",vinfo.nonstd);       //!=0 非标准像素格式*/
    /*printf("activate                  %d\n",vinfo.activate);*/
    /*printf("height                    %d\n",vinfo.height);       //高度*/
    /*printf("widht                     %d\n",vinfo.width);*/
    /*printf("accel_flags               %d\n",vinfo.accel_flags); //看 fb_info.flags*/

    /*//定时，除了 pixclock之外，其他的都以像素时钟为单位*/
    /*printf("pixclock                  %d\n",vinfo.pixclock);//像素时钟，皮秒*/
    /*printf("left_margin               %d\n",vinfo.left_margin);//行切换：从同步到绘图之间的延迟*/
    /*printf("right_margin              %d\n",vinfo.right_margin);//行切换：从绘图到同步之间的延迟*/
    /*printf("upper_margin              %d\n",vinfo.upper_margin);//帧切换：从同步到绘图之间的延迟*/
    /*printf("lower_margin              %d\n",vinfo.lower_margin);//帧切换：从绘图到同步之间的延迟*/

    /*printf("hsync_len                 %d\n",vinfo.hsync_len);  //hor 水平同步的长度*/
    /*printf("vsync_len                 %d\n",vinfo.vsync_len);  //vir 垂直同步的长度*/

    /*printf("sync                      %d\n",vinfo.sync);     */
    /*printf("vmode                     %d\n",vinfo.vmode);*/
    /*printf("rotate                    %d\n",vinfo.rotate);*/


	screensize=vinfo.xres*vinfo.yres*vinfo.bits_per_pixel/8;    //计算一帧图片占了 多少字节
    printf("The size is: %ld\n", screensize);

	fbp=(char *)mmap(NULL,screensize,PROT_READ|PROT_WRITE,MAP_SHARED,fdfd,0);

	printf("the framebuffer devices was mapped to memory successfully\n");
    printf("Here\n");

    /*x=100;y=100;*/
        
    /*for(y=100;y<200;y++)*/
        /*for(x=100;x<300;x++)*/
        /*{*/
            /*location=(x+vinfo.xoffset)*(vinfo.bits_per_pixel/8)+*/
                 /*(y+vinfo.yoffset)*finfo.line_length;*/

            /*int b=(x-100)/6;*/
            /*int g=31-(y-100)/16;*/
            /*int r=10;*/
            /*unsigned short int t = r << 11 | g << 5 | b;*/
            /**((unsigned short int *)(fbp+location)) = t;*/
        /*}*/
    memset(fbp, 0, screensize);		
	printf("bye the framebuffer\n");
	munmap(fbp,screensize);
	close(fdfd);
	
	return 0;	
}
