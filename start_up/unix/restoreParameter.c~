/*!
 * \file	restoreParameter.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-10-08 09:06:41
 */
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if(execl("/bin/tar", "tar", "-xvf", "/tmp/etc.tar", "-C", "/", NULL) == -1){
        printf("untar the upload file fail!!\n");
        exit(0);
    }
    /*if(execl("/bin/rm", "rm", "-rf", "/etc", NULL) == -1){*/
        /*printf("Cancle the '/etc' file fail!!\n");*/
        /*exit(0);*/
    /*}*/
    /*if(execl("/bin/mv", "mv", "/etc.back", "/etc",NULL) == -1){*/
        /*printf("Rename the '/etc' file fail!!\n");*/
        /*exit(0);*/
    /*}*/
    printf("Success!\n");
    return 0;
}

