/*!
 * \file	recursion.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-10-11 13:23:41
 */
#include <stdio.h>

#define COMPARE(a, b)   ((a) < (b) ? 1 : ((a) == (b)) ? 0 : -1)
#define SWAP(a, b, tmp)    ((tmp) = (a), (a) = (b), (b) = (tmp))

int recursion(int *list, int searchNum, int left, int right);
void perm(char *list, int i, int n);

int main(int argc, char* argv[])
{
    int numList[11] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int num, j;
    if((num = recursion(numList, 19, 0, 10)) == -1){
        printf("Can not find the number!\n");
        return 0;
    }
    printf("It is the %d number in the array!\n", num);

    char charList[] = {'a', 'b', 'c'};
    perm(charList, 0, 2);

    printf("The original list is: ");
    for(j = 0; j < 3; j++)
        printf("%c ", charList[j]);
    printf("   \n");
     
    return 0;
}

int recursion(int *list, int searchNum, int left, int right){
    int middle;
    if(left <= right){
        middle = (left + right)/2;
        switch(COMPARE(list[middle], searchNum)){
            case 1:
                recursion(list, searchNum, middle + 1, right);
            case 0:
                return middle;
            case -1:
                recursion(list, searchNum, left, middle - 1);
        }
    }
    return -1;
}

/*!
 * \brief 递归的全排列产生算法
 *
 * \param list
 * \param i
 * \param n
 */
void perm(char *list, int i, int n){
    int j, tmp;
    if(i == n){
        for(j = 0; j <= n; j++)
            printf("%c ", list[j]);
        printf("   \n");
    }

    else{
        for(j = i; j <= n; j++){
            printf("%d\n",j);
            SWAP(list[i], list[j], tmp);
            perm(list, i+1, n);
            SWAP(list[i], list[j], tmp);
        }
    }
}
