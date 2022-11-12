/*********************朴素模式匹配算法**********************/
#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"

#define MAXLEN 255 //预定义最大串长为255

struct S_String
{
    char ch[MAXLEN]; //每个分量存储一个字符
    int length;      //串的实际长度
};

typedef struct S_String String;

//在主串中找到与模式串相同的子串，并返回其所在位置
int SimpleStringIndex(String S, String T)
{
    int k = 0; //记录当前匹配的子串到底是从哪开始的
    int i = k;
    int j = 0;

    while ((i < S.length) && (j < T.length))
    {
        if (S.ch[i] == T.ch[j])
        {
            ++i;
            ++j; //继续比较后续字符
        }
        else
        {
            k++; //检查下一个子串
            i = k;
            j = 0;
        }
    }
    if (j >= T.length)
    {
        return (k + 1); //这种匹配方法是数组形式，所以下标加一
    }

    else
    {
        return 0;
    }
}

//朴素模式匹配测试
int main()
{
    String S1;
    String S2;

    char String1[] = "llo";
    char String2[] = "llo";

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

    printf("%d\n", SimpleStringIndex(S1, S2));

    return 0;
}
