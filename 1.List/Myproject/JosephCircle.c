/********************************循环链表实现约瑟夫环*********************************/
#include "stdio.h"
#include "malloc.h"
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
    L->next = *List;
}

void findAndKill(LinkList List, int k, int m)
{
    LinkList p = List;
    //我们需要一个指针，指向待删除节点的上一个节点，且要一开始就指向头节点的前一个节点
    LinkList Front = List;
    while (Front->next != List)
    {
        Front = Front->next;
    }
    //找到第k个人
    while (p->data != k)
    {
        Front = p; //Front指针也要跟着移动
        p = p->next;
    }
    //从编号为k的人开始，只有符合p->next==p时，说明链表中除了p结点，所有编号都出列了，
    while (p->next != p)
    {
        //找到从p报数1开始，报m的人，并且还要知道数m-1的人的位置，方便做删除操作。
        for (int i = 1; i < m; i++)
        {
            Front = p; //Front指针也要跟着移动
            p = p->next;
        }
        Front->next = p->next; //将报m的人挪走
        printf("出列人的编号为:%d\n", p->data);
    }
    free(p);
}

int main()
{
    printf("输入圆桌上的人数n:");
    int n;
    scanf("%d", &n);

    LinkList List = NULL;
    Rear_CreateLinkList(&List, 5);
    /*
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", List->data);
        List = List->next;
    }
    printf("\n");
    */
    printf("从第k人开始报数(k>1且k<%d)：", n);
    int k;
    scanf("%d", &k);
    printf("数到m的人出列：");
    int m;
    scanf("%d", &m);
    findAndKill(List, k, m);

    free(List);
    return 0;
}
/********************************循环链表实现约瑟夫环*******************************/