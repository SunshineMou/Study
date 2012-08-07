/*!
 * \file	initial.c
 * \brief	
 * \author	SunshineMou
 * contact  qingtianmou@gmail.com
 * \version	0.00
 * \date	12-02-13 15:17:23
 */
#include <stdio.h>

int main(int argc, char* argv[])
{
    struct {
        int x;
        struct {
            int y, z;
        } nested;
    } i = { .nested.y = 5, 8, .x = 1, 2 };

    printf("i.nested.y: %d, i.nested.z: %d\n", i.nested.y, i.nested.z);
    printf("i.x: %d\n", i.x);
    return 0;
}

