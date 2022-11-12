#include <stdio.h>
#include <malloc.h>

typedef int ElemType;

//节点结构体
struct Node
{
    ElemType data;     //数据域
    struct Node *next; //指针域
};

typedef struct Node *QueueNode;

//队列的链表结构
struct S_LinkQueue
{
    QueueNode front; //队头指针
    QueueNode rear;  //队尾指针
};

typedef struct S_LinkQueue *LinkQueue;

//队列初始化
void QueueInit(LinkQueue *Queue)
{
    QueueNode p = (QueueNode)malloc(sizeof(struct Node)); //构建头结点
    p->next = NULL;                                       //头结点初始化指向为空
    (*Queue)->front = (*Queue)->rear = p;                 //初始化队列头尾指针指向为头结点
}

//插入元素e为Q的新的队尾节点(链式队列不用判断队列满的情况~~~~~~~~~~~~)
int EnLinkQueue(LinkQueue Queue, ElemType e)
{
    QueueNode node = (QueueNode)malloc(sizeof(struct Node));

    if (node == NULL)
    {
        return 0;
    }
    node->data = e;
    node->next = NULL;

    Queue->rear->next = node; //把拥有元素e的新节点s赋值给原队尾节点的后继(注意点~~~~~~~~~~~~~~~~~)
    Queue->rear = node;       //把当前的s设置为队尾节点，rear指向s

    return 1;
}

//若队列不空，删除Q的队头元素，用e返回其值
int DeLinkQueue(LinkQueue Queue, ElemType *e)
{
    if (Queue->front == Queue->rear) //队列满
    {
        return 0;
    }
    QueueNode p = (QueueNode)malloc(sizeof(struct Node));
    p = Queue->front->next; //将要删除的队头节点暂存给P(注意在链队列中，头节点不存储数据)
    *e = p->data;           //将要删除的队头节点的值赋值给e;

    Queue->front->next = p->next; //将待删除节点后继p->next赋值给头节点后继

    if (Queue->rear == p)
    {
        Queue->rear = Queue->front; //若队头是队尾，则删除后将rear指向头节点(注意点~~~~~~~~~~~~~~)
    }

    free(p);

    return 1;
}

int main()
{
    LinkQueue Queue = (LinkQueue)malloc(sizeof(struct S_LinkQueue)); //创建队列
    QueueInit(&Queue);                                               //初始化队列

    for (int i = 0; i < 5; i++)
    {
        EnLinkQueue(Queue, i);
    }

    ElemType Array[5] = {0};
    for (int i = 0; i < 5; i++)
    {
        DeLinkQueue(Queue, &Array[i]);
        printf("%d ", Array[i]);
    }
    printf("\n");

    free(Queue);

    return 0;
}
