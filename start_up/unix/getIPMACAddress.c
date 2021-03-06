/*!
 * \file	getIPMACAddress.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-08-15 11:35:04
 */

#include <arpa/inet.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

#define MAXINTERFACES 16            /* 最大接口数 */
 
int    fd;                          /* 套接字 */
int    if_len;                      /* 接口数量 */
struct ifreq buf[MAXINTERFACES];    /* ifreq结构数组 */
struct ifconf ifc;                  /* ifconf结构 */
char   nameBuffer[] = "eth0";

int main(int argc, char* argv[])
{
    printf("Content-Type:text/xml\r\n");
    printf("Cache-Control: no-cache\r\n");
    printf("\n");
    printf("<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?>\n");
    printf("<root>");
    /* 建立IPv4的UDP套接字fd */
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
        printf("    <error>1</error>");
        return -1;
    }
 
    /* 初始化ifconf结构 */
    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = (caddr_t) buf;    /*typedef void * caddr_t*/
 
    /* 获得接口列表 */
    if (ioctl(fd, SIOCGIFCONF, (char *) &ifc) == -1){
        printf("    <error>1</error>\n");
        return -1;
    }

    if_len = ifc.ifc_len / sizeof(struct ifreq);   /* 接口数量 */
 
    while (if_len-- > 0) { /* 遍历每个接口 */

        if(strncmp(buf[if_len].ifr_name, nameBuffer, 4) == 0){ /* 接口名称 */
            /* 获得IP地址 */
            if (!(ioctl(fd, SIOCGIFADDR, (char *) &buf[if_len]))){
                printf("    <ipAddress>%s</ipAddress>",
                        (char*)inet_ntoa(((struct sockaddr_in*) (&buf[if_len].ifr_addr))->sin_addr));
            }
            else{
                printf("    <error>1</error>");
                break;
            }

            /*获得MAC地址 */
            if (!(ioctl(fd, SIOCGIFHWADDR, (char *) &buf[if_len]))){
                printf("    <macAddress>%02x:%02x:%02x:%02x:%02x:%02x</macAddress>",
                        (unsigned char) buf[if_len].ifr_hwaddr.sa_data[0],
                        (unsigned char) buf[if_len].ifr_hwaddr.sa_data[1],
                        (unsigned char) buf[if_len].ifr_hwaddr.sa_data[2],
                        (unsigned char) buf[if_len].ifr_hwaddr.sa_data[3],
                        (unsigned char) buf[if_len].ifr_hwaddr.sa_data[4],
                        (unsigned char) buf[if_len].ifr_hwaddr.sa_data[5]);
            }
            else{
                printf("    <error>1</error>");
                break;
            }
        }
    }
    printf("</root>\n");
 
    //关闭socket
    close(fd);
    return 0;     
}

