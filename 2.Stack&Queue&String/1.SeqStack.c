#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 15

typedef int ElemType;

struct S_SeqStack
{
    ElemType data[MAXSIZE];
    int top; //栈顶
};

typedef struct S_SeqStack *SeqStack;

//进栈
int SeqStackPush(SeqStack L, ElemType e)
{
    if (L->top == MAXSIZE - 1)
    {
        printf("堆栈满");
        return 0;
    }
    L->top++;
    L->data[L->top] = e;
    return 1;
}

//出栈
int SeqStackPop(SeqStack S, ElemType *e)
{
    if (S->top == -1)
    {
        printf("堆栈空");
        return 0;
    }
    *e = S->data[S->top];
    S->top--;

    return 1;
}

int main()
{
    SeqStack Stack = (SeqStack)malloc(sizeof(SeqStack));
    Stack->top = -1; //初始化栈顶位置在-1

    for (int i = 0; i < MAXSIZE; i++)
    {
        SeqStackPush(Stack, i);
    }

    ElemType Array[MAXSIZE];
    for (int i = 0; i < MAXSIZE; i++)
    {
        SeqStackPop(Stack, &Array[i]);
        printf("%d ", Array[i]);
    }
    printf("\n");

    free(Stack);
    return 0;
}