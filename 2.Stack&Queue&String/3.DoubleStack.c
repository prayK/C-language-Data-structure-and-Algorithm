#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20

typedef int ElemType;

struct S_DoubleSeqStack
{
    ElemType data[MAXSIZE];
    int top1; //栈顶//初始化栈顶为-1
    int top2; //栈顶//初始化栈顶为MAXSIZE
};

typedef struct S_DoubleSeqStack *DoubleSeqStack;

//插入元素e为新的栈顶元素，StackNumber表示进哪个栈
int DoubleSeqStackPush(DoubleSeqStack Stack, int StackNumber, ElemType e)
{
    if (Stack->top1 + 1 == Stack->top2) //堆栈满了
    {
        printf("堆栈满");
        return 0;
    }
    if (StackNumber == 1) //栈1有元素进栈
    {
        Stack->top1++;
        Stack->data[Stack->top1] = e;
    }
    else if (StackNumber == 2)
    {
        Stack->top2--;
        Stack->data[Stack->top2] = e;
    }
}

//若栈不为空，则删除Stack的栈顶元素，用e返回其值，并返回1，否则返回0
int DoubleSeqStackPop(DoubleSeqStack Stack, int StackNumber, ElemType *e)
{
    if (StackNumber == 1) //栈1有元素进栈
    {
        if (Stack->top1 == -1)
        {
            printf("空栈");
            return 0;
        }
        *e = Stack->data[Stack->top1];
        Stack->top1--;
    }
    else if (StackNumber == 2)
    {
        if (Stack->top2 == MAXSIZE)
        {
            printf("空栈");
            return 0;
        }
        *e = Stack->data[Stack->top2];
        Stack->top2++;
    }
    return 1;
}

int main()
{
    DoubleSeqStack Stack = (DoubleSeqStack)malloc(sizeof(DoubleSeqStack));

    Stack->top1 = -1;
    Stack->top2 = MAXSIZE;

    for (int i = 0; i < MAXSIZE / 2 - 5; i++)
    {
        DoubleSeqStackPush(Stack, 1, i);
    }
    for (int i = MAXSIZE - 1; i >= MAXSIZE / 2 + 5; i--)
    {
        DoubleSeqStackPush(Stack, 2, i);
    }

    ElemType Array[MAXSIZE - 1] = {0};
    for (int i = 0; i < MAXSIZE / 2 - 5; i++)
    {
        DoubleSeqStackPop(Stack, 1, &Array[i]);
    }
    for (int i = MAXSIZE - 1; i >= MAXSIZE / 2 + 5; i--)
    {
        DoubleSeqStackPop(Stack, 2, &Array[i]);
    }
    for (int i = 0; i < MAXSIZE; i++)
    {
        printf("%d ", Array[i]);
    }
    printf("\n");

    free(Stack);
    return 0;
}