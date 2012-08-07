/*!
 * \file	funcPointer.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-02 08:13:44
 */
#include <stdio.h>

int fun0(const int a)//定义谓词1 （我们把作为函数参数的函数称为谓词）
{
    if(a == 1)
        return 1;
    else
        return 0;
}

int fun1(const int a)//定义谓词2
{
    if(a < 10)
        return 1;
    else
        return 0;
}

/*根据whatCondition函数指针所指的函数（谓词）设置的条件打印数组*/
void print_arr_if(const int *arr, int(*whatCondition)(const int))
{
    /*printf("%d ", sizeof(arr));*/
    int   i = 0;
    for(i = 0; i < 8; i++)
    {
        if( whatCondition(arr[i]) )
            printf("%d ",arr[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[])
{
    int arr[] = {1, 1, 2, 1, 11, 12, 3, 10};
    /*printf("%d ", sizeof(arr));*/
    print_arr_if(arr, fun0); //打印结果为1 1
    print_arr_if(arr, fun1); //打印结果为1,1,2,1,3
    return 0;
}

