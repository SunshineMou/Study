/*!
 * \file	pointer-to-pointer.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-10-08 15:19:15
 */
#include <stdio.h>

void find(char array[], char search, char **pa){
    int i;
    for(i = 0; *(array + i) != 0; i++){
        printf("*(array + i) = %c\n", *(array + i));
        if(*(array + i) == search){
            *pa = array + i;
            break;
        }
        else if(*(array + i + 1) == 0){
            *pa = NULL;
            break;
        }
    }
}

/*!
 * \brief 这个find1根本就完不成查找操作！！为什么？
 *                                      ------->因为这个函数本身它就是值传递
 *
 * \param array[]
 * \param search
 * \param pa
 */
void find1(char array[], char search, char *pa){
    int i;
    for(i = 0; *(array + i) != 0; i++){
        printf("*(array + i) = %c\n", *(array + i));
        if(*(array + i) == search){
            pa = array + i;
            break;
        }
        else if(*(array + i + 1) == 0){
            pa = NULL;
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    char str[] = {"afsdfsdfdf0"};
    char a = 'd';
    char *p = 0;
    find(str, a, &p);
    if(p == NULL){
        printf("Not Found!\n");
    }
    else{
        printf("Found! p = %s\n", p);
    }
     
    return 0;
}

