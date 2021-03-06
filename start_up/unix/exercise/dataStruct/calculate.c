/*!
 * \file	calculate.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-10-19 11:41:22
 */
#include <stdio.h>

#define TEST_VALUE 200

void calculate(int *list, int n, int value, int total);
int final;

int main(int argc, char* argv[])
{
    int money[6] = {1, 2, 5, 10, 20, 50};
    calculate(money, 0, 0, 6);
    printf("The value is: %d\n", final);
     
    return 0;
}

void calculate(int *list, int n, int value, int total){
    int temp, i;
    if(n < total){
        for(i=0; i <= TEST_VALUE/list[n]; i++){
            if((temp = (value + list[n] * i)) == TEST_VALUE){
                final++;
                break;
            }
            calculate(list, n+1, temp, 6);
        }
    }
}
