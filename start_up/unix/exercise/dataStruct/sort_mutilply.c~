/*!
 * \file	sort_mutilply.c
 * \brief	
 * \author	SunshineMou
 * contact  qingtianmou@gmail.com
 * \version	0.00
 * \date	12-02-17 16:38:01
 */
#include <stdio.h>
#include <stdlib.h>

typedef int Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) { Item t = A; A = B; B = t;}
#define compexch(A, B) if(less(B, A)) exch(A, B)
#define STEP 3

void insert_sort(Item a[], int begin, int end);
void selection(Item a[], int begin, int end);
void bubble(Item a[], int begin, int end);
void insertion(Item a[], int begin, int end);
void shellsort(Item a[], int begin, int end);

int main(int argc, char* argv[])
{
    int i, N = atoi(argv[1]), sw = atoi(argv[2]);
    int *a = malloc(N * sizeof(int));

    if(sw)
        for(i = 0; i < N; i++)
            a[i] = 1000 * (1.0 *rand()/RAND_MAX);
    else
        while(scanf("%d", a + N) == 1)
            N++;
    /*insert_sort(a, 0, N - 1);*/
    /*selection(a, 0, N - 1);*/
    /*bubble(a, 0, N - 1);*/
    /*insertion(a, 0, N - 1);*/
    shellsort(a, 0, N - 1);

    for(i = 0; i < N; i++)
        printf("%3d ", a[i]);
    printf("\n");
     
    return 0;
}

/*!
 * \brief        插入排序的一种变形
 *
 * \param a[]    要排列的数组
 * \param begin  要排列的起始位置
 * \param end    要排列的结束位置
 */
void insert_sort(Item a[], int begin, int end)
{
    int i, j;
    for(i = begin + 1; i <= end; i++)
        for(j = i; j > begin; j--)
            compexch(a[j-1], a[j]);
}

/*!
 * \brief        选择排序
 *
 * \param a[]    要排列的数组
 * \param begin  要排列的起始位置
 * \param end    要排列的结束位置
 */
void selection(Item a[], int begin, int end){
    int i, j;
    for(i = begin; i < end; i++){
        int min = i;
        for(j = i + 1; j <= end; j++)
            if(less(a[j], a[min]))
                min = j;
        exch(a[i], a[min]);
    }
}

/*!
 * \brief        冒泡排序
 *
 * \param a[]    要排列的数组
 * \param begin  要排列的起始位置
 * \param end    要排列的结束位置
 */
void bubble(Item a[], int begin, int end){
    int i, j;
    for(i = begin; i <end; i++)
        for(j = end; j > i; j--)
            compexch(a[j-1], a[j]);
}

/*!
 * \brief        插入排序
 *
 * \param a[]    要排列的数组
 * \param begin  要排列的起始位置
 * \param end    要排列的结束位置
 */
void insertion(Item a[], int begin, int end){
    int i;
    for(i = end; i > begin; i--)
        compexch(a[i-1], a[i]);
    for(i = begin + 2; i <= end; i++){
        int j = i;
        Item v = a[i];
        while(less(v, a[j-1])){
            a[j] = a[j-1];
            j--;
        }
        a[j] = v;
    }
}

/*!
 * \brief        希尔排序 
 *
 * \param a[]    要排列的数组
 * \param begin  要排列的起始位置
 * \param end    要排列的结束位置
 */
void shellsort(Item a[], int begin, int end){
    int i, j, h;
    for(h = begin; h <= (end-1)/STEP; h = 3 * h + 1);
    for(; h > 0; h /= 3)
        for(i = begin + h; i <= end; i++){
            int j = i;
            Item v = a[i];
            while(j >= begin + h && less(v, a[j - h])){
                a[j] = a[j-h];
                j -= h;
            }
            a[j] = v;
        }
}
