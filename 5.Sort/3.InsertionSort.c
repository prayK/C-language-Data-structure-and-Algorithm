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

//直接插入排序，O(n平方),性能优于冒泡排序和简单选择排序
void InsertionSort1(int array[], int len)
{
    for (int i = 1; i < len; i++) //从第一个元素开始，把第0个元素作为有序的初始序列
    {
        //当前如果比前一个元素大就不用往前插了；反之，需要找到适当的插入位置后在插入
        if (array[i] < array[i - 1])
        {
            int j = i - 1;
            int temp = array[i]; //随时准备移动，要把待插入值放进temp中
#if 1
            while ((j >= 0) && (temp < array[j]))
            {
                //采用顺序查找方式找到插入的位置，在查找的同时，将数组中的元素进行后移操作，给插入元素腾出空间
                array[j + 1] = array[j];
                j--;
            }
            array[j + 1] = temp; //插入到正确位置
#endif

#if 0
            for (; (j >= 0 && (array[j] > temp)); j--)
            {
                //查找应该插到什么地方,当不越界和需要向左插入时才执行转换操作
                array[j + 1] = array[j];
            }
            array[j + 1] = temp;//插入到正确位置
#endif
        }
    }
}

void InsertionSort2(int array[], unsigned int len)
{
    if (len < 2)
    {
        return;
    }
    for (unsigned int i = 1; i < len; ++i)
    {
        int temp = array[i];
        int j = i - 1;
        for (; (j >= 0) && (array[j] > temp); --j)
        {
            for (; j >= 0; --j)
            {
                if (array[j] <= temp)
                {
                    break;
                }
                array[j + 1] = array[j];
            }
        }
        array[j + 1] = temp;
    }
}

int main()
{
    int array[] = {9, 1, 5, 8, 3, 7, 4, 6, 2};
    int len = sizeof(array) / sizeof(*array);

    printfIn(array, len);

    InsertionSort1(array, len);
    printfIn(array, len);

    InsertionSort2(array, len);
    printfIn(array, len);

    return 0;
}
