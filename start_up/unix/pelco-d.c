/*!
 * \file	pelco-d.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-08-31 14:12:19
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

#define  cmdFiFo  "/tmp/command.fifo"

/*!
 * \brief 利用串口发送数据实现利用pelco-D协议；
 *
 * \param argc
 * \param argv[]
 *
 * \return 
 */
int main(int argc, char* argv[])
{
    int     cmdFd;
    int     *cmdFdPointer;
    ssize_t recvNum;
    int     runStatus = 1;
    fd_set  catchCmd;
    fd_set  catchCmdBackUp;
    char    buffer[12];
    int     ret;
    char    pelcoCmd[7];

    unlink(cmdFiFo);
    ret = mkfifo(cmdFiFo, 0666);
    if ((ret == -1) && (errno != EEXIST))
    {
        perror("Error creating the FIFO");
        exit(1);
    }
    ret = chmod(cmdFiFo, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (ret < 0)
    {
        perror("Error changing the FIFO permission");
        exit(1);
    }

    cmdFd = open(cmdFiFo, O_RDWR | O_NONBLOCK);
    FD_ZERO(&catchCmd);
    FD_SET(cmdFd, &catchCmd);
    while(runStatus)
    {
        catchCmdBackUp = catchCmd;
        if(select(cmdFd + 1, &catchCmdBackUp, NULL, NULL, NULL) > 0)
        {
            if((recvNum = read(cmdFd, &buffer, sizeof(buffer))) == -1) 
            {
                printf("Read %s error:%s\n", cmdFiFo, strerror(errno));
                exit(-1);
            }
            buffer[recvNum] = '\0';
            if(getCmd(buffer, &pelcoCmd) == -1){
                printf("Process Data False!\n");
                exit(-1);
            }
            cmdFdPointer = &cmdFd;
            if(ttyopen(cmdFdPointer, 1) == -1){
                printf("Error in open ttyS*!\n");
                exit(-1);
            }
            if(ttySetOpt(cmdFd, 2400, 8, 'N', 1) < 0){
                printf("Error in setup ttyS*!\n");
                exit(-1);
            }
        }
    }
    return 0;
}

/*!
 * \brief 根据fifo中获取的命令来打包串口要发送的命令；
 *
 * \param cmd
 * \param getcmd
 *
 * \return 
 */
int getCmd(char *cmd, char *getcmd){
    int    i;
    char   *characterFirst;
    char   bufferUp[7]    = {0xff, 0x01, 0x00, 0x08, 0x00, 0xff, 0x08};
    char   bufferFar[7]   = {0xff, 0x01, 0x01, 0x00, 0x00, 0x00, 0x02};
    char   bufferDown[7]  = {0xff, 0x01, 0x00, 0x10, 0x00, 0xff, 0x10};
    char   bufferLeft[7]  = {0xff, 0x01, 0x00, 0x04, 0xff, 0x00, 0x04};
    char   bufferTele[7]  = {0xff, 0x01, 0x00, 0x20, 0x00, 0x00, 0x21};
    char   bufferWide[7]  = {0xff, 0x01, 0x00, 0x40, 0x00, 0x00, 0x41};
    char   bufferNear[7]  = {0xff, 0x01, 0x00, 0x80, 0x00, 0x00, 0x81};
    char   bufferRight[7] = {0xff, 0x01, 0x00, 0x02, 0xff, 0x00, 0x02};

    switch((characterFirst = strchr(cmd, '$')) - strchr(cmd, '=')){
        case 3:
            for(i = 0; i < 7; i++)
                getcmd[i] = bufferUp[i];
            break;
        case 4:
            for(i = 0; i < 7; i++)
                getcmd[i] = bufferFar[i];
            break;
        case 5:
            if(*characterFirst++ == 'd'){
                for(i = 0; i < 7; i++)
                    getcmd[i] = bufferDown[i];
            }
            else if(*characterFirst++ == 'l'){
                for(i = 0; i < 7; i++)
                    getcmd[i] = bufferLeft[i];
            }
            else if(*characterFirst++ == 't'){
                for(i = 0; i < 7; i++)
                    getcmd[i] = bufferTele[i];
            }
            else if(*characterFirst++ == 'w'){
                for(i = 0; i < 7; i++)
                    getcmd[i] = bufferWide[i];
            }
            else if(*characterFirst++ == 'n'){
                for(i = 0; i < 7; i++)
                    getcmd[i] = bufferNear[i];
            }
            break;
        case 6:
            for(i = 0; i < 7; i++)
                getcmd[i] = bufferRight[i];
            break;
        default:
            return -1;
    }
    return 1;
}

/*!
 * \brief 将打包号的命令数据通过串口发送出去
 *
 * \param cmd
 *
 * \return 
 */
int ttyWriteData(char *cmd){
}
/*!
 * \brief 打开/dev下的串口设备ttyS0
 *
 * \param fd      返回串口设备的文件描述符；
 * \param comport 打开串口的端口号
 *
 * \return 
 */
int ttyOpen(int *fd,int comport)
{
    char *dev[]={"/dev/ttyS0","/dev/ttyS1","/dev/ttyS2"};
    long vdisable;
    if (comport==1)//串口 1
    {
        *fd = open( "/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY); /*读写方式，不把文件作为终端设备，无延时模式*/
        if (-1 == *fd){
            perror("Can't Open Serial Port");
            return(-1);
        }
    }
    else if(comport==2)//串口 2
    {
        *fd = open( "/dev/ttyS1", O_RDWR | O_NOCTTY | O_NDELAY);
        if (-1 == *fd){
            perror("Can't Open Serial Port");
            return(-1);
        }
    }
    else if (comport==3)//串口 3
    {
        *fd = open( "/dev/ttyS2", O_RDWR | O_NOCTTY | O_NDELAY);
        if (-1 == *fd){
            perror("Can't Open Serial Port");
            return(-1);
        }
    }

    /*恢复串口为阻塞状态*/
    if(fcntl(*fd, F_SETFL, 0) < 0){
        printf("fcntl failed!\n");
        return -1;
    }
    else
        printf("fcntl=%d\n",fcntl(fd, F_SETFL,0));

    /*测试是否为终端设备*/
    if(isatty(STDIN_FILENO)==0)
        printf("standard input is not a terminal device\n");
    else
        printf("isatty success!\n");
    printf("fd-open=%d\n",*fd);
    return 1;
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
int ttySetOpt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
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
    /*设置数据位数*/
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

    /*刷清未决输入或输出*/
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

