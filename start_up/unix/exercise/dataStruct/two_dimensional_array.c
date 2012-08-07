/*!
 * \file	two_dimensional_array.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-11-15 09:46:27
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **creat_two_dimensional_array(unsigned int x, unsigned int y);
void initial_two_dimensional_array(char **argv_list, unsigned int x, unsigned int y);
void qsort_two_dimensional_array(char **argv_list, unsigned int x);
int  compare(void *str_1, void *str_2);

int main(int argc, char* argv[])
{
    int i;
    unsigned int x_dimensional, y_dimensional;
    printf("The dimensional information for the two_dimensional array: x <= 255, y <= 255!\n");
    printf("Please enter the dimensional information for the two_dimensional array:\n");
    printf("Please enter the x-dimensional number:");
    scanf("%d", &x_dimensional);
    printf("\n");
    printf("Please enter the y-dimensional number:");
    scanf("%d", &y_dimensional);
    printf("\n");

    char **two_d_array = creat_two_dimensional_array(x_dimensional, y_dimensional);
    initial_two_dimensional_array(two_d_array, x_dimensional, y_dimensional);
    qsort_two_dimensional_array(two_d_array, x_dimensional);

    printf("The array after the qsort is:\n");
    for(i = 0; i < x_dimensional; i++)
       printf("%s\n", two_d_array[i]); 
    printf("%c\n", two_d_array[0][0]); 

    return 0;
}

char **creat_two_dimensional_array(unsigned int x, unsigned int y){
    int  i;
    char **two_d_array;
    two_d_array = malloc(x * sizeof(char *));
    for(i = 0; i < x; i++)
        two_d_array[i] = malloc(y * sizeof(char));
    return two_d_array;
}

void initial_two_dimensional_array(char **argv_list, unsigned int x, unsigned int y){
    int i;
    printf("Please enter %d strings divided by Spaces! And the length should less than the y-dimensional: %d\n", x, y);
    for(i = 0; i < x; i++){
       printf("Please enter the string_%d: ", i);
       scanf("%s", argv_list[i]);
    } 
    printf("Done!\n");
}

/*!
 * \brief qsort: 按照自己定义的规则进行排序的操作 
 *
 * \param argv_list
 * \param x
 */
void qsort_two_dimensional_array(char **argv_list, unsigned int x){
    qsort(argv_list, x, sizeof(char *), compare);
}

int  compare(void *str_1, void *str_2){
    return (strlen(*(char **)str_1) >= strlen(*(char **)str_2) ? 1 : 0);
}
