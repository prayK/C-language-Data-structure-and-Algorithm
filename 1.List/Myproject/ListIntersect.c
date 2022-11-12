/********************************判断两个单链表是否相交********************************/
#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"

typedef int ElemType;

struct Node
{
    ElemType data;
    struct Node *next;
};
typedef struct Node *LinkList;

/*尾插法创建单链表，新的节点始终在最后*/
void Rear_CreateLinkList(LinkList *List, int n)
{
    (*List) = (LinkList)malloc(sizeof(struct Node)); //创建头结点，头指针指向头结点
    (*List)->data = n;                               //头节点的数据域存储链表的长度信息
    (*List)->next = NULL;                            //头结点指针域
    LinkList L = *List;                              //申明一个指向尾节点的变量(当前尾结点就是头结点)

    for (int i = 0; i < n; i++)
    {
        LinkList p = (LinkList)malloc(sizeof(struct Node)); //生成新节点
        p->data = i;
        L->next = p; //将尾节点的指针指向新节点(第一次执行这一步时，头结点就是尾结点)
        L = p;       //将当前的新节点定义为表尾终端节点(当前的新节点就是尾结点)
    }
    L->next = NULL; //表示当前列表结束(最终尾结点指向NULL)
}

//判断两个单链表是否相交(方法一：遍历比较法O(n平方))(任何相交模式都适合(单点相交))
//L1 和 L2 为 2 个单链表，函数返回 1 表示链表相交，返回 0 表示不相交
int LinkIntersect_Solution1(LinkList L1, LinkList L2)
{
    LinkList p1 = L1;
    LinkList p2 = L2;
    //逐个遍历 L1 链表中的各个节点
    while (p1)
    {
        //遍历 L2 链表，针对每个 p1，依次和 p2 所指节点做比较
        while (p2)
        {
            //p1、p2 中记录的就是各个节点的存储地址，直接比较即可
            if (p1 == p2)
            {
                return 1;
            }
            p2 = p2->next;
        }
        p1 = p1->next;
    }
    return 0;
}

//判断两个单链表是否相交(方法一优化O(n))(适合从开始不相交到某点后一直相交)
//L1 和 L2 为 2 个单链表，函数返回 1 表示链表相交，返回 0 表示不相交
int LinkIntersect_Solution2(LinkList L1, LinkList L2)
{
    LinkList p1 = L1;
    LinkList p2 = L2;
    //找到 L1 链表中的最后一个节点
    while (p1->next)
    {
        p1 = p1->next;
    }
    //找到 L2 链表中的最后一个节点
    while (p2->next)
    {
        p2 = p2->next;
    }
    //判断 L1 和 L2 链表最后一个节点是否相同
    if (p1 == p2)
    {
        return 1;
    }
    return 0;
}

//判断两个单链表是否相交(方法二)(适合从开始就相交到某点后不再相交)
//L1 和 L2 为 2 个单链表，函数返回 True 表示链表相交，返回 False 表示不相交
int LinkIntersect_Solution3(LinkList L1, LinkList L2)
{
    LinkList plong = L1;
    LinkList pshort = L2;
    unsigned int num1 = 0, num2 = 0;
    //得到 L1 的长度
    while (plong)
    {
        num1++;
        plong = plong->next;
    }
    //得到 L2 的长度
    while (pshort)
    {
        num2++;
        pshort = pshort->next;
    }

    //重置plong和pshort，使plong代表较长的链表，pshort代表较短的链表
    int step = (num1 > num2) ? (num1 - num2) : (num2 - num1);
    if (num1 > num2)
    {
        plong = L1;
        pshort = L2;
    }
    else
    {
        plong = L2;
        pshort = L1;
    }
    //在plong链表中找到和pshort等长度的子链表
    LinkList temp = plong;
    while (step)
    {
        temp = temp->next;
        step--;
    }
    //逐个比较temp和pshort链表中的节点是否相同
    while (temp && pshort)
    {
        if (temp == pshort)
        {
            return 1;
        }
        temp = temp->next;
        pshort = pshort->next;
    }
    return 0;
}

int main(void)
{
    LinkList List1 = NULL;
    LinkList List2 = NULL;

    Rear_CreateLinkList(&List1, 5);
    Rear_CreateLinkList(&List2, 5);

    //if (LinkIntersect_Solution1(List1, List2))
    //if (LinkIntersect_Solution2(List1, List2))
    //if (LinkIntersect_Solution3(List2, List2))
    {
        printf("YES");
    }
    else
    {
        printf("NO");
    }

    free(List1);
    free(List2);

    return 0;
}
/********************************判断两个单链表是否相交********************************/