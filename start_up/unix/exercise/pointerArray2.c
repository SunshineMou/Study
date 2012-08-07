/*!
 * \file	pointerArray2.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-23 20:02:53
 */


#include <stdio.h>

struct Test{
    int a[10];
};

struct Test fun( struct Test* );

int main(int argc, char* argv[]){
    struct Test T;
    int *p = fun( &T ).a;                         /* A */
    int (*q)[10] = &fun( &T ).a;                  /* B */
    printf( "%d", sizeof( fun( &T ).a ) );       /* C*/
    return 0;
}
struct Test fun( struct Test *T ){
    return *T;
}
