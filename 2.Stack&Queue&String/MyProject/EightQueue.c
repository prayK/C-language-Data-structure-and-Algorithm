#include <stdio.h>

#define N 8

//三个方向的偏移量
typedef struct _tag_Pos
{
    int ios;
    int jos;
} Pos;

char board[N + 2][N + 2];                 //八皇后是有两个边界的，所以要+2
Pos pos[] = {{-1, -1}, {-1, 0}, {-1, 1}}; //分别是左上，正上，右上，三个方向
int count = 0;

/*初始化棋盘*/
void init()
{
    int i = 0;
    int j = 0;

    /*边界*/
    for (i = 0; i < N + 2; i++)
    {
        board[0][i] = '#';
        board[N + 1][i] = '#';
        board[i][0] = '#';
        board[i][N + 1] = '#';
    }
    /*棋盘*/
    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
        {
            board[i][j] = ' ';
        }
    }
}

/*棋盘显示*/
void display()
{
    int i = 0;
    int j = 1;

    for (i = 0; i < N + 2; i++)
    {
        for (j = 0; j < N + 2; j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

/*检查三个方向，然后判断能不能放皇后*/
int check(int i, int j)
{
    int ret = 1;
    int p = 0;

    //三个方向
    for (p = 0; p < 3; p++)
    {
        //printf("OK\n");
        int ni = i;
        int nj = j;

        //还没有搜索到边界
        while (ret && (board[ni][nj] != '#'))
        {
            ni = ni + pos[p].ios;
            nj = nj + pos[p].jos;

            ret = ret && (board[ni][nj] != '*');
        }
    }

    return ret;
}

/*摆放皇*/
void find(int i)
{
    int j = 0;

    if (i > N)
    {
        count++;

        printf("Solution: %d\n", count);
        display();

        //getchar();
    }
    else
    {
        //printf("OK\n");
        for (j = 1; j <= N; j++)
        {
            if (check(i, j))
            {
                board[i][j] = '*';
                find(i + 1);
                board[i][j] = ' '; //递归回来之后说明这条路径失败，所以要清空
            }
        }
    }
}

int main(void)
{
    init();
    find(1);

    return 0;
}

/*




#include <stdio.h>
int Queenes[8] = {0}, Counts = 0;
int Check(int line, int list)
{
    //遍历该行之前的所有行
    for (int index = 0; index < line; index++)
    {
        //挨个取出前面行中皇后所在位置的列坐标
        int data = Queenes[index];
        //如果在同一列，该位置不能放
        if (list == data)
        {
            return 0;
        }
        //如果当前位置的斜上方有皇后，在一条斜线上，也不行
        if ((index + data) == (line + list))
        {
            return 0;
        }
        //如果当前位置的斜下方有皇后，在一条斜线上，也不行
        if ((index - data) == (line - list))
        {
            return 0;
        }
    }
    //如果以上情况都不是，当前位置就可以放皇后
    return 1;
}
//输出语句
void print()
{
    for (int line = 0; line < 8; line++)
    {
        int list;
        for (list = 0; list < Queenes[line]; list++)
            printf("0");
        printf("#");
        for (list = Queenes[line] + 1; list < 8; list++)
        {
            printf("0");
        }
        printf("\n");
    }
    printf("================\n");
}

void eight_queen(int line)
{
    //在数组中为0-7列
    for (int list = 0; list < 8; list++)
    {
        //对于固定的行列，检查是否和之前的皇后位置冲突
        if (Check(line, list))
        {
            //不冲突，以行为下标的数组位置记录列数
            Queenes[line] = list;
            //如果最后一样也不冲突，证明为一个正确的摆法
            if (line == 7)
            {
                //统计摆法的Counts加1
                Counts++;
                //输出这个摆法
                print();
                //每次成功，都要将数组重归为0
                Queenes[line] = 0;
                return;
            }
            //继续判断下一样皇后的摆法，递归
            eight_queen(line + 1);
            //不管成功失败，该位置都要重新归0，以便重复使用。
            Queenes[line] = 0;
        }
    }
}
int main()
{
    //调用回溯函数，参数0表示从棋盘的第一行开始判断
    eight_queen(0);
    printf("摆放的方式有%d种", Counts);
    return 0;
}









*/