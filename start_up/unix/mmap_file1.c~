/*!
 * \file	mmap_file1.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-08-05 11:48:47
 */

#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct {
    char name[4];
    int  age;
}people;

/*!
 * \brief     执行的时候需要通过命令行制定测试文件的地址： for  example: /tmp/test_shm
 *
 * \param argc
 * \param argv[]
 *
 * \return 
 */
int main(int argc, char* argv[])
{
    int    fd, i;
    people *p_map;
    char   temp;

    fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC, 00777);
    /*
     *  lseek:显式的为一个打开的文件设置其偏移量 
     */
    lseek(fd, sizeof(people)*5-1, SEEK_SET);  
    write(fd, "", 1);
    
    p_map = (people *)mmap(NULL, sizeof(people)*10, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    close(fd);
    temp = 'a';
    for(i=0; i<10; i++){
        temp += 1;
        memcpy( (*(p_map + i)).name, &temp, 2);
        (*(p_map + i)).age = 20 + i;
    }

    printf("Initialize over \n");
    sleep(10);
    munmap(p_map, sizeof(people)*10); /*munmap之后，只会将显式设置偏移量的数据同步到指定的文件上*/
    printf("umap ok \n");

    return 0;
}

