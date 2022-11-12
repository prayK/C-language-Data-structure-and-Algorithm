#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"

#define MAXLEN 255 //预定义最大串长为255

struct S_String
{
    char ch[MAXLEN];     //每个分量存储一个字符
    unsigned int length; //串的实际长度
};

typedef struct S_String String;

//求主串长
int StringLength(String S)
{
    return S.length;
}

//求子串
int SubString(String S, String *Sub, int pos, int len)
{
    //子串范围越界
    if ((pos + len - 1) > (S.length))
    {
        return 0;
    }
    for (int i = (pos - 1); i < (pos + len - 1); i++)
    {
        Sub->ch[i - (pos - 1)] = S.ch[i];
    }
    Sub->length = len;

    return 1;
}

//比较操作,若S>T,则返回值>0,若S=T，则返回值=0,若S<T，则返回值<0
int StringCompare(String S, String T)
{
    for (int i = 0; (i < S.length) && (i < T.length); i++)
    {
        if (S.ch[i] != T.ch[i])
        {
            return S.ch[i] - T.ch[i];
        }
    }
    //扫描过的所有字符都相等，则长度长的串更大
    return S.length - T.length;
}

//定位操作，若主串S中存在与串T值相同的子串，则返回它在主串S中第一次出现的位置，否则函数值为0
int StringIndex(String S, String T)
{
    int i = 1;
    int S_Len = StringLength(S); //"Hello"
    int T_Len = StringLength(T); //"llo"

    String *Sub = (String *)malloc(sizeof(String)); //用于暂存子串

    //i如果过大时，主串剩下的字符数就比子串小了，就不可能查找得到了
    while (i <= (S_Len - T_Len + 1))
    {
        SubString(S, Sub, i, T_Len);     //从头找起
        if (StringCompare(*Sub, T) != 0) //如果不一样，那就继续找
        {
            i++;
        }
        else //否则找到了
        {
            return i; //返回子串在主串中的位置
        }
    }
    return 0;
}

//子串获取测试
void Test1()
{
    String S;
    String *S2 = (String *)malloc(sizeof(struct S_String));

    S.ch[0] = 'H';
    S.ch[1] = 'e';
    S.ch[2] = 'l';
    S.ch[3] = 'l';
    S.ch[4] = 'o';

    S.length = 5;

    if (SubString(S, S2, 2, 3))
    {
        printf("%d\n", S2->length);
        for (int i = 0; i < S2->length; i++)
        {
            printf("%c", S2->ch[i]);
        }
    }
    free(S2);
}

//字符串比较测试
void Test2()
{
    String S1;
    String S2;

    char String1[] = "Hello";
    char String2[] = "Hello";

    S1.length = (sizeof(String1) - 1);
    S2.length = (sizeof(String2) - 1);

    for (int i = 0; i < (sizeof(String1) - 1); i++)
    {
        S1.ch[i] = String1[i];
    }
    for (int i = 0; i < (sizeof(String2) - 1); i++)
    {
        S2.ch[i] = String2[i];
    }

    printf("%d\n", StringCompare(S1, S2));
}

//子串检索测试
void Test3()
{
    String S1;
    String S2;

    char String1[] = "Hello";
    char String2[] = "llo";

    S1.length = (sizeof(String1) - 1);
    S2.length = (sizeof(String2) - 1);

    for (int i = 0; i < (sizeof(String1) - 1); i++)
    {
        S1.ch[i] = String1[i];
        //printf("%c ", S1.ch[i]);
    }
    for (int i = 0; i < (sizeof(String2) - 1); i++)
    {
        S2.ch[i] = String2[i];
        //printf("%c ", S2.ch[i]);
    }

    printf("%d\n", StringIndex(S1, S2));
}

int main()
{
    //Test1();
    //Test2();
    Test3();

    return 1;
}
