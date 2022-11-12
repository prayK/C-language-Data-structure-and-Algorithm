#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAXSIZE 5
typedef int ElemType;

struct SeqList
{
    ElemType data[MAXSIZE];
    int length;
};

//初始化操作，建立一个空的线性表List
int InitSeqList(struct SeqList *List, int length)
{
    if (length <= MAXSIZE)
    {
        List->length = length;
        for (int i = 0; i < length; i++)
        {
            List->data[i] = 0;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

//返回线性表List的元素个数
int ListLength(struct SeqList *List)
{
    return List->length;
}

//判断线性表List是否为空
int ListEmpty(struct SeqList *List)
{
    if (List->length == 0)
    {
        return 1;
    }
    return 0;
}

//将线性表List清空
void ClearList(struct SeqList *List)
{
    for (int i = 0; i < List->length; i++)
    {
        List->data[i] = 0;
    }
    List->length = 0;
}

//将线性表List中的第index个元素值返回给e
int GetElem(struct SeqList *List, int index, ElemType *e)
{
    if ((index < 1) || (index > List->length + 1) || (List->length == 0))
    {
        return 0;
    }
    else
    {
        *e = List->data[index - 1];
        return 1;
    }
}

//在线性表中查找与给定值e相等的元素，如果查找成功，返回该元素在表中的序号,失败返回-1
int LocateElem(struct SeqList *List, ElemType e)
{
    for (int i = 0; i < List->length; i++)
    {
        if (List->data[i] = e)
        {
            return i + 1;
        }
        else
        {
            return -1;
        }
    }
}

//在线性表List中的第index个位置插入新元素e
int ListInsert(struct SeqList *List, int index, ElemType e)
{
    if ((index < 1) || (index > MAXSIZE) || (List->length == MAXSIZE))
    {
        return 0;
    }
    else
    {
        //for (unsigned int i = List->length; i > index - 1; --i)
        for (int i = index; i < List->length + 1; i++)
        {
            List->data[i] = List->data[i - 1]; //挪出一个空间给插入的值
        }
        List->data[index - 1] = e;
        List->length++;
        return 1;
    }
}

//删除线性表List中第index个位置的元素，并用e返回其值
int ListDelete(struct SeqList *List, int index, ElemType *e)
{
    if ((index < 1) || (index > List->length) || (List->length == 0)) //循环删除的话就有问题
    {
        return 0;
    }
    *e = List->data[index - 1];
    if (index < List->length) //如果删除的不是最后一位
    {
        for (int i = index; i < List->length; i++)
        {
            List->data[i - 1] = List->data[i];
        }
    }
    List->length--;
    return 1;
}

int main(void)
{
    int length = 3;
    struct SeqList *List = (struct SeqList *)malloc(sizeof(struct SeqList));

    if (List != NULL)
    {
        if (InitSeqList(List, length) == 1)
        {
            for (int i = 0; i < length; i++)
            {
                printf("%d ", List->data[i]);
            }
            printf("\n");
        }
    }

    printf("该线性表中含有%d个元素\n", ListLength(List));
    printf("该线性表为空是否为空：%d\n", ListEmpty(List));

    ClearList(List); //将顺序表清空
    printf("该线性表中含有%d个元素\n", ListLength(List));
    printf("该线性表为空是否为空：%d\n", ListEmpty(List));

    for (int i = 1; i < 3; i++)
    {
        ListInsert(List, i, i * 3);
    }
    printf("该线性表中含有%d个元素\n", ListLength(List));
    printf("该线性表为空是否为空：%d\n", ListEmpty(List));

    int a[3] = {0, 0, 0};
    GetElem(List, 1, &a[0]);
    GetElem(List, 2, &a[1]);

    for (int i = 0; i < 2; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    printf("该线性表中含有%d个元素\n", ListLength(List));
    printf("该线性表为空是否为空：%d\n", ListEmpty(List));

    ListDelete(List, 1, &a[0]);
    ListDelete(List, 1, &a[1]);

    for (int i = 0; i < 2; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    printf("该线性表中含有%d个元素\n", ListLength(List));
    printf("该线性表为空是否为空：%d\n", ListEmpty(List));

    free(List);

    return 0;
}