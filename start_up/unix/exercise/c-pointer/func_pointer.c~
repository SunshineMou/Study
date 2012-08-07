/*!
 * \file	func_pointer.c
 * \brief	函数指针的应用 -->回调函数
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-10-13 13:59:33
 */
#include <stdio.h>

typedef struct int_node{
    int  value;
    void *next;
}iNode;

typedef struct char_node{
    char  value;
    void *next;
}cNode;

iNode *search_list(iNode *node, void const *value, int (*compare)(void const *, void const *));
int compare_int(void const *a, void const *b);
int compare_char(void const *a, void const *b);

int main(int argc, char* argv[])
{
    iNode *header, *result;
    int   searchValue = 2;
    iNode a, b, c;
    a.value = 1;
    b.value = 2;
    c.value = 3;
    a.next  = &b;
    b.next  = &c;
    c.next  = NULL;
    header  = &a;
    result  = search_list(header, &searchValue, &compare_int);
    printf("The value of the node is: %d\n", result->value);
     
    return 0;
}

iNode *search_list(iNode *node, void const *value, int (*compare)(void const *, void const *)){
    while(node != NULL){
        if(compare(&node->value, value))
            break;
        node = node->next;
    }
    return node;
}

int compare_int(void const *a, void const *b){
    return (*(int *)a == *(int *)b ? 1 : 0);
}

int compare_char(void const *a, void const *b){
    return (*(char *)a == *(char *)b ? 1 : 0);
}
