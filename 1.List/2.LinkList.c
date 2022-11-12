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

/*头插法创建单链表，新的节点始终在第一个位置*/
void Head_CreateLinkList(LinkList *List, int n)
{
    (*List) = (LinkList)malloc(sizeof(struct Node)); //创建头结点，头指针指向头结点
    (*List)->data = n;                               //头节点的数据域存储链表的长度信息
    (*List)->next = NULL;                            //头结点指针域

    for (int i = 0; i < n; i++)
    {
        LinkList p = (LinkList)malloc(sizeof(struct Node)); //生成新节点
        p->data = i;
        p->next = (*List)->next;
        (*List)->next = p;
    }
}

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

//非二重指针法创建单链表
LinkList CreateLinkList(int n)
{
    LinkList HeadNode = (LinkList)malloc(sizeof(struct Node)); //创建头结点，头指针指向头结点
    HeadNode->data = n;                                        //头节点的数据域存储链表的长度信息
    HeadNode->next = NULL;                                     //头结点指针域
    LinkList L = HeadNode;                                     //申明一个指向尾节点的变量(当前尾结点就是头结点)
    if (HeadNode != NULL)                                      //如果创建成功
    {
        for (int i = 0; i < n; i++)
        {
            LinkList p = (LinkList)malloc(sizeof(struct Node)); //创建后继节点
            p->data = i;                                        //给后继节点的数据域赋值
            L->next = p;                                        //将尾节点的指针指向新节点(第一次执行这一步时，头结点就是尾结点)
            L = p;                                              //将当前的新节点定义为表尾终端节点(当前的新节点就是尾结点)
        }
        L->next = NULL; //表示当前列表结束(最终尾结点指向NULL)
    }

    return HeadNode;
}

//用e返回L中第i个数据元素的值
int GetElem(LinkList List, int i, ElemType *e)
{
    LinkList p = List;
    int j = 1;

    while ((j < i) && p != NULL) //遍历找
    {
        p = p->next;
        ++j;
    }
    if ((p == NULL) || j > i) //找到最后都没有找到
    {
        return 0;
    }
    else
    {
        *e = p->data;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
    }
    return 1;
}

/*在单链表中第i个位置之前插入新的数据元素e，L的长度加1(单链表的长度还没有实现)*/
int LinkListInsert(LinkList L, int i, ElemType e)
{
    LinkList p = L;
    int j = 1;

    while ((p != NULL) && j < i) //寻找第i个节点
    {
        p = p->next;
        ++j;
    }
    if ((p == NULL) || j > i) //找不到,那就直接插在结尾吧或者直接返回0(这里返回0)
    {
        return 0;
    }
    else
    {
        LinkList s = (LinkList)malloc(sizeof(struct Node)); //生成新的节点
        s->data = e;
        s->next = p->next;
        p->next = s;
    }
    return 1;
}

/*删除单链表的第i个数据元素，并用e返回其值，L的长度减1(单链表的长度还没有实现)*/
int LinkListDelete(LinkList L, int i, ElemType *e)
{
    LinkList p = L;
    int j = 1;

    while ((p->next != NULL) && (j < i)) //注意，我们找到的是要删除的节点的前驱节点，最后p是前驱
    {
        p = p->next;
        ++j;
    }

    if ((p->next == NULL) || j > i) //找到最后都没有找到
    {
        return 0;
    }
    /*
    else
    {
        //p是待删除节点的前一个节点，我们需要构建一个临时节点q，把待删除节点的指针域保存下来，p->next中存的就是
        //待删除节点的地址(存在q中)，然后q->next中存的就是待删除节点下一个节点的地址，要保存在p->next中
        LinkList q = (LinkList)malloc(sizeof(struct Node)); //需要一个节点q去暂存待删除节点的后继
        q = p->next;                                        //将待删除节点的地址给q暂存
        p->next = q->next;                                  //链接删除节点两端的节点
        *e = q->data;                                       //将删除的节点的值取出
        free(q);                                            //回收这个节点
        return 1;
    }
    */

    else
    {
        *e = (p->next)->data;
        //struct Node *temp = p->next->next;
        p->next = p->next->next;
        return 1;
    }
}

/*单链表已经存在，要将单链表置空*/
int LinkListClear(LinkList L)
{
    LinkList p = L->next;   //指向第一个节点
    while (p->next != NULL) //循环到表尾
    {
        LinkList q = p->next;
        free(p);
        p = q;
    }
    L->next = NULL; //头结点的指针域为空
    return 1;
}

int main(void)
{
//头插法测试代码
#if 0
    LinkList List = NULL; //创建头指针

    Head_CreateLinkList(&List, 3);

    for (int i = 0; i < 4; i++)
    {
        printf("%d\n", List->data);
        List = List->next;
    }
#endif

//尾插法测试代码
#if 1
    LinkList List = NULL;
    Rear_CreateLinkList(&List, 3);

    /*
    for (int i = 0; i < 4; i++)
    {
        printf("%d ", List->data);
        List = List->next;
    } //注意循环结束时List指向空了
    */
#endif

//非二重指针法创建单链表测试代码
#if 0
    LinkList List = CreateLinkList(3);
    for (int i = 0; i < 4; i++)
    {
        printf("%d\n", List->data);
        List = List->next;
    }
#endif

//链表内获取指定位置元素值测试代码
#if 0
    ElemType a = 0;
    for (int i = 1; i < 5; i++)
    {
        if (GetElem(List, i, &a))
        {
            printf("a=%d\n", a);
        }
        else
        {
            printf("ERROR");
        }
    }
#endif

//链表插入元素测试代码
#if 0
    LinkListInsert(List, 4, 5);
    for (; List != NULL; List = List->next)
    {
        printf("%d ", List->data);
    }
    printf("\n");
#endif

//链表删除元素测试代码
#if 1
    ElemType a = 0;
    LinkListDelete(List, 3, &a);
    //printf("a=%d\n", a);
    for (int i = 0; i < 3; i++)
    {
        printf("%d ", List->data);
        List = List->next;
    }
    printf("\n");
#endif

//链表清空测试代码
#if 0
    LinkListClear(List);
    printf("%p ", List->next);

#endif

    free(List);

    return 0;
}