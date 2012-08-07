/*!
 * \file	strstr.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-03-12 16:34:29
 */
#include <stdio.h>

char * strstr ( char * str1, const char * str2 );

int main(int argc, char* argv[])
{
    char *point;
    if(argc!=3)
        printf("Usage:strstr.out <str1> <str2>");
    point=strstr(argv[1],argv[2]);
    printf("The begining string is:%s\n",point);
    return 0;
}

/********Rewrite the function strstr************/

char *strstr ( char * str1, const char * str2 )
{
    int str2_len=0;
    int str1_len=0;
    int cycle=0;
    int i=0;
    int j=0;
    while(*(str2+str2_len) != 0x00)
        str2_len++;
    while(*(str1+str1_len) != 0x00)
        str1_len++;
    for(i=0;i<str1_len;i++)
    {
        if(*(str1+i) == *str2)
        {
            for(j=0;j<str2_len;j++)
            {
                if(*(str1+i+j)==*(str2+j))
                    cycle++;
            }
            if(cycle==str2_len)
                return (str1+i);
            if(cycle!=str2_len)
                cycle=0;
        }
    }
    return (char *)0x00;
}

