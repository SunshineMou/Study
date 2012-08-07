/*!
 * \file	strcmp.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-03-12 08:48:49
 */
#include <stdio.h>

int strcmp(const char *str1, const char *str2);
int strncmp(const char *str1, const char *str2, size_t num);

int main(int argc, char* argv[])
{
    int result;
    if(argc!=3)
       printf("Usage:strcmp.out <string1> <string2>\n");
    /*
    result=strcmp(argv[1],argv[2]);
    */ 
    result = strncmp(argv[1],argv[2],5);
    if(result==1)
        printf("The greater string is:%s\n",argv[1]);
    if(result==0)
        printf("The two string is equal;\n");
    if(result==-1)
        printf("The greater string is:%s\n",argv[2]);
    return 0;
}

/*Rewrite the function strcmp*/

int strcmp(const char *str1, const char *str2)
{
    int number=0;
    while(*(str1+number)==*(str2+number))
    {
        if(*(str1+number)==0x00)
            return 0;
        number++;
    }
    if(*(str1+number) > *(str2+number))
        return 1;
    if(*(str1+number) < *(str2+number))
        return -1;
}

/*Rewrite the function strncmp*/

int strncmp(const char *str1, const char *str2, size_t num)
{
    /*********************************************************************************************************************************/
    /* The followed code is used for detect if the string length is less than "num".If it is true, return -2, print the debug string;*/
    /*********************************************************************************************************************************/
    int str1_len=0;
    int str2_len=0;
    while(*(str1+str1_len)!=0x00)
        str1_len++;
    while(*(str2+str2_len)!=0x00)
        str2_len++;
    if(str1_len < num || str2_len < num)
    {
        printf("Error:The string is less than %d bits\n",num);
        return -2;
    }
    /********************************/
    /*This is the main function code*/
    /********************************/
    int number=0;
    while(*(str1+number)==*(str2+number))
    {
        if(number==num)
            return 0;
        number++;
    }
    if(*(str1+number) > *(str2+number))
        return 1;
    if(*(str1+number) < *(str2+number))
        return -1;
}
