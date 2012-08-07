/*!
 * \file	func_p.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-12-01 11:20:16
 */

#include <stdio.h>

int inc(int a){
    return(++a);
}
int multi(int*a,int*b,int*c){
    return(*c=*a**b);
}

typedef int(*FUNC1)(int in);
typedef int(*FUNC2) (int*,int*,int*);

void show(FUNC2 fun,int arg1, int*arg2){
    FUNC1 p = inc;
    int temp = p(arg1);
    fun(&temp,&arg1, arg2);
    printf("%d\n",*arg2);
}

int main(){
    int a;
    show(multi,10,&a);
    return 0;
}
