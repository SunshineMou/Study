/*!
 * \file	struct.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-12-02 14:56:03
 */
#include <stdio.h>

#pragma pack(8)

struct example_1{
    /*short int    a;*/
    /*long  double b;*/
    short  a;
    long   b;
};

struct example_2{
    char             c;
    struct example_1 struct_1;
    /*char             e;*/
    short             e;
};

#pragma pack()

int main(int argc, char* argv[])
{
    struct example_2 struct_2;
    
    printf("%d\n", sizeof(struct example_1)); 
    printf("%d\n", sizeof(struct example_2)); 
    printf("%d\n", (unsigned int)(&struct_2.struct_1) - \
            (unsigned int)(&struct_2));

    return 0;
}

