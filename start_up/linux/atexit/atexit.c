/*!
 * \file	atexit.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-03-30 08:36:57
 */

#include <stdio.h>

static void my_exit_1(void);
static void my_exit_2(void);

int main(int argc, char* argv[])
{
    if(atexit(my_exit_1)!=0)
    {
        printf("Can't register my_exit_1;\n");
        return -1;
    }
    if(atexit(my_exit_2)!=0)
    {
        printf("Can't register my_exit_2;\n");
        return -1;
    }
    if(atexit(my_exit_2)!=0)
    {
        printf("Can't register my_exit_2;\n");
        return -1;
    }
    printf("Main is done!\n");
    return 0;
}
/* atexit
 *登记终止处理程序，这些函数由exit函数自动調用(最后登记的函数最先被执行)；
 */
static void my_exit_1(void)
{
    printf("First exit handler;\n");
}

static void my_exit_2(void)
{
    printf("Second exit handler;\n");
}
