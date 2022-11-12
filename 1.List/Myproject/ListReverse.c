/********************************四种算法实现单链表的反转****************************/
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
    (*List)->data = 1;                               //头节点的数据域存储链表的长度信息
    (*List)->next = NULL;                            //头结点指针域
    LinkList L = *List;                              //申明一个指向尾节点的变量(当前尾结点就是头结点)

    for (int i = 2; i < 2 + n; i++)
    {
        LinkList p = (LinkList)malloc(sizeof(struct Node)); //生成新节点
        p->data = i;
        L->next = p; //将尾节点的指针指向新节点(第一次执行这一步时，头结点就是尾结点)
        L = p;       //将当前的新节点定义为表尾终端节点(当前的新节点就是尾结点)
    }
    L->next = NULL; //表示当前列表结束(最终尾结点指向NULL)
}

//迭代反转法
LinkList iteration_reverse(LinkList head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    else
    {
        LinkList beg = NULL; //初始化为NULL
        LinkList mid = head;
        LinkList end = head->next;
        //一直遍历
        while (1)
        {
            //修改 mid 所指节点的指向
            mid->next = beg;
            //此时判断 end 是否为 NULL，如果成立则退出循环
            if (end == NULL)
            {
                break;
            }
            //整体向后移动 3 个指针
            beg = mid;
            mid = end;
            end = end->next;
        }
        //最后修改 head 头指针的指向
        head = mid;
        return head;
    }
}

//递归反转法
LinkList recursive_reverse(LinkList head)
{
    //递归的出口
    if (head == NULL || head->next == NULL) // 空链或只有一个结点，直接返回头指针
    {
        return head;
    }
    else
    {
        //一直递归，找到链表中最后一个节点（其实倒数第二个节点传进去的时候递归就到底了）
        LinkList new_head = recursive_reverse(head->next);
        //当逐层退出时，new_head 的指向都不变，一直指向原链表中最后一个节点；
        //递归每退出一层，函数中 head 指针的指向都会发生改变，都指向上一个节点。
        //每退出一层，都需要改变 head->next 节点指针域的指向，同时令 head 所指节点的指针域为 NULL。
        head->next->next = head;
        head->next = NULL;
        //每一层递归结束，都要将新的头指针返回给上一层。由此，即可保证整个递归过程中，能够一直找得到新链表的表头。
        return new_head;
    }
}

//头插法
LinkList head_reverse(LinkList head)
{
    LinkList new_head = NULL;
    LinkList temp = NULL;
    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    while (head != NULL)
    {
        temp = head;
        //将 temp 从 head 中摘除
        head = head->next;
        //将 temp 插入到 new_head 的头部
        temp->next = new_head;
        new_head = temp;
    }

    return new_head;
}

//就地逆置法
LinkList local_reverse(LinkList head)
{
    LinkList beg = head;
    LinkList end = head->next;
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    while (end != NULL)
    {
        //将 end 从链表中摘除
        beg->next = end->next;
        //将 end 移动至链表头
        end->next = head;
        head = end;
        //调整 end 的指向，另其指向 beg 后的一个节点，为反转下一个节点做准备
        end = beg->next;
    }
    return head;
}

int main(void)
{
    LinkList List1 = NULL;
    LinkList List2 = NULL;

    Rear_CreateLinkList(&List1, 5);
    //List2 = iteration_reverse(List1);
    //List2 = recursive_reverse(List1);
    List2 = head_reverse(List1);
    //List2 = local_reverse(List1);
    for (; List2 != NULL; List2 = List2->next)
    {
        printf("%d ", List2->data);
    }

    free(List1);
    free(List2);

    return 0;
}
/********************************四种算法实现单链表的反转****************************/