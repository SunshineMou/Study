/*!
 * \file	define.c
 * \brief   带副作用的宏参数	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-10-13 20:38:26
 */
#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

/*!
 * \brief 当宏参数在宏的定义中出现的次数超过一次时，如果参数具有副作用，使用时就有
 *        危险，导致出现不可预料的后果；
 *
 * \param argc
 * \param argv[]
 *
 * \return 
 */
int main(int argc, char* argv[])
{
    int x = 5;
    int y = 8;
    int z;
    z = MAX(x++, y++);
    printf("x = %d, y = %d, z= %d\n", x, y, z);
     
    return 0;
}

