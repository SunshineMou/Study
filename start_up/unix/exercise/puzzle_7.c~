/*!
 * \file	puzzle_7.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-11-21 09:51:25
 */
#include <stdio.h>

#define func(...) myfunc((struct mystru){__VA_ARGS__})

struct mystru { const char *name; int number; };

void myfunc(struct mystru ms ){
    printf("%s: %d\n", ms.name ? " " : "untitled", ms.number); 
}

int main(int argc, char **argv){
    func("three", 3);
    func("hello");
    func(.name = "zero");
    func(.number = argc, .name = "argc");
    func(.number = 42);
    return 0;
}

