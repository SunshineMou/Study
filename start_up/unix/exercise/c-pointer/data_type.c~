/*!
 * \file	array.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-10-14 11:14:13
 */
#include <stdio.h>

/*!
 * \brief 如果某个算数运算符的所有操作数均为整数，则执行整形运算；
 *        如果某个运算符有个浮点型和一个整型操作数，则在开始运算
 *        之前，整型操作数会被转换为浮点操作数；
 *
 * \param argc
 * \param argv[]
 *
 * \return 
 */
int main(int argc, char* argv[])
{
    int a[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    printf("The value of a[2][2] is: %d\n", 2[2[a]]);
    
    float test_1, test_2;
    test_1 = 5/9;   /*--> 5/9 = 0; 所以test = 0.00000*/   
    test_2 = 5.0/9.0;   /*--> 5.0/9.0 != 0; 程序可正常执行，得到应有的结果*/   
    printf("The value is: %f\n", test_1);  
    printf("The value is: %f\n", test_2);  
    return 0;
}

