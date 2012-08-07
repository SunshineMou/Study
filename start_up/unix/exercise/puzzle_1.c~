/*!
 * \file	puzzle_1.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-11-18 08:49:31
 */
#include <stdio.h>

#define TOTAL_ELEMENTS(argv) ((sizeof(argv)/sizeof(argv[0])))
#define PrintInt(argv) printf("%s : %d\n", #argv, (argv))

int argv[] = {23, 34, 12, 17, 204, 99, 16};

int main()
{
    int d;

    PrintInt(TOTAL_ELEMENTS(argv));
    /*for(d = -1; d <= (TOTAL_ELEMENTS(argv) - 2); d++){*/
    for(d = -1; printf("d is:%d\n", sizeof(argv)/sizeof(argv[0]) - 2), d <= (int)(sizeof(argv)/(int)sizeof(argv[0]) - 2); d++){
        printf("OK!\n");
        printf("%d\n", argv[d+1]);
    }
     
    return 0;
}

