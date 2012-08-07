/*!
 * \file	umask.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-03-17 11:32:16
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |S_IROTH | S_IWOTH )

int main(int argc, char* argv[])
{
    umask(0);
    if(creat("sunshine_1",RWRWRW)<0)
        printf("Creat error!\n");
    umask(S_IRGRP | S_IWGRP |S_IROTH | S_IWOTH );
    if(creat("sunshine_2",RWRWRW)<0)
        printf("Creat error!\n");
    exit(0);
}

