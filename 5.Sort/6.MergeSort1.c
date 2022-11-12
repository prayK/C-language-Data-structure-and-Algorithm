#include <stdio.h>
#include <stdlib.h>

#define OK 1

void printfIn(int array[], int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

//归并函数，将src中的元素由小到大并入到des中去
void Merge(int src[], int des[], int low, int mid, int high)
{
    int i = low;
    int j = mid + 1;
    int k = low;
    //printf("%d %d %d\n", low, mid, high);
    //这个时候[i,mid]和[mid+1,high]是已经排好了的，此时只需归并这两个就可以了
    //将小的那个放到最终目的地里面去
    for (; (i <= mid) && (j <= high); k++)
    {
        if (src[i] < src[j])
        {
            des[k] = src[i];
            i++;
        }
        else
        {
            des[k] = src[j];
            j++;
        }
    }

    //归并剩下来的数组数据

    while (i <= mid)
    {
        des[k] = src[i]; //将 src[i - m]中没有归并的数据归并进des[]
        i++;
        k++;
    }

    while (j <= high)
    {
        des[k] = src[j]; //将 src[j - high]中没有归并的数据归并进des[]
        j++;
        k++;
    }
}

//每次分两路，分到只剩一个的时候就不分了
void MergeSort(int src[], int des[], int low, int high, int max)
{
    if (low == high)
    {
        des[low] = src[low];
    }
    else
    {
        int mid = low + (high - low) / 2;
        int *space = (int *)malloc(sizeof(int) * max);

        if (space != NULL)
        {
            MergeSort(src, space, low, mid, max);      //将src[low - mid]有序归并到space中
            MergeSort(src, space, mid + 1, high, max); //将src[mid+1 - high]有序归并到space中
            Merge(space, des, low, mid, high);         //将space[low - mid] 和space[mid + high]归并到des中
        }
        free(space);
    }
}

int main()
{
    int array[] = {9, 1, 5, 8, 3, 7, 4, 6, 2, 10};
    int len = sizeof(array) / sizeof(*array);

    printfIn(array, len);
    MergeSort(array, array, 0, len - 1, len);
    printfIn(array, len);

    return 0;
}
