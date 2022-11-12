#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10

typedef int ElemType;

struct S_SeqQueue
{
    ElemType Data[MAXSIZE];
    int Front;
    int Rear;
};

typedef struct S_SeqQueue *SeqQueue;

//初始化队列
void InitQueue(SeqQueue Queue)
{
    Queue->Front = 0;
    Queue->Rear = 0;
}

//循环队列的队列长度
int QueueLength(SeqQueue Queue)
{
    return (Queue->Rear - Queue->Front + MAXSIZE) % MAXSIZE;
}

//循环队列的入队列操作
void EnQueue(SeqQueue Queue, ElemType e)
{
    if ((Queue->Rear + 1) % MAXSIZE == Queue->Front) //队列满了
    {
        printf("Full Queue!\n");
    }
    Queue->Data[Queue->Rear] = e;              //将e赋值给队尾
    Queue->Rear = (Queue->Rear + 1) % MAXSIZE; //rear指针向后移动一位，若在最后则转到数组头部
}

//循环队列出队操作
void DeQueue(SeqQueue Queue, ElemType *e)
{
    if (Queue->Front == Queue->Rear) //队列为空
    {
        printf("Empty Queue!\n");
    }

    *e = Queue->Data[Queue->Front];
    Queue->Front = (Queue->Front + 1) % MAXSIZE; //front指针向后移动一位，若在最后则转到数组头部
}

int main()
{
    SeqQueue Queue = (SeqQueue)malloc(sizeof(SeqQueue));

    InitQueue(Queue);

    for (int i = 0; i < 5; i++)
    {
        EnQueue(Queue, i);
    }
    ElemType Array[5] = {0};
    for (int i = 0; i < 5; i++)
    {
        DeQueue(Queue, &Array[i]);
        printf("%d ", Array[i]);
    }
    printf("\n");

    free(Queue);

    return 0;
}
