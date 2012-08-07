/*!
 * \file	strstr_nocase.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-03-22 18:49:23
 */

#include <stdio.h>

char *strstr_nocase(char *source,char *pattern);
char *reverse(char string[]);

int main(int argc, char* argv[])
{
    char *point;
    char *point2;
    point = strstr_nocase(argv[1],argv[2]);
    printf("The string is:%s;\n",point);
    point2 = reverse(argv[1]);
    printf("The reverse string is:%s;\n",point2);
    return 0;
}

char *strstr_nocase(char *source,char *pattern)
{
    int i=0;
    for(;*source!='\0';source++)
    {
        for(i = 0;(*(pattern+i) == *(source+i) || *(pattern+i) == *(source+i)+0x20 || *(pattern+i) == *(source+i)-0x20) && *pattern!='\0';i++)
        {
            if(*(pattern+i+1)=='\0')
            return (source); 
        }
        i=0;
    }
    return NULL; 
}
char *reverse(char string[])
{
    int i=0;
    int j=0;
    char tmp;
    for(i=0;string[i] != '\0';i++)
        ;
    for(j=0;j<i/2;j++)
    {
        tmp = string[j];
        string[j] = string[i-j-1];
        string[i-j-1] = tmp;
    }
    printf("The reverse string is: %s\n",string);
    return string;
}  
