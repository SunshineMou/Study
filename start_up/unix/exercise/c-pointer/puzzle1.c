/*!
 * \file	puzzle1.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-10-09 10:37:51
 */
#include <stdio.h>

int main(int argc, char* argv[])
{
    int a[5] = {1, 2, 3, 4, 5};
    int *ptr_1 = (int *)(&a + 1);  /*result ---> 2  5*/
    int *ptr_2 = (int *)(a + 1);   /*result ---> 2  1*/

    printf("%d %d\n", *(a + 1), *(ptr_1 - 1));
    printf("%d %d\n", *(a + 1), *(ptr_2 - 1));
     
    return 0;
}

