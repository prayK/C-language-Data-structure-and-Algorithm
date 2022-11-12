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

/*********************************希尔排序(算法一)****************************************/
//希尔排序时间复杂度低于O(n平方)
void ShellSort1(int array[], int len)
{
    int gap = len;

    do
    {
        gap = gap / 3 + 1; //经过若干次变化后，应该最终收敛于1就可以,gap为1时退化为插入排序

        for (int i = gap; i < len; i++)
        {
            //当前如果比前一个元素大就不用往前插了；反之，需要找到适当的插入位置后在插入
            if (array[i] < array[i - gap])
            {
                int j = i - gap;
                int temp = array[i];
#if 1
                while ((j >= 0) && (temp < array[j]))
                {
                    //采用顺序查找方式找到插入的位置，在查找的同时，将数组中的元素进行后移操作，给插入元素腾出空间
                    array[j + gap] = array[j];
                    j -= gap;
                }
                array[j + gap] = temp; //插入到正确位置
#endif

#if 0
            for (; (j >= 0 && (array[j] > temp)); j -= gap)
            {
                array[j + gap] = array[j];
            }
            array[j + gap] = temp;
#endif
            }
        }
    } while (gap > 1);
}
/*********************************希尔排序(算法一)****************************************/

/*********************************希尔排序(算法二)****************************************/
// 对希尔排序中的单个组进行排序
// array为待排序的数组，len为数组总的长度，pos为分组的起始位置，step为分组的步长（增量）
void groupsort(int array[], int len, int pos, int step)
{
    for (int i = pos + step; i < len; i = i + step)
    {
        int temp = array[i]; // 待排序元素
        int j = i - step;    // 插入排序时，需要后移元素的计数器

        // 从已排序的最右边开始，把大于当前排序的元素后移
        // for(; (jj >= 0 && array[j] > temp); j = j - istep)
        for (; j >= 0; j = j - step)
        {
            if (array[j] <= temp)
            {
                break;
            }
            array[j + step] = array[j]; // 逐个元素后移
        }

        array[j + step] = temp; // 插入当前排序元素
    }
}

// 希尔排序，arr是待排序数组的首地址，len是数组的大小
void ShellSort2(int array[], unsigned int len)
{
    //step为步长，每次减为原来的一半取整数，最后一次必定为1
    for (int step = len / 2; step > 0; step = step / 2)
    {
        // 共step个组，对每一组都执行插入排序
        for (int i = 0; i < step; i++)
        {
            groupsort(array, len, i, step);
        }
    }
}
/*********************************希尔排序(算法二)****************************************/

int main()
{
    int array[] = {9, 1, 5, 8, 3, 7, 4, 6, 2};
    int len = sizeof(array) / sizeof(*array);

    printfIn(array, len);
    ShellSort1(array, len);
    printfIn(array, len);

    ShellSort2(array, len);
    printfIn(array, len);

    return 0;
}
