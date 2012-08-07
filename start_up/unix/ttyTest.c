#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

/*!
 * \brief 打开/dev下的串口设备ttyS0
 *
 * \param fd      返回串口设备的文件描述符；
 * \param comport 打开串口的端口号
 *
 * \return 
 */
int open_port(int fd,int comport)
{
    char *dev[]={"/dev/ttyS0","/dev/ttyS1","/dev/ttyS2"};
    long vdisable;
    if (comport==1)//串口 1
    {
        fd = open( "/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY); /*读写方式，不把文件作为终端设备，无延时模式*/
        if (-1 == fd){
            perror("Can't Open Serial Port");
            return(-1);
        }
    }
    else if(comport==2)//串口 2
    {
        fd = open( "/dev/ttyS1", O_RDWR | O_NOCTTY | O_NDELAY);
        if (-1 == fd){
            perror("Can't Open Serial Port");
            return(-1);
        }
    }
    else if (comport==3)//串口 3
    {
        fd = open( "/dev/ttyS2", O_RDWR | O_NOCTTY | O_NDELAY);
        if (-1 == fd){
            perror("Can't Open Serial Port");
            return(-1);
        }
    }

    /*恢复串口为阻塞状态*/
    if(fcntl(fd, F_SETFL, 0) < 0)
        printf("fcntl failed!\n");
    else
        printf("fcntl=%d\n",fcntl(fd, F_SETFL,0));

    /*测试是否为终端设备*/
    if(isatty(STDIN_FILENO)==0)
        printf("standard input is not a terminal device\n");
    else
        printf("isatty success!\n");
    printf("fd-open=%d\n",fd);
    return fd;
}

/*!
 * \brief 设置串口的参数
 *
 * \param fd     打开串口设备的文件描述符
 * \param nSpeed 串口波特率
 * \param nBits  串口发送位数
 * \param nEvent 奇偶校验位
 * \param nStop  停止位
 *
 * \return 
 */
int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
    struct termios newtio,oldtio;
    /*保存测试现有串口参数设置,在这里如果串口号等出错,会有相关的出错信息*/
    if ( tcgetattr( fd,&oldtio) != 0) {
        perror("SetupSerial 1");
        return -1;
    }
    bzero( &newtio, sizeof( newtio ) );
    /*步骤一,设置字符大小*/
    newtio.c_cflag |= CLOCAL | CREAD;
    newtio.c_cflag &= ~CSIZE;
    /*设置停止位*/
    switch( nBits )
    {
        case 7:
            newtio.c_cflag |= CS7;
            break;
        case 8:
            newtio.c_cflag |= CS8;
            break;
    }
    /*设置奇偶校验位*/
    switch( nEvent )
    {
        case 'O': //奇数
            newtio.c_cflag |= PARENB;
            newtio.c_cflag |= PARODD;
            newtio.c_iflag |= (INPCK | ISTRIP);
            break;
        case 'E': //偶数
            newtio.c_iflag |= (INPCK | ISTRIP);
            newtio.c_cflag |= PARENB;
            newtio.c_cflag &= ~PARODD;
            break;
        case 'N': //无奇偶校验位
            newtio.c_cflag &= ~PARENB;
            break;
    }
    /*设置波特率*/
    switch( nSpeed )
    {
        case 2400:
            cfsetispeed(&newtio, B2400);
            cfsetospeed(&newtio, B2400);
            break;
        case 4800:
            cfsetispeed(&newtio, B4800);
            cfsetospeed(&newtio, B4800);
            break;
        case 9600:
            cfsetispeed(&newtio, B9600);
            cfsetospeed(&newtio, B9600);
            break;
        case 115200:
            cfsetispeed(&newtio, B115200);
            cfsetospeed(&newtio, B115200);
            break;
        case 460800:
            cfsetispeed(&newtio, B460800);
            cfsetospeed(&newtio, B460800);
            break;
        default:
            cfsetispeed(&newtio, B9600);
            cfsetospeed(&newtio, B9600);
            break;
    }
    /*设置停止位*/
    if( nStop == 1 )
        newtio.c_cflag &= ~CSTOPB;
    else if ( nStop == 2 )
        newtio.c_cflag |= CSTOPB;

    /*
     * 设置等待时间和最小接收字符
     *
     * 以下的组合为有read立即回传
     */
    newtio.c_cc[VTIME] = 0; /*读时的延时*/
    newtio.c_cc[VMIN] = 0;  /*VMIN:满足read的最小字元数*/

    /*处理未接收字符*/
    tcflush(fd,TCIFLUSH);

    /*
     * 激活新配置
     *
     * tcsetattr: 设置与终端相关的参数；  TCSANOW：改变立即生效；
     */
    if((tcsetattr(fd,TCSANOW,&newtio))!=0){
        perror("com set error");
        return -1;
    }
    printf("set done!\n");
    return 0;
}

int main(void)
{
    int  fd;
    int  nwrite, i;
    char buff[] = "Hello\n";

    /*打开串口*/
    if((fd = open_port(fd, 1))<0){
        perror("open_port error");
        return;
    }

    /*对串口进行设置*/
    if((i = set_opt(fd, 115200, 8, 'N', 1))<0){
        perror("set_opt error");
        return;
    }
    printf("fd=%d\n",fd);

    /*对串口进行写操作*/
    for(i = 0; i < 20; i++){
        nwrite = write(fd, buff, 6);
        printf("nwrite=%d,%s\n", nwrite, buff);
        sleep(1);
    }
    close(fd);
    return;
}
