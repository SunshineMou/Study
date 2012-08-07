/*!
 * \file	rotateString.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-08 09:54:54
 */

#include <stdio.h>
#include <string.h>

void swap(char  *pa, char *pb);

int main(int argc, char* argv[])
{
    int strLength, i;
    char   string[] = "Hello,World!";
    strLength = strlen(string);
    /*rotateString(string, 3);*/
    for(i=0; i<3;i++)
        swap((char *)&string[0 + i], (char *)&string[strLength - i]);
    /*[>string[strLength] = '\0';<]*/
    printf("The final string is:%s\n", string); 
    return 0;
}

/*int rotateString(char *string, int n){*/
    /*int strLength;*/
    /*int i, j;*/
    /*strLength = strlen(string);*/
    /*for(j = 0; j < n; j++){*/
        /*string[strLength] = string[0];*/
        /*for(i = 0; i < strLength; i++ )     */
            /*string[i] = string[i+1];*/
    /*}*/
    /*string[strLength] = '\0';*/
/*}*/

void swap(char  *pa, char *pb)
{
    int temp;
    temp = *pa;
    *pa = *pb;
    *pb = temp;
}
