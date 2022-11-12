#include <stdio.h>

#define M 2
#define N 3

//数组打印函数(注意二维数组作为形参是需要将第二个维度的值传进去)
void Printconst(int array1[], int column1, int array2[M][N], int row2, int column2, int SWITCH)
{
    if (SWITCH == 1)
    {
        for (int i = 0; i < column1; i++)
        {
            printf("%d ", array1[i]);
        }
        printf("\n");
    }
    else
    {
        for (int i = 0; i < row2; i++)
        {
            for (int j = 0; j < column2; j++)
            {
                printf("%d ", array2[i][j]);
            }
            printf("\n");
        }
    }
}

//交换值函数
void swap(int array[], int i, int j)
{
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

//冒泡排序算法
void BubbleSort(int array[], int len)
{
    int flag = 1;

    for (int i = 0; (i < len && flag); i++)
    {
        flag = 0;
        for (int j = len - 1; j > i; j--)
        {
            if (array[j - 1] > array[j])
            {
                swap(array, j - 1, j);
                flag = 1;
            }
        }
    }
}

//二维数组转换为一维数组再进行冒泡排序(结果是有序的一维数组)
void function1(int array1[], int column1, int array2[M][N], int row2, int column2)
{
    int k = 0;
    for (int i = 0; i < row2; i++)
    {
        for (int j = 0; j < column2; j++)
        {
            array1[k] = array2[i][j];
            k++;
        }
    }
    BubbleSort(array1, M * N);
}

//直接对二维数组进行排序(结果是有序的二维数组)
void function2(int array[M][N], int row, int column)
{
    for (int i = 0; i < M * N; i++)
    {
        for (int j = i + 1; j < M * N; j++)
        {
            if (array[i / N][i % N] > array[j / N][j % N])
            {
                int Temp = array[i / N][i % N];
                array[i / N][i % N] = array[j / N][j % N];
                array[j / N][j % N] = Temp;
            }
        }
    }
}

int main(void)
{
    int array2[M][N] = {{1, 3, 5}, {2, 4, 8}};
    int array1[M * N] = {0};

    Printconst(array1, M * N, array2, M, N, 2); //打印二维数组
    function1(array1, M * N, array2, M, N);
    Printconst(array1, M * N, array2, M, N, 1); //打印一维数组

    function2(array2, M, N);
    Printconst(array1, M * N, array2, M, N, 2); //打印二维数组

    return 0;
}