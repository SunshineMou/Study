/*!
 * \file	printf_va_list.c
 * \brief   可变参数的运用	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-10-19 14:57:59
 */
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void param_demo(char *fmt, ...);
void va_arg_is_fuc(int num, ...);
void new_printf_1(char *list, int n);
void new_printf_2(char *list, int n);

int main(int argc, char* argv[])
{
    param_demo("idsc", 2, 2.01, "hello, world", 'c');    
    va_arg_is_fuc(4, &new_printf_1, &new_printf_2, &new_printf_2, &new_printf_1);
    return 0;
}

void param_demo(char *fmt, ...)
{
    int param_count, i;
    char *pi;
    param_count = (int)strlen(fmt);
    pi = (char *)&fmt + sizeof(char *);

    for (i=0; i < param_count; i++){
        switch(fmt[i]){
            case 'i':
                printf("int : %d \n", *((int *)pi));
                pi = pi + sizeof (int);
                break;
            case 's':
                printf("string : %s \n", *((char **)pi));
                pi = pi + sizeof (char *);
                break;
            case 'c':
                printf("char : %c \n", *pi);
                pi = pi + sizeof (int);
                break;
            case 'd':
                printf("double : %lf \n", *((double *)pi));
                pi = pi + sizeof (double);
                break;
            default:
                break;
        }
    }
}

void va_arg_is_fuc(int num, ...){
    char *list = "sunshine";
    int i;
    va_list va_list_func;
    va_start(va_list_func, num);
    void (*oper_func[num])(char *, int);
    for(i=0; i<num; i++){
        oper_func[i] = va_arg(va_list_func, void *);
    }
    oper_func[0](list,1);
    oper_func[1](list,2);
    oper_func[2](list,3);
}

void new_printf_1(char *list, int n){
    while(n--)
        printf("[%s]The string is:%s\n",__func__, list);
}

void new_printf_2(char *list, int n){
    while(n--)
        printf("[%s]The string is:%s\n", __func__, list);
}
