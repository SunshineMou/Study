/*!
 * \file	openfile.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-08-03 16:00:41
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define SLEEPTIME  3
#define ARGLEN     20
#define CONTROLLEN CMSG_LEN(sizeof(int))

/*!
 * \brief 
 *
 * \param send_sock
 * \param send_fd
 * \param data
 * \param bytes
 *
 * \return 
 */
int func_send_fd(int send_sock, int send_fd, void *data, int bytes){
    struct  msghdr msg;
    static  struct cmsghdr *cmptr = NULL;
    struct  iovec  passdata[1];
    int     ret;

    /*填充msg结构*/
    msg.msg_name     = NULL;
    msg.msg_namelen  = 0;
    passdata[0].iov_base = data;
    passdata[0].iov_len  = bytes;
    msg.msg_iov      = passdata;
    msg.msg_iovlen   = 1;

    /*if(send_fd <0){*/
        /*msg.msg_control    = NULL;*/
        /*msg.msg_controllen = 0;*/
    /*}*/
    /*else{*/
        if(cmptr == NULL && (cmptr = malloc(CONTROLLEN)) == NULL)
            return (-1);
        cmptr -> cmsg_level = SOL_SOCKET;
        cmptr -> cmsg_type  = SCM_RIGHTS;
        cmptr -> cmsg_len   = CONTROLLEN;
        msg.msg_control     = cmptr;
        msg.msg_controllen  = CONTROLLEN;
        *(int *)CMSG_DATA(cmptr) = send_fd;
    /*}*/
    if((ret = sendmsg(send_sock, &msg, 0)) <= 0)
        return (-1);
    /*printf("The controllen is: %d\n", CONTROLLEN);*/
    /*printf("The ret is: %d\n", ret);*/
    printf("The fd which the child process send is: %d\n", *(int *)CMSG_DATA(cmptr));
    printf("The data which the child process send is: %s\n", (char *)passdata[0].iov_base);
    close(send_sock);
    return 0;
}

int main(int argc, char* argv[])
{
    int     i, fd, ret;
    ssize_t size;
    size_t  buflen;
    char    data[10];
    char    buf[] = "openfile,write-test!!\n";
    
    umask(0);  /*设置所创建的文件的权限位*/
    unlink("/home/sunshine/file");

    fd = -1;
    if((fd = open("/home/sunshine/file", atoi(argv[1]), atoi(argv[2]))) < 0){
        printf("In openfile, open failed\n");
        exit(-1);
    }

    size = -1;
    buflen = strlen(buf) - 1;
    printf("The length of the string is: %d\n", buflen);
    if((size = write(fd, buf, buflen)) < 0)
        printf("In openfile, write failed.\n");

    /*把设定的data信息也传给父进程*/
    ret = 'a';
    for(i=0; i<sizeof(data); i++,ret++)
        data[i] = ret;
    data[sizeof(data) - 1] = '\0';

    ret = -1;
    if((ret = func_send_fd(atoi(argv[3]), fd, data, 10)))
        printf("In openfileprog, func_send_fd failed.\n");
    close(fd);
    return 0;
}

