#include <stdio.h>
#include <stdlib.h>

#define Elemtype int

//有序表的二分查找
struct B_List
{
    Elemtype *Data;
    int length;
};

typedef struct B_List *List;

void Creat(List *L, int length)
{
    (*L) = (List)malloc(sizeof(struct B_List));
    (*L)->length = length;
    (*L)->Data = (Elemtype *)malloc((length + 1) * sizeof(Elemtype));

    printf("输入表中的%d个数据元素：\n", length);

    //根据查找表中数据元素的总长度，在存储时，从数组下标为 1 的空间开始存储数据
    for (int i = 1; i <= length; i++)
    {
        printf("请输入第%d个数据: ", i);
        scanf("%d", &((*L)->Data[i]));
    }
}

int BinarySearch(List L, Elemtype e)
{
    int low = 1;
    int high = L->length;
    int mid = 0;

    while (low <= high)
    {
        mid = (low + high) / 2;

        if (L->Data[mid] == e)
        {
            return mid;
        }
        else if (L->Data[mid] > e)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return 0;
}

int main(void)
{
    List L = NULL;
    Creat(&L, 11);

    Elemtype e;
    printf("请输入查找数据的关键字：");
    scanf("%d", &e);
    int location = BinarySearch(L, e);

    //如果返回值为 0，则证明查找表中未查到 key 值
    if (location == 0)
    {
        printf("查找表中无该元素");
    }
    else
    {
        printf("数据在查找表中的位置为：%d", location);
    }

    return 0;
}