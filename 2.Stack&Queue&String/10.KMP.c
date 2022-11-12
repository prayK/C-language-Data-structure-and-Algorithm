/****************KMP模式匹配算法(建议模式串从1开始存)*****************/
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

//通过计算返回子串的next数组，next数组从1开始
void Get_Next(String T, int next[])
{
    int i = 1;
    int j = 0;
    next[1] = 0;

    /*
    printf("\n");
    for(int k=1; k<T.length; k++)
    {
        printf("T.ch[%d] = %c\n", k, T.ch[k]);
    }
    printf("\n");
    printf("T.length = %d\n\n", T.length);
    */
    while (i < T.length) //
    {
        if (j == 0 || (T.ch[i] == T.ch[j])) //T[i]表示后缀的单个字符，T[j]表示前缀的单个字符
        {
            ++i;
            ++j;
            next[i] = j;
        }
        else
        {
            j = next[j]; //若字符不相同，则j值回溯
        }
    }
}

//KMP算法代码
int Index_KMP(String S, String T, int next[])
{
    int i = 0;
    int j = 1;

    /*
    for(int k=0; k<S.length; k++)
    {
        printf("S.ch[%d] = %c\n", k, S.ch[k]);
    }
    printf("S.length = %d\n\n", S.length);
    for(int k=0; k<T.length; k++)
    {
        printf("T.ch[%d] = %c\n", k, T.ch[k]);
    }
    printf("T.length = %d\n\n", T.length);
    */

    while ((i < S.length) && (j < T.length))
    {
        if (j == 0 || (S.ch[i] == T.ch[j])) //与朴素算法增加了j==0判断，j==0时就要一起右移了
        {
            ++i;
            ++j; //继续比较后续字符
        }
        else //指针回退重新开始匹配
        {
            j = next[j]; //模式串向右回退到合适的位置，i值不变
        }
    }
    if (j >= T.length)
    {
        return i - T.length + 2; //匹配成功
    }
    else
    {
        return 0;
    }
}

//模式串的next测试
void Test5()
{
    String S1;
    char String1[] = "Mababaaaba"; //字符串长度为字符数目，第一位不用
    int next[9];                   //next数组与有效字符数一致就行

    S1.length = (sizeof(String1) - 1);

    for (int i = 0; i < (sizeof(String1) - 1); i++)
    {
        S1.ch[i] = String1[i];
        printf("%c ", S1.ch[i]);
    }
    printf("\n");

    Get_Next(S1, next); //获取next数组

    for (int i = 1; i < (sizeof(String1)); i++)
    {
        printf("next[%d] = %d\n", i, next[i]);
    }
    printf("\n");
}

//KMP算法测试
void Test6()
{
    int next[9]; //next数组与有效字符数一致就行

    String S1;
    String S2;

    char String1[] = "Hello";
    char String2[] = " llo";

    S1.length = (sizeof(String1) - 1);
    S2.length = (sizeof(String2) - 1);

    for (int i = 0; i < (sizeof(String1) - 1); i++)
    {
        S1.ch[i] = String1[i];
        //printf("S1.ch[%d]=%c\n", i, S1.ch[i]);
    } //printf("\n");
    for (int i = 0; i < (sizeof(String2) - 1); i++)
    {
        S2.ch[i] = String2[i];
        //printf("S2.ch[%d]=%c\n", i, S2.ch[i]);
    } //printf("\n");

    Get_Next(S2, next); //获取next数组
    /*
    for (int i = 1; i < (sizeof(String2)); i++)
    {
        printf("next[%d] = %d\n", i, next[i]);
    }
    printf("\n");
    */
    printf("%d\n", Index_KMP(S1, S2, next));
}

int main()
{
    //Test5();
    Test6();

    return 1;
}
