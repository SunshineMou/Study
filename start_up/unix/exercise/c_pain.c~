/*!
 * \file	c_pain.c
 * \brief	
 * \author	SunshineMou
 * contact  qingtianmou@gmail.com
 * \version	0.00
 * \date	12-02-13 16:13:33
 */
#include <stdio.h>

typedef struct
{
    char *key;
    char *value;
} T1;

typedef struct
{
    long type;
    char *value;
} T3;

T1 a[] =
{
    {
        "",
        ((char *)&((T3){1, (char *) 1}))
    }
};
int main() {
    T3 *pt3 = (T3*)a[0].value;
    printf("Value: %d\n", (int)pt3->value);
    return (int)pt3->value;
}
