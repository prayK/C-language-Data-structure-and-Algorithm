#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
#define MAXSIZE 100

struct S_SeqQueue
{
    ElemType Data[MAXSIZE];
    int Front;
    int Rear;
};
typedef struct S_SeqQueue *SeqQueue;

void EnQueue(SeqQueue Queue, ElemType e)
{
    if (Queue->Rear == MAXSIZE) //如果队列满了
    {
        return 0;
    }
    Queue->Data[Queue->Rear] = e;
    Queue->Rear++;
}

void DeQueue(SeqQueue Queue, ElemType *e)
{
    //如果 front==rear，表示队列为空
    if (Queue->Front != Queue->Rear)
    {
        *e = Queue->Data[Queue->Front];
        Queue->Front++;
    }
    else
    {
        printf("队列满\n");
    }
}

int main()
{
    SeqQueue Queue = (SeqQueue)malloc(sizeof(struct S_SeqQueue));

    //设置队头指针和队尾指针，当队列中没有元素时，队头和队尾指向同一块地址
    Queue->Front = Queue->Rear = 0;

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