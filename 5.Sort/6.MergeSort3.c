#include <stdio.h>
#include <stdlib.h>

void printfIn(int array[], int len)
{
    for (int i = 1; i < len; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void Merge(int src[], int des[], int low, int mid, int high)
{
    int i = low;
    int j = mid + 1;
    int k = low;
    //这个时候[i,mid]和[mid+1,high]是已经排好了的，此时只需归并这两个就可以了
    //将小的那个放到最终目的地里面去
    for (; (i <= mid) && (j <= high); k++)
    {
        if (src[i] < src[j])
        {
            des[k] = src[i++];
        }
        else
        {
            des[k] = src[j++];
        }
    }
    //肯定会有一路会剩下来，将剩下来的那一个复制到目的地中去
    while (i <= mid)
    {
        des[k++] = src[i++];
    }
    while (j <= high)
    {
        des[k++] = src[j++];
    }
}

/*将src[]中相邻长度为k的子序列两两归并到des[]中*/
void MergePass(int src[], int des[], int k, int len)
{
    int i = 0;
    int j;
    while (i <= (len - 2 * k + 1))
    {
        Merge(src, des, i, (i + k - 1), (i + 2 * k - 1)); //两两归并
        i = i + 2 * k;
    }
    if (i < (len - k + 1)) //归并最后两个序列
    {
        Merge(src, des, i, (i + k - 1), len);
    }
    else //若最后只剩下单个子序列
    {
        for (j = i; j <= len; j++)
        {
            des[j] = src[j];
        }
    }
}

void MergeSort(int array[], int len)
{
    int *des = (int *)malloc(sizeof(int) * len); //存放归并结果

    int k = 1; //注意是从1开始存的
    while (k < len)
    {
        MergePass(array, des, k, len); //将原来的无序数组两两归并入des中
        k = 2 * k;                     //子序列长度加倍
        MergePass(des, array, k, len);
        k = 2 * k; //子序列长度加倍
    }
    free(des);
}

int main()
{
    int array[] = {9, 1, 5, 8, 3, 7, 4, 6, 2, 10};
    int len = sizeof(array) / sizeof(*array);

    printfIn(array, len - 1);
    MergeSort(array, len - 1);
    printfIn(array, len - 1);

    return 0;
}
