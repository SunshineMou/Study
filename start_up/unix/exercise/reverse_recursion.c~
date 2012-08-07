/*!
 * \file	reverse_recursion.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-12-07 19:55:34
 */
#include <stdio.h>

void swap(char *string, unsigned int left, unsigned int right){
    char tmp;
    tmp           = string[left];
    string[left]  = string[right];
    string[right] = tmp;
}

void reverse_recursion(char *string, unsigned int left, unsigned int right){
    if(left >= right)
        return; 
    swap(string, left, right);
    reverse_recursion(string, left + 1, right - 1);
}

int main(int argc, char* argv[])
{
    char test[] = "xiaodong";
    reverse_recursion(test, 0, 7);
    printf("%s\n", test);
     
    return 0;
}

