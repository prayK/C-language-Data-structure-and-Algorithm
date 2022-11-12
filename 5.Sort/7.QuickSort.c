#include <stdio.h>
#include <stdlib.h>

void printfIn(int array[], int len)
{
    int i = 0;
    for (i = 0; i < len; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void swap(int array[], int i, int j)
{
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

//求枢轴
int pivot(int array[], int low, int high)
{
#define OK 2
    if (OK == 1) //选最低位值为枢轴
    {
        return array[low];
    }
    if (OK == 2) //左中右三数求枢轴
    {
        int mid = low + (high - low) / 2; //计算数组中间的元素的下标

        if (array[low] > array[high])
            swap(array, low, high); //保证左边比右边小
        if (array[mid] > array[high])
            swap(array, high, mid); //保证中间比右边小
        if (array[mid] > array[low])
            swap(array, mid, low); //此时右边最大，比较左边和中间即可，使得左边为中间值
        //此时array[low]中已经为整个序列左中右三个关键字的中间值

        return array[low];
    }
    if (OK == 3) //九数求枢轴，适用于非常大的待排序序列
    {
    }
}

/*partition函数是快速排序的划分过程，要先选取一个关键字(比如array[0])，
然后将它放置到一个位置，使得左边的值比它小，右边的值比它大*/
int partition(int array[], int low, int high)
{
    int pivotkey = pivot(array, low, high); //枢轴值

    while (low < high)
    {
        while ((low < high) && (array[high] >= pivotkey))
        {
            high--;
        }
        /*直接交换会导致很多冗余的步骤*/
        array[low] = array[high]; //采用替换而不是交换的方式进行操作

        while ((low < high) && (array[low] < pivotkey))
        {
            low++;
        }
        /*直接交换会导致很多冗余的步骤*/
        array[high] = array[low]; //采用替换而不是交换的方式进行操作
    }
    array[low] = pivotkey; //将枢轴值替换回array[low]
    return high;
}

//快排在元素较少的情况下可以用直接插入排序来替代，因为此时直接插入排序的效率更高
void QuickSort(int array[], int low, int high)
{
    if (low < high)
    {
        //pivot左边元素都比他小，右边元素都比他大
        int pivot = partition(array, low, high); //将数组一分为二，算出枢轴值pivot

        QuickSort(array, low, pivot - 1);  //对低子表递归排序，直到顺序全部正确
        QuickSort(array, pivot + 1, high); //对高子表递归排序，知道顺序全部正确
    }
}

int main()
{
    int array[] = {9, 1, 5, 8, 3, 7, 4, 6, 2, 10};
    int len = sizeof(array) / sizeof(*array);

    printfIn(array, len);

    QuickSort(array, 0, len - 1);
    printfIn(array, len);

    return 0;
}
