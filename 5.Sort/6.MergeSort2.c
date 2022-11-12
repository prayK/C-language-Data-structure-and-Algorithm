#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printfIn(int array[], int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void MSort(int *src, int *des, int start, int end)
{
    if (start == end)
    {
        return;
    }
    unsigned int mid = (start + end) / 2; //计算排序区间中间的位置

    //左区间始末
    unsigned int LeftStart = start;
    unsigned int LeftEnd = mid;

    //右区间始末
    unsigned int RightStart = mid + 1;
    unsigned int RightEnd = end;

    MSort(src, des, LeftStart, LeftEnd);   //左区间递归排序
    MSort(src, des, RightStart, RightEnd); //右区间递归排序

    unsigned int index = start;

    while ((LeftStart <= LeftEnd) && (RightStart <= RightEnd))
    {
        if (src[LeftStart] < src[RightStart])
        {
            des[index] = src[LeftStart];
            index++;
            LeftStart++;
        }
        else
        {
            des[index] = src[RightStart];
            index++;
            RightStart++;
        }
    }

    //把左区间其它的元素追加到已排序数组
    while (LeftStart <= LeftEnd)
    {
        des[index] = src[LeftStart];
        index++;
        LeftStart++;
    }
    //把右区间其它的元素追加到已排序数组
    while (RightStart <= RightEnd)
    {
        des[index] = src[RightStart];
        index++;
        RightStart++;
    }

    //把已排序数组des中的元素复制到src中
    memcpy(src + start, des + start, (end - start + 1) * sizeof(int));
}

void MergeSort(int array[], int len)
{
    if (len < 2)
    {
        return; //小于两个元素不用排序
    }
    int des[len];

    MSort(array, des, 0, len - 1);
}

int main()
{
    int array[] = {9, 1, 5, 8, 3, 7, 4, 6, 2, 10};
    int len = sizeof(array) / sizeof(*array);

    printfIn(array, len);
    MergeSort(array, len);
    printfIn(array, len);

    return 0;
}
