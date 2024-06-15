#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

//��������
//C99�У��ṹ���е����һ��Ԫ��������δ֪��С�����飬��ͽ���[��������]��Ա

struct St
{
    int i;
    int arr[];     //���������Ա
};

       // ����������ص�
// 1.�ṹ���е����������Աǰ�����������һ��������Ա
// 2.sizeof���ص����ֽṹ���С����������������ڴ�
// 3.�������������Ա�Ľṹ����malloc���������ڴ�Ķ�̬���䣬���ҷ�����ڴ�Ӧ�ô��ڽṹ��Ĵ�С������Ӧ���������Ԥ�ڴ�С
int main()
{
    int sz = sizeof(struct St);
    printf("%d ", sz); //4

    //���������ʹ��
    //struct St s;  //������ʹ�ã����ٵĿռ�̶�Ϊ4
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
           //�Ա��������飬��ָ��ķ�ʽҪ���������ڴ棬�����ڷ����ٶȺ��ڴ��ͷţ������ڴ���Ƭ