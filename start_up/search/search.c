/*!
 * \file	search.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-03-21 09:29:39
 */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#define MAX_NUM 1101

struct file_info
{
    int number;
    char info[20];
};

struct file_info f_info;
char buffer[MAX_NUM];

int search(char *file);

int main(int argc, char* argv[])
{
    int i;
    if(argc!=2)
    {
        printf("Usage:search.out file.txt\n");
        exit(-1);
    }
    if(search(argv[1]) == 0)
        exit(-1);
    printf("The total number:%d\n",f_info.number);
    for(i=0;i<20;i++)
        printf("The number of length %d is:%d\n",i,f_info.info[i]);
    exit(0);
}

int search(char *file)
{
    FILE *fd;
    int length = 0;
    int i;
    fd = fopen(file , "r");
    if(fd == NULL)
    {
        printf("Open %s error;\n",file);
        return 0;
    }
    while(fgets(buffer , MAX_NUM , fd)!=NULL)
    {
        printf("Open: %s;\n",buffer);
        for(i=0; buffer[i] !='\n'; i++)
        {
            length++;
            if(buffer[i] == ' ' || buffer[i] == '\t' || \
                    buffer[i] == ',' || buffer[i] == ';' || buffer[i] == '.')
            {
                printf("The char of the last word is:%c\n",buffer[i-1]);
                f_info.number++;
                f_info.info[length - 1]++;
                length = 0;
                continue;
            }
            if(buffer[i+1] == '\n')
            {
                printf("The char of the last word is:%c\n",buffer[i]);
                f_info.number++;
                f_info.info[length]++;
                length = 0;
            }
        }
    }   
    return 1;
}
