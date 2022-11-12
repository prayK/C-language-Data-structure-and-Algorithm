#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 30

typedef char ElemType;
struct S_SeqStack
{
    ElemType data[MAXSIZE];
    int top;
};
typedef struct S_SeqStack *SeqStack;

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

int isNumber(char c)
{
    return (('0' <= c) && (c <= '9'));
}

int isOperator(char c)
{
    return ((c == '+') || (c == '-') || (c == '*') || (c == '/'));
}

int isLeft(char c)
{
    return (c == '(');
}

int isRight(char c)
{
    return (c == ')');
}

int priority(char c)
{
    int ret = 0;
    if ((c == '+') || (c == '-'))
    {
        ret = 1;
    }

    if ((c == '*') || (c == '/'))
    {
        ret = 2;
    }
    return ret;
}

int express(int left, int right, char op)
{
    int ret = 0;
    switch (op)
    {
    case '+':
        ret = left + right;
        break;
    case '-':
        ret = left - right;
        break;
    case '*':
        ret = left * right;
        break;
    case '/':
        ret = left / right;
        break;
    default:
        break;
    }

    return ret;
}

void output(char c)
{
    if (c != '\0')
    {
        printf("%c", c);
    }
}

int CharToValue(char c)
{
    return (c - '0');
}

int ValueToChar(int v)
{
    return (v + '0');
}

//将中缀表达式转为后缀表达式
void transform(const char *exp, char *Result)
{
    SeqStack SymbolStack = (SeqStack)malloc(sizeof(struct S_SeqStack));
    char c = '0';
    int i = 0;
    SymbolStack->top = -1;
    int j = 0;

    //遍历表达式
    while (exp[i] != '\0')
    {
        //数字
        if (isNumber(exp[i]))
        {
            Result[j++] = exp[i];
        }
        else if (isOperator(exp[i]))
        {
            if (SymbolStack->top == -1)
            {
                SeqStackPush(SymbolStack, exp[i]);
            }
            else
            {
                //操作符优先级判断
                while (priority(exp[i]) <= priority(SymbolStack->data[SymbolStack->top]))
                {
                    SeqStackPop(SymbolStack, &c);
                    Result[j++] = c;
                }
                //当前操作符的优先级大于栈顶符号就直接入栈
                SeqStackPush(SymbolStack, exp[i]);
            }
        }
        //左括号直接入栈
        else if (isLeft(exp[i]))
        {
            SeqStackPush(SymbolStack, exp[i]);
        }
        else if (isRight(exp[i]))
        {
            while (isLeft(SymbolStack->data[SymbolStack->top]) == 0)
            {
                SeqStackPop(SymbolStack, &c);
                Result[j++] = c;
            }
            SeqStackPop(SymbolStack, &c); //还要把'('弹栈出去
        }
        else
        {
            printf("Invalid expression!");
            break;
        }
        i++;
    }

    while ((SymbolStack->top != -1) && (exp[i] == '\0'))
    {
        SeqStackPop(SymbolStack, &c);
        Result[j++] = c;
    }
    free(SymbolStack);
}

//根据中缀表达式计算最后结果
int Calculate(const char *exp)
{
    SeqStack Stack = (SeqStack)malloc(sizeof(struct S_SeqStack));
    Stack->top = -1;
    int i = 0;

    char Pop_RightNumber = '0';
    char Pop_LeftNumber = '0';
    char Pop_FinalResult = '0';

    int RightNumber = 0;
    int LeftNumber = 0;
    int FinalResult = 0;

    while (exp[i] != '\0')
    {
        if (isNumber(exp[i]))
        {
            SeqStackPush(Stack, exp[i]);
        }
        else if (isOperator(exp[i]))
        {
            //弹出右操作字符,将右操作字符转换为数字
            SeqStackPop(Stack, &Pop_RightNumber);
            RightNumber = CharToValue(Pop_RightNumber);

            //弹出左操作字符,将左操作字符转换为数字
            SeqStackPop(Stack, &Pop_LeftNumber);
            LeftNumber = CharToValue(Pop_LeftNumber);

            int Result = express(LeftNumber, RightNumber, exp[i]);
            char Push_Result = ValueToChar(Result); //将结果数字转换为字符压栈

            SeqStackPush(Stack, Push_Result);
        }
        else
        {
            printf("Invalid expression1!\n");
            break;
        }
        i++;
    }
    if ((Stack->top == 0) && (exp[i] == '\0'))
    {
        //将字符结果转换为数字输出
        SeqStackPop(Stack, &Pop_FinalResult);
        FinalResult = CharToValue(Pop_FinalResult);
    }
    else
    {
        printf("Invalid expression2\n");
    }

    free(Stack);

    return FinalResult;
}

int main(void)
{
    char Source[MAXSIZE] = "9+(3-1)*3+8/2+6"; //9+(3-1)*3+8/2
    char Result[MAXSIZE] = "0";               //931-3*+82/+6+

    transform(Source, Result);
    /*
    for (int i = 0; i < MAXSIZE; i++)
    {
        printf("%c", Result[i]);
    }
    printf("\n");
*/
    printf("%s = %d\n", Source, Calculate("931-3*+82/+6+"));

    return 0;
}

/*************************不用特地构造栈数据结构********************************/
/*
struct S_SymbolStack
{
    char str[20];
    int top = -1;
};

using SymbolStack = struct S_SymbolStack;

void Transform(const char *exp, char *Result)
{
    unsigned int i = 0;
    unsigned int j = 0;

    SymbolStack Stack;

    while (exp[i] != '\0')
    {
        if (isNumber(exp[i]))
        {
            Result[j++] = exp[i];
        }
        else if (isOperator(exp[i]))
        {
            if (Stack.top == -1)
            {
                Stack.str[++Stack.top] = exp[i];
            }
            else
            {
                while (Priority(exp[i]) <= Priority(Stack.str[Stack.top]))
                {
                    Result[j++] = Stack.str[Stack.top--];
                }
                Stack.str[++Stack.top] = exp[i];
            }
        }
        else if (isLeft(exp[i]))
        {
            Stack.str[++Stack.top] = exp[i];
        }
        else if (iSRight(exp[i]))
        {
            while (isLeft(Stack.str[Stack.top]) == false)
            {
                cout << Stack.str[Stack.top] << endl;
                Result[j++] = Stack.str[Stack.top--];
            }
            Stack.str[Stack.top--];
        }
        else
        {
            cout << "ERROR" << endl;
            break;
        }
        ++i;
    }
    while ((Stack.top != -1) && (exp[i] == '\0'))
    {
        Result[j++] = Stack.str[Stack.top--];
    }
}
*/
/*************************不用特地构造栈数据结构********************************/
