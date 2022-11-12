/******************************栈实现字符匹配*************************************/
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

int isLeft(char e)
{
    int ret = 0;

    switch (e)
    {
    case '<':
    case '{':
    case '[':
    case '(':
    case '\'':
    case '\"':
        ret = 1;
        break;
    default:
        ret = 0;
        break;
    }

    return ret;
}

int isRight(char e)
{
    int ret = 0;

    switch (e)
    {
    case '>':
    case '}':
    case ']':
    case ')':
    case '\'':
    case '\"':
        ret = 1;
        break;
    default:
        ret = 0;
        break;
    }

    return ret;
}

int match(char left, char right)
{
    int ret = 0;

    switch (left)
    {
    case '<':
        ret = (right == '>');
        break;
    case '{':
        ret = (right == '}');
        break;
    case '[':
        ret = (right == ']');
        break;
    case '(':
        ret = (right == ')');
        break;
    case '\'':
        ret = (right == '\'');
        break;
    case '\"':
        ret = (right == '\"');
        break;
    default:
        ret = 0;
        break;
    }
    return ret;
}

int sanner(const char *code)
{
    SeqStack Stack = (SeqStack)malloc(sizeof(SeqStack));
    int ret = 0;
    int i = 0;

    Stack->top = -1; //定义时将栈顶位置放在-1处
    while (code[i] != '\0')
    {
        if (isLeft(code[i])) //左括号压栈
        {
            SeqStackPush(Stack, code[i]);
        }
        if (isRight(code[i]))
        {
            int c;
            SeqStackPop(Stack, &c);
            if (!match(c, code[i])) //匹配不成功
            {
                printf("%c does not match!\n", code[i]);
                ret = 0;
                printf("OK");
                break;
            }
        }
        i++;
    }
    if ((Stack->top == -1) && (code[i] == '\0'))
    {
        printf("SUCCESS\n");
        ret = 1;
    }
    else
    {
        printf("Invalid code!\n");
        ret = 0;
    }
    return ret;
}

int main()
{
    const char *code = "{}()‘’{}[]";
    sanner(code);

    return 0;
}
/******************************栈实现字符匹配*************************************/
