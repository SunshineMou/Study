/*!
 * \file	hotplug.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-08-01 10:52:52
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <linux/types.h>
#include <linux/netlink.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <netinet/in.h>

#define UEVENT_BUFFER_SIZE 2048
#define USB_ADD_SIGNAL  "add@/devices/pci0000:00/0000:00:11.0/0000:02:02.0/usb1"

/*
 *   使用NETLINK是内核kernel与用户层的通信方式，使用socket通信，比使用系统调用和信号量简单，易于理解；
 *   使用NETLINK也可以实现通过广播形式实现用户层的两个进程之间的通信；
 */

static int init_hotplug_socket(){
    const int buffersize = 1024;
    int ret;

    struct sockaddr_nl snl;
    memset(&snl, 0x00, sizeof(struct sockaddr_nl));
    snl.nl_family = AF_NETLINK;
    snl.nl_pid =getpid();
    snl.nl_groups = 1;     /* 这是发广播用的，如果是发往内核该值为0*/
    
    /*
     * SOC_DGRAM:与对方通信是不需要逻辑连接的，只需要送出一个报文，其地址是一个对方进程所使用的套接字；
     * NETLINK_KOBJECT_UEVENT:内核事件向用户态通知
     */
    int hotplug_socket = socket(AF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);
    if(hotplug_socket == -1){
        printf("Error: Creat socket: %s",strerror(errno));
        return -1;
    }

    setsockopt(hotplug_socket, SOL_SOCKET, SO_RCVBUFFORCE, &buffersize, sizeof(buffersize));

    ret = bind(hotplug_socket, (struct sockaddr *)&snl, sizeof(struct sockaddr_nl));
    if(ret < 0){
        printf("Bind failed: %s", strerror(errno));
        close(hotplug_socket);
        return -1;
    }

    return hotplug_socket;
}


int main(int argc, char* argv[])
{ 
    int hotplug_socket = init_hotplug_socket();
    
    while(1){
        char buffer[UEVENT_BUFFER_SIZE * 2] = {0};
        recv(hotplug_socket, &buffer, sizeof(buffer), 0);
        /*if(memcmp(buffer, USB_ADD_SIGNAL, strlen(USB_ADD_SIGNAL)) == 0){*/
            /*printf("you have add an usb device on your computer!\n");*/
            /*return 0;*/
        /*}*/
        printf(" %s | Sys Info\n", buffer);
    }   
    return 0;
}

