/*!
 * \file	sort.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-10-09 17:27:11
 */
#include <stdio.h>
#include <math.h>

#define MAX_SIZE 101
#define SWAP(x, y, t)  ((t) = (x), (x) = (y), (y) = (t))

void sort(int list[], int n);

int main(int argc, char* argv[])
{
    int i, n;
    int list[MAX_SIZE];
    printf("Please enter the number of numbers to generate: ");
    scanf("%d", &n);
    if(n < 1 || n > MAX_SIZE){
        printf("The number is too large!\n");
        exit(0);
    }

    for(i = 0;i < n; i++){
        list[i] = rand() % 1000;
        printf("%d ", list[i]);
    }

    sort(list, n);

    printf("\n Sorted Array:\n");
    for(i = 0; i < n; i++)
        printf("%d ", list[i]);
    printf("\n");
     
    return 0;
}

void sort(int *list, int n){
    int i, j, min, temp;
    for(i = 0; i < n - 1; i++){
        min = i;
        for(j = i + 1; j < n; j++){
            if(list[min] > list[j])
                min = j;    /*--->如果找到小的数，下一次比较变成与找到的小的数进行比较*/
        }
        SWAP(list[i], list[min], temp);
    } 
}


