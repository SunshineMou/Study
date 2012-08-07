/*!
 * \file	func_xiaodong.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-03-19 11:17:03
 */

/*!
 * \brief THe function "strrindex" returns the poistion of the rightmost occurrence of the char 'letter' in the tring;
 *
 * \param string
 * \param letter
 *
 * \return 
 */


#include <stdio.h>
#include <fcntl.h>

int strrindex(char *string, char letter)
{
    int j=0;
    int search_letter=0;
    for(;*string != '\0'; string++)
	{
        j++;
        if(*string == letter)
		    if(search_letter<=j)
		        search_letter=j;
	}
    if(search_letter==0)
	return -1;
    else
        printf("The location is %d\n",search_letter);
	return search_letter;
}
/*!
 * \brief Write a function reverse(s) that reverses the character string s . 
 *
 * \param string[]
 *
 * \return 
 */ 
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
/*!
 * \brief Copy the source string to the destination string;
 *
 * \param destination
 * \param source
 *
 * \return 
 */
char *strcpy(char *destination, char *source)
{

    /********************************************************
     * The following code is to detect if the destination 
     * is enough to storethe source string
     * ******************************************************/
    int des_len=0;
    int src_len=0;
    while(*(destination+des_len)!=0x00)
	des_len++;
    while(*(source+src_len)!=0x00)
	src_len++;
    if(des_len<src_len)
    {
	printf("The destination is not long enough to store the source\n");
	return NULL;
    }
    /*****The main function code*****/
    int i=0;
    while(*(source+i)!=0x00)
    {
	*(destination+i)=*(source+i);
	    i++;	
    }
    *(destination+i)=0x00;
    return destination;
}

/*!
 * \brief Copy the first num bits of the source string to the destination string;
 *
 * \param destination
 * \param source
 * \param num
 *
 * \return 
 */
char *strncpy(char *destination, const char *source, size_t num)
{
    /****************************************************
     * The following code is to detect if the destination 
     * is enough to store the source string
     ***************************************************/
    int des_len=0;
    while(*(destination+des_len)!=0x00)
	des_len++;
    if(des_len<num)
    {
	printf("The destination is not long enough to store the source\n");
	return NULL;
    }
    /********The main function code********/
    int i=0;
    int j=0;
    for(i=0;i<num;i++)
    {
	*(destination+i)=*(source+i);
	if(*(source+i)==0x00)
        {
	    for(j=i;j<num;j++)
	        *(destination+j)=0x00;	
	    break;
	}
    }
    return destination;
}
/*!
 * \brief Store the source string to the destination string;
 *
 * \param destination
 * \param source
 *
 * \return 
 */
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

/*!
 * \brief Store the first num bits of the source string to the destination string;
 *
 * \param destination
 * \param source
 * \param num
 *
 * \return 
 */
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
/*!
 * \brief Compare the string 'str1' and the string 'str2';
 *
 * \param str1
 * \param str2
 *
 * \return 
 */
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

/*!
 * \brief Compare the first num bits of the string 'str1' and 'str2'; 
 *
 * \param str1
 * \param str2
 * \param num
 *
 * \return 
 */
int strncmp(const char *str1, const char *str2, size_t num)
{
    /*******************************************************************/
    /* The followed code is used for detect if the string length is less 
     * than "num".If it is true, return -2, print the debug string;*/
    /*******************************************************************/
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
/*!
 * \brief Search the string 'str2' in the string 'str1';
 *
 * \param str1
 * \param str2
 *
 * \return 
 */
char *strstr ( char * source, const char *pattern )
{
    int i=0;
    for(;*source!='\0';source++)
    {
        for(i = 0;*(pattern+i) == *(source+i) && *pattern!='\0';i++)
        {
            if(*(pattern+i+1)=='\0')
            return (source); 
        }
        i=0;
    }
    return NULL; 
}

int strstr_nocase(const char *source,char *pattern)
{
    int i=0;
    for(;*source!='\0';source++)
    {
        for(i = 0;(*(pattern+i) == *(source+i) || *(pattern+i) == *(source+i)+0x20 || *(pattern+i) == *(source+i)-0x20) && *pattern!='\0';i++)
        {
            if(*(pattern+i+1)=='\0')
            return 1; 
        }
        i=0;
    }
    return 0; 
}
