/*!
 * \file	calculator_ADT.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-11-10 14:06:58
 */
#include <stdio.h>
#include <string.h>
#include "stack_ADT.h"

int main(int argc, char* argv[])
{
    char *str = argv[1];
    int i, j, num = strlen(str);
    char cal_data[num];

    /*===中缀-->后缀（波兰表示法）===*/
    char_stack_init(num);
    for(i = 0, j =0; i < num; i++){
        if(str[i] == ')'){
            sprintf(cal_data + j, "%c", char_stack_pop());
            printf("%c ",cal_data[j]);
            j++;
        }
        else if(str[i] == '*' || str[i] == '+' || str[i] == '-' || str[i] == '/'){
            char_stack_push(str[i]);
        }
        else if((str[i] >= '0') && str[i] <= '9'){
            sprintf(cal_data + j, "%c", str[i]);
            printf("%c ",cal_data[j]);
            j++;
        }
        else{
        }
    }
    cal_data[j] = char_stack_pop();
    printf("%c ",cal_data[j]);
    printf("\n");
    char_stack_release();

    /*===计算波兰表示法的字符串===*/
    unsigned int oper;
    stack_init(j+1);
    for(i = 0; i <= j; i++){
        if(cal_data[i] == '+')
            stack_push(stack_pop() + stack_pop());
        if(cal_data[i] == '*')
            stack_push(stack_pop() * stack_pop());
        if(cal_data[i] == '-'){
            oper = stack_pop();
            stack_push(stack_pop() - oper);
        }
        if(cal_data[i] == '/'){
            if((oper = stack_pop()) == 0.0)
                printf("Data error!\n");
            stack_push(stack_pop() / oper);
        }
        if((cal_data[i] >= '0') && cal_data[i] <= '9'){
            stack_push(cal_data[i] - '0');
            printf("The push value is: %d\n", cal_data[i]- '0');
        }
    }
    
    printf("The result is: %d\n", stack_pop());

    stack_release();

    return 0;
}

