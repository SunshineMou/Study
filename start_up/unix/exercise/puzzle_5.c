/*!
 * \file	puzzle_5.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-11-18 11:04:32
 */
#include <stdio.h>

int main(int argc, char* argv[])
{
    float f = 0.0f;
    float value_1 = 0.2f;
    float value_2 = 0.1f;
    int i;

    for(i = 0; i < 10; i++)
        f = f + 0.1f;

    if(f == 1.0f)
        printf("f is 1.0!\n");
    else
        printf("f is not 1.0!\n");
     
    if(f >= 1.0f)
        printf("f is 1.0!\n");
    else
        printf("f is not 1.0!\n");

    if((f - 1.0f) < 0.1f)
        printf("f is 1.0!\n");
    else
        printf("f is not 1.0!\n");

    if(value_1 > value_2)
        printf("value_1 > value_2\n");

    return 0;
}

