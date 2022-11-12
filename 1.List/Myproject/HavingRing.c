/********************************判断单链表是否有环*********************************/
#include "stdio.h"
#include "stdlib.h"

typedef int ElemType;

struct Node
{
    ElemType data;
    struct Node *next;
    int length;
};
typedef struct Node *LinkList;

/*尾插法创建单链表，新的节点始终在最后*/
void Rear_CreateLinkList(LinkList *List, int n)
{
    (*List) = (LinkList)malloc(sizeof(struct Node));
    (*List)->length = n;
    (*List)->data = 1;
    (*List)->next = NULL;
    LinkList L = *List;

    for (int i = 2; i <= n; i++)
    {
        LinkList p = (LinkList)malloc(sizeof(struct Node));
        p->data = i;
        L->next = p;
        L = p;
    }
    L->next = *List; //把这里改为NULL，就无环了
}

//判断单链表是否有环(方法一)，0表无环，1表有环
int HaveRing_Solution1(LinkList List)
{
    LinkList Htemp = List;
    //存储所遍历节点所有前驱节点的存储地址，64位环境下地址占 8 个字节，所以这里用 long long 类型
    LinkList addr[20] = {0};
    int length = 0, i = 0;
    //逐个遍历链表中各个节点
    while (Htemp != NULL)
    {
        //依次将 Htemp 和 addr 数组中记录的已遍历的地址进行比对
        for (i = 0; i < length; i++)
        {
            //如果比对成功，则证明有环
            if (Htemp == addr[i])
            {
                return 1;
            }
        }
        //比对不成功，则记录 Htemp 节点的存储地址
        addr[length] = Htemp;
        //printf("%p, %p\n", addr[length], Htemp);
        length++;
        Htemp = Htemp->next;
    }
    return 0;
}

//判断单链表是否有环(方法二)，0表无环，1表有环
int HaveRing_Solution2(LinkList List)
{
    LinkList H1 = List->next;
    LinkList H2 = List;
    while (H1 != NULL)
    {
        if (H1 == H2)
        {
            return 1; //链表中有环
        }
        else
        {
            H1 = H1->next;
            if (H1 == NULL)
            {
                return 0; //链表中无环
            }
            else
            {
                H1 = H1->next;
                H2 = H2->next;
            }
        }
    }
    //链表中无环
    return 0;
}

int main()
{
    LinkList List = NULL;
    Rear_CreateLinkList(&List, 5);
    printf("%d\n", HaveRing_Solution1(List));
    //printf("%d\n", HaveRing_Solution2(List));

    free(List);
    return 0;
}

/********************************判断单链表是否有环*********************************/