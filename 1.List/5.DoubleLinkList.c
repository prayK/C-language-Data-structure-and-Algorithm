#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"

typedef int ElemType;

struct Node
{
    ElemType data;
    struct Node *prior;
    struct Node *next;
};
typedef struct Node *LinkList;

void Rear_CreateLinkList(LinkList *List, int n)
{
    (*List) = (LinkList)malloc(sizeof(struct Node));
    (*List)->data = 1;
    (*List)->prior = NULL;
    (*List)->next = NULL;
    LinkList L = *List;

    for (int i = 2; i < 2 + n; i++)
    {
        LinkList p = (LinkList)malloc(sizeof(struct Node));
        p->data = i;
        L->next = p; //新节点与链表最后一个节点建立连接
        p->prior = L;
        L = p;
    }
    L->next = NULL;
}

int ListInsert(LinkList List, int index, ElemType e)
{
    LinkList temp = List;
    int j = 1;

    while ((temp != NULL) && j < index)
    {
        temp = temp->next;
        ++j;
    }
    if ((temp == NULL) || j > index)
    {
        return 0;
    }
    else
    {
        LinkList q = (LinkList)malloc(sizeof(struct Node)); //生成新的节点
        q->data = e;
        q->next = temp->next;
        q->prior = temp;
        temp->next->prior = s;
        temp->next = s;

        /*
        //完成与后一个节点的连接关系
        temp->next->prior = q;
        q->next = temp->next; //修改插入节点的后继
        //完成前一个节点的连接关系
        temp->next = q;
        q->prior = temp;
        */
    }
    return 1;
}

int ListDelete(LinkList List, int index, ElemType *e)
{
    LinkList temp = List;
    int j = 1;

    while ((temp->next != NULL) && (j < index))
    {
        temp = temp->next;
        ++j;
    }

    if ((temp->next == NULL) || j > index)
    {
        return 0;
    }
    else
    {
        LinkList q = (LinkList)malloc(sizeof(struct Node));
        q = temp->next;
        q->prior->next = q->next;
        q->next->prior = q->prior;
        free(q);
        return 1;
    }
}

void Display(LinkList List)
{
    LinkList Temp = List;
    while (Temp != NULL)
    {
        if (Temp->next == NULL)
        {
            printf("%d\n", Temp->data);
        }
        else
        {
            printf("%d <-> ", Temp->data);
        }
        Temp = Temp->next;
    }
}

int main()
{
    LinkList List = NULL;
    Rear_CreateLinkList(&List, 5);
    Display(List);

    int a = 0;
    ListDelete(List, 3, &a);
    Display(List);

    ListInsert(List, 3, 9);
    Display(List);

    free(List);
    return 0;
}