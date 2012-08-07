/*!
 * \file	mmap_write.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-12-26 10:51:59
 */
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct{
    char name[4];
    int  age;
}people;

char data[sizeof(people)*10];

int main(int argc, char** argv)   // map a normal file as shared mem:
{
    int fd,i;
    people *p_map;
    char temp;

    umask(00);
    fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC, 00777);
    /*lseek(fd, sizeof(people)*5-1, SEEK_SET);*/
    lseek(fd, 0, SEEK_SET);
    /*确定文件的大小，确保我们在内存中维护的信息可以同步到这个文件中*/
    write(fd, data, sizeof(people)*10);

    p_map = (people*) mmap(NULL, sizeof(people)*10, PROT_READ | PROT_WRITE, \
            MAP_SHARED, fd, 0);
    close( fd );

    temp = 'a';
    for(i=0; i<10; i++)
    {
        temp += 1;
        memcpy((*(p_map+i)).name, &temp, 1);
        (*(p_map+i)).age = 20 + i;
    }
    
    printf(" initialize over \n ");
    msync((void *)p_map, sizeof(people)*10, MS_SYNC);

    /*sleep(10);*/
    munmap(p_map, sizeof(people)*10);
    printf("umap ok!\n");
    return 0;
}
