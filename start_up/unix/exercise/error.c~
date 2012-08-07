/*!
 * \file	error.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-12-01 11:40:15
 */
#include <string.h>
#include <malloc.h>

int main()
{
    char* src  = "hello,world";
    char* dest = NULL;
    int len    = strlen(src);
    printf("The length is: %d\n", len);
    dest       = (char*)malloc(len);
    char* d    = dest;
    char* s    = src + len;
    while(len--!=0)
        *(d++)=*(--s);
    printf("%s\n", dest);
    
    free(dest);
    return 0;
}
