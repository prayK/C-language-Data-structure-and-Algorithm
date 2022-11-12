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

void Merge(int *src, unsigned int low, unsigned int mid, unsigned int high)
{
    unsigned int i = low;
    unsigned int j = mid + 1;
    unsigned int k = low;

    printf("%d %d %d\n", low, mid, high);

    int des[high - low + 1];

    while ((i <= mid) && (j <= high))
    {
        if (src[i] < src[j])
            des[k++] = src[i++];
        else
            des[k++] = src[j++];
    }

    while (i <= mid)
        des[k++] = src[i++];

    while (j <= high)
        des[k++] = src[j++];

    memcpy(src + low, des + low, (high - low + 1) * sizeof(int));
}

void MergeSort(int *src, unsigned int low, unsigned int high)
{
    if (low >= high)
        return; // 终止递归的条件

    unsigned int mid = low + (high - low) / 2;

    MergeSort(src, low, mid);
    MergeSort(src, mid + 1, high);
    Merge(src, low, mid, high);
}

int main()
{
    int array[] = {9, 1, 5, 8, 3, 7, 4, 6, 2, 10};
    int len = sizeof(array) / sizeof(*array);

    printfIn(array, len);
    MergeSort(array, 0, len - 1);
    printfIn(array, len);

    return 0;
}
