#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

//柔性数组
//C99中，结构体中的最后一个元素允许是未知大小的数组，这就叫做[柔性数组]成员

struct St
{
    int i;
    int arr[];     //柔性数组成员
};

       // 柔性数组的特点
// 1.结构体中的柔性数组成员前面必须至少有一个其它成员
// 2.sizeof返回的这种结构体大小不包括柔性数组的内存
// 3.包含柔性数组成员的结构体用malloc函数进行内存的动态分配，并且分配的内存应该大于结构体的大小，以适应柔性数组的预期大小
int main()
{
    int sz = sizeof(struct St);
    printf("%d ", sz); //4

    //柔性数组的使用
    //struct St s;  //不这样使用，开辟的空间固定为4
    struct St* Pst = (struct St*)malloc(sizeof(struct St) + 40);
    if (Pst == NULL)
    {
        printf("%s", strerror(errno));
        return 1;
    }
    Pst->i = 100;
    int i;
    for (i = 0; i < 10;i++)
    {
        Pst->arr[i] = i;
    }
    for (i = 0; i < 10; i++)
    {
        printf("%d ", Pst->arr[i]);
    }
    struct St* Pst1 = (struct St*)realloc(Pst, sizeof(struct St) + 80);
    if (Pst1 != NULL)
    {
        Pst = Pst1;
    }
    free(Pst);
    Pst = NULL;
    return 0;
}

struct S
{
    int n;
    int* arr;
};
int main()
{
    struct S* p = (struct S*)malloc(sizeof(struct S));
    if (p == NULL)
    {
        printf("%s", strerror(errno));
        return 1;
    }
    p->n = 100;
    p->arr = malloc(40);
    int i;
    for (i = 0; i < 10; i++)
    {
        p->arr[i] = i;
    }
    for (i = 0; i < 10; i++)
    {
        printf("%d ", p->arr[i]);
    }
    int* ptr = (int *)realloc(p->arr, 80);
    if (ptr != NULL)
    {
        p->arr = ptr;
    }
    free(p->arr);
    free(p);
    p = NULL;
    return 0;
}  
           //对比柔性数组，用指针的方式要开辟两次内存，不利于访问速度和内存释放，增加内存碎片