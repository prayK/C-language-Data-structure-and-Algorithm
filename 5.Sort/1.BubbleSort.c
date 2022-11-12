#include <stdio.h>

void printfIn(int array[], int len)
{
    int i = 0;
    for (i = 0; i < len; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void MySwap(int array[], int i, int j)
{
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

//从前往后比较，效率最低，（不算严格意义上的冒泡）O(n平方)
void BubbleSort_1(int array[], int len)
{
    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (array[i] > array[j])
            {
                MySwap(array, i, j);
            }
        }
    }
}

//正宗的冒泡，从后往前推进 O(n平方)
void BubbleSort_2(int array[], int len)
{
    for (int i = 0; i < len; i++)
    {
        for (int j = len - 1; j > i; j--) //从后往前循环
        {
            if (array[j - 1] > array[j]) //前者大于后者
            {
                MySwap(array, j - 1, j);
            }
        }
    }
}

//冒泡排序针对只需要少量换位数据情况下的优化 O(n平方)
void BubbleSort_3(int array[], int len)
{
    int flag = 1;

    for (int i = 0; (i < len && flag); i++)
    {
        flag = 0; //每一轮交换前都将flag赋值为0
        for (int j = len - 1; j > i; j--)
        {
            if (array[j - 1] > array[j])
            {
                MySwap(array, j - 1, j);
                flag = 1; //有数据交换就再来一轮，否则就直接结束
            }
        }
        /*
        if (flag == 0)
        {
            return;
        }
        */
    }
}

//冒泡递归解
void BubbleSort_4(int array[], int len)
{
    if (len < 2)
        return;
    for (int i = 0; i < len - 1; i++)
    {
        if (array[i] > array[i + 1])
        {
            MySwap(array, i, i + 1);
        }
    }
    BubbleSort_4(array, len - 1);
}

int main()
{
    int array[] = {9, 1, 5, 8, 3, 7, 4, 6, 2};
    int len = sizeof(array) / sizeof(*array);

    printfIn(array, len);

    BubbleSort_1(array, len);
    printfIn(array, len);

    BubbleSort_2(array, len);
    printfIn(array, len);

    BubbleSort_3(array, len);
    printfIn(array, len);

    BubbleSort_4(array, len);
    printfIn(array, len);

    return 0;
}
