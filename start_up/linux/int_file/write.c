/*!
 * \file	write.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	12-01-26 10:43:39
 */
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    int fd, fd_2;
    if((fd = open("test", O_RDONLY | O_CREAT, 0666)) < 0){
        fprintf(stderr, "Open file error!\n");
        return 0;
    }
    fprintf(stderr, "Open file Success!\n");
    
    if((fd_2 = open("if", O_WRONLY | O_CREAT, 0666)) < 0){
        fprintf(stderr, "Open file --if-- error!\n");
        return 0;
    }
    fprintf(stderr, "Open file --if-- Success!\n");

    printf("fd is: %d\n", fd);

    if(write(fd_2, &fd, sizeof(fd)) < 0){
        fprintf(stderr, "Write fd error!\n");
        perror("Reason");
    }

    while(1)
       sleep(1);

    return 0;
}

