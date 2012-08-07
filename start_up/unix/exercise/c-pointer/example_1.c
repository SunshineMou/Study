/*!
 * \file	example_1.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-10-09 16:02:50
 */
#include <stdio.h>

int main(int argc, char* argv[])
{
    int i, j, k;
    int num = 0;
    for(i = 1; i < 5; i++){
        for(j = 1; j < 5; j++){
            for(k = 1; k <5; k++){
                if(i != k && j != k && i != j){
                    printf("%d\n", (100*i + 10*j + k));
                    num++;
                }
            }
        }
    }
    printf("The total number is: %d\n", num);

    return 0;
}

