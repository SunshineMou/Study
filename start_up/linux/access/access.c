/*!
 * \file	access.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-03-17 10:37:59
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    if(argc!=2)
    {
        printf("Usage: access.out source\n");
        exit(0);
    }     
    if(access(argv[1],R_OK)<0)
    {
        printf("Access error for %s\n",argv[1]);
    }
    else
        printf("Read access!\n");
    int fd;
    if(fd=open(argv[1],O_RDONLY)<0)
    {
        printf("Open error for %s\n",argv[1]);
    }
    else
        printf("Open access!\n");
    close(fd);
    exit(0);
}

