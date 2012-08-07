/*!
 * \file	bit.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-12-07 13:19:55
 */
#include <stdio.h>

struct bit{
    unsigned int is_first  : 1;
    unsigned int           : 0;
    unsigned int is_second : 1;
    unsigned int is_third  : 1;
};

int main(int argc, char* argv[])
{
    struct bit example = {0, 1, 1};

    printf("The size of the unsigned int is:%u\n", sizeof(unsigned int));
    printf("The size of the bit struct is:%u\n", sizeof(struct bit));
    
    if(example.is_first == 1)
        printf("The first bit is 1!\n");
    else
        printf("The first bit is 0!\n");
     
    if(example.is_second == 1)
        printf("The second bit is 1!\n");
    else
        printf("The second bit is 0!\n");

    if(example.is_third == 1)
        printf("The third bit is 1!\n");
    else
        printf("The third bit is 0!\n");

    printf("Value: %u\n", *((unsigned int *)&example) + 1);

    return 0;
}

