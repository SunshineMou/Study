/*!
 * \file	strcat.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-03-11 16:56:47
 */

#include <stdio.h>

char * strcat ( char * destination, const char * source );
char * strncat ( char * destination, const char * source, size_t num);

int main(int argc, char* argv[])
{
    if(argc!=3)
        printf("Usage:strcat.out <destination_string> <source_string>");
    /*
    strcat(argv[1],argv[2]);
    */
    strncat(argv[1],argv[2],5);
    printf("The final destination string is:%s\n",argv[1]);
    return 0;
}

/*************Rewrite the C function strcat*************/
char * strcat ( char * destination, const char * source )
{
    int i=0;
    int des_len=0;
    int src_len=0;
    while(*(source+src_len)!=0x00)
        src_len++;
    while(*(destination+des_len)!=0x00)
        des_len++;
    for(i=0;i<src_len;i++)
        *(destination+des_len+i)=*(source+i);
    *(destination+des_len+i)=0x00;
    return destination;    
}

/*******************Rewrite the C function strncat******************/
char * strncat ( char * destination, const char * source, size_t num)
{
    int i=0;
    int des_len=0;
    int src_len=0;
    while(*(source+src_len)!=0x00)
        src_len++;
    while(*(destination+des_len)!=0x00)
        des_len++;
    if(src_len>num)
    {
        for(i=0;i<num;i++)
            *(destination+des_len+i)=*(source+i);
        *(destination+des_len+i)=0x00;
    }
    if(src_len<num)
    {
        for(i=0;i<src_len;i++)
            *(destination+des_len+i)=*(source+i);
        *(destination+des_len+i)=0x00;
    }
    return destination;    
}
