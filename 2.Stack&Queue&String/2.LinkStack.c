#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

struct Node
{
    ElemType data;
    struct Node *next;
};
typedef struct Node *LinkStack;

void LinkStack_Push(LinkStack *Stack, ElemType e)
{
    LinkStack p = (LinkStack)malloc(sizeof(struct Node));
    p->data = e;
    p->next = (*Stack);

    (*Stack) = p;
}

void LinkStack_Pop(LinkStack *Stack, ElemType *e)
{
    if ((*Stack) != NULL)
    {
        *e = (*Stack)->data;
        (*Stack) = (*Stack)->next;
    }
    else
    {
        printf("Stack is Empty!");
    }
}

int main()
{
    LinkStack List = NULL;
    for (int i = 0; i < 5; i++)
    {
        LinkStack_Push(&List, i);
        printf("%d ", i);
    }
    printf("\n");

    ElemType Array[5] = {0};
    for (int i = 0; i < 5; i++)
    {
        LinkStack_Pop(&List, &Array[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", Array[i]);
    }

    return 0;
}