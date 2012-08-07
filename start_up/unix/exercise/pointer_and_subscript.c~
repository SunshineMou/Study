/*!
 * \file	pointer_and_subscript.c
 * \brief   指针会比下标更有效率的情况	
 * \author	SunshineMou
 * contact  qingtianmou@gmail.com
 * \version	0.00
 * \date	12-02-24 15:00:50
 */
#include <stdio.h>

/*!
 * \brief 利用下标初始化数组
 *
 * 为了对下标表达式求值，编译器在程序中插入指令，取得a的值
 * 并把它与整型的长度（也就是4）相乘，这个乘法需要花费一定
 * 的时间和空间。
 */
void subscript_initial(void){
    int array[10], a;
    for(a = 0; a < 10; a++)
        array[a] = 0;
}

/*!
 * \brief 利用指针初始化数组
 *
 * 现在，这个乘法运算出现在for语句的调整部分，1这个值必须
 * 与整型的长度相乘，然后再与指针相加。
 *
 * 但这里存在一个重大的区别：循环每次执行时，执行乘法的都
 * 是两个相同的数（1和4）。结果，这个乘法只在编译器的编译
 * 阶段只执行一次---程序现在包含了一条指令，把4与指针相加
 *
 * 所以在程序的运行阶段并不执行我们所看到的乘法操作。
 */
void pointer_initial(void){
    int array[10], *ap;
    for(ap = array; ap < array + 10; ap++)
        *ap = 0;
}

int main(int argc, char* argv[])
{
    pointer_initial();
    subscript_initial();
     
    return 0;
}

