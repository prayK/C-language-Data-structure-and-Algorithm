/*******************************尾插法构建链表**********************************/
#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"

struct node
{
    int data;
    struct node *next;
};

int main()
{
    struct node *p = (struct node *)malloc(sizeof(struct node)); //创建头节点
    p->data = 20;
    struct node *head = p; //创建指向链表尾部的指针
    for (int i = 1; i <= 3; i++)
    {
        struct node *q = (struct node *)malloc(sizeof(struct node)); //新节点
        q->data = (i + 2) * 10;
        p->next = q;
        p = q; //尾指针迭代
    }
    p->next = NULL;
    printf("链表的头指针的值是：%#X\n", head);
    printf("链表节点的地址：");
    for (struct node *p = head; p != NULL; p = p->next) //遍历链表，输出每个节点的地址
    {
        printf("%#X   ", p);
    }
    printf("\n");
    printf("链表节点的内容：");
    for (struct node *p = head; p != NULL; p = p->next) //遍历链表，输出每个节点的值
    {
        printf("%d:%#X   ", p->data, p->next);
    }
    printf("\n");
    return 0;
}
/*******************************尾插法构建链表**********************************/

/*******************************尾插法构建链表**********************************/
#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"

typedef int ElemType;

struct node
{
    ElemType data;
    struct node *next;
};

typedef struct node *Node;

Node CreateLinkList(int n)
{
    Node head = (Node)malloc(sizeof(Node)); //创建头节点
    head->data = 20;
    Node p = head; //创建一个指向尾结点的节点

    for (int i = 1; i <= n; i++)
    {
        Node q = (Node)malloc(sizeof(Node));
        q->data = (i + 2) * 10;
        p->next = q;
        p = q;
    }
    p->next = NULL;

    return head;
}

int main()
{
    Node node = CreateLinkList(3);
    printf("链表节点的地址:");

    for (Node node1 = node; node1 != NULL; node1 = node1->next)
    {
        printf("%#X   ", node1);
    }

    printf("\n");
    printf("链表节点的内容:");

    for (Node node2 = node; node2 != NULL; node2 = node2->next)
    {
        printf("%d:%#X  ", node2->data, node2->next);
    }
    printf("\n");
    free(node);
    return 0;
}
/*******************************尾插法构建链表**********************************/