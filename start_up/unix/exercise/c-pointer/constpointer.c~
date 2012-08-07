/*!
 * \file	constpointer.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-10-12 08:21:30
 */
#include <stdio.h>

void func_1(int* const list);
void func_2(int* const list);
void func_3(const int *list);
void func_4(const int *list);

int main(int argc, char* argv[])
{
    int list[] = {11, 12, 13, 14, 15, 16};
    func_4(list); 
    return 0;
}

/*!
 * \brief (void* const pointer)的使用；
 *
 * \param list
 */
void func_1(int* const list){
    int newlist[] = {11, 12, 13, 14, 15, 16};
    list = newlist;   //错误：现在的list是只读的，它不能重新指向新的地址；但指向的内存中的数据是可以改变的；
    list[0] = 20;
    printf("%d \n", newlist[0]);
}


/*!
 * \brief 我们不能改变(void* const pointer)所指向的地址，但我们可以改变地址中的内容；
 *
 * \param list
 */
void func_2(int* const list){
    list[0] = 20;
    printf("%d \n", list[0]);
}

/*!
 * \brief (const int *pointer)的使用；
 *
 * \param list
 */
void func_3(const int *list){
    list[0] = 20; //错误，我们不能改变list所指向的地址中的内容；但我们可以改变list所指向的地址；
    printf("%d \n", list[0]); 
}

/*!
 * \brief 我们可以改变(const int *pointer)所指向的地址，但是我们不能改变地址中的数据；
 *
 * \param list
 */
void func_4(const int *list){
    int newlist[] = {11, 12, 13, 14, 15, 16};
    list = newlist; 
    printf("%d \n", list[0]);  // Success!  
    list[0] = 20;  //错误，可以改变它指向的地址，但不可以改变地址中的内容； 
}
