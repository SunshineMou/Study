/*!
 * \file	get_memory.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-12-01 15:09:50
 */
#include <stdio.h>
#include <string.h>
#include <malloc.h>

void Test(void){
    char *str = (char *) malloc(100);
    strcpy(str, "hello");
    free(str);
    if(str != NULL){
        strcpy(str, "world");
        printf(str);
    }
    printf("\n");
}

char *GetMemory(void){
    char p[] = "hello world";
    printf("%s\n", p);
    return p;
}
void test(void){
    char *str = NULL;
    str = GetMemory();
    printf("%c\n", *str+4);
}

int main(int argc, char* argv[])
{
    Test();     
    test();
    return 0;
}

