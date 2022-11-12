#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int x, int y)
{
    return x < y ? x : y;
}

void printfIn(int array[], int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void MergeSort(int array[], unsigned int len)
{
    if (len < 2)
    {
        return;
    }
    int *src = array;                            //指向未排序的数组
    int *des = (int *)malloc(sizeof(int) * len); //指向已排序的数组

    int segement; //区间分段计数器 1 2 4 8 16
    int start;    //区间起始位置的计数器

    //排序趟数循环
    for (segement = 1; segement < len; segement *= 2)
    {
        //每趟排序选取的区间的内部循环
        for (start = 0; start < len; start = start + segement * 2)
        {
            // 把每个区间分成两部分，low是起始位置，mid是中间位置，high是结束位置
            unsigned int low = start;
            unsigned int mid = min(start + segement, len);      // 考虑分段不均的情况，mid不能超出len
            unsigned int high = min(start + segement * 2, len); // 考虑分段不均的情况，max也不能超出len

            unsigned int index = low;
            unsigned int LeftStart = low;
            unsigned int LeftEnd = mid;
            unsigned int RightStart = mid;
            unsigned int RightEnd = high;

            while ((LeftStart < LeftEnd) && (RightStart < RightEnd))
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
            while (LeftStart < LeftEnd)
            {
                des[index] = src[LeftStart];
                index++;
                LeftStart++;
            }
            //把右区间其它的元素追加到已排序数组
            while (RightStart < RightEnd)
            {
                des[index] = src[RightStart];
                index++;
                RightStart++;
            }
        }

        //交换两个数组的指针，准备下一趟的排序
        int *temp = src;
        src = des;
        des = temp;
    }

    // 如果src指向的不是原始数组的指针，把src中的内容复制到array中
    if (src != array)
    {
        memcpy(array, src, len * sizeof(int));
        des = src;
    }
    free(des);
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
