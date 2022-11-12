#include <stdio.h>

//递归实现斐波那契数列
int fac(int n)
{
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    return fac(n - 1) + fac(n - 2);
}
//递归实现汉诺塔问题
void hanoi(int n, char a, char b, char c)
{
    if (n > 0)
    {
        if (n == 1) //如果就一个盘子，就直接从a柱移动到c柱
        {
            printf("%c -> %c\n", a, c);
        }
        else
        {
            hanoi(n - 1, a, c, b); //第一步：从a借助c移动到b
            printf("%c -> %c\n", a, c);
            hanoi(n - 1, b, a, c); //第二步：将盘子从b柱借助a柱移动到c柱
        }
    }
}

//递归实现全排列问题
void permutation(char s[], int begin, int end)
{
    if ((0 <= begin) && (begin <= end))
    {
        /*起始和结束都是自己*/
        if (begin == end)
        {
            printf("%s\n", s);
        }
        else
        {
            int i = 0;
            for (i = begin; i <= end; i++)
            {
                /*交换数据，每个字符都当头一次*/
                char c = s[begin];
                s[begin] = s[i];
                s[i] = c;

                /*对剩下的进行全排列*/
                permutation(s, begin + 1, end);

                /*还原为原始排序*/
                c = s[begin];
                s[begin] = s[i];
                s[i] = c;
            }
        }
    }
}

int main(void)
{
#if 0
    ("%d\n", fac(1));
    printf("%d\n", fac(2));
    printf("%d\n", fac(9));
#endif

#if 0
    hanoi(64, 'a', 'b', 'c');
#endif

#if 1
    char s[] = "abc";
    permutation(s, 0, 2);
#endif

    return 0;
}
