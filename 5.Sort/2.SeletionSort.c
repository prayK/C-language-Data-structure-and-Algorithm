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

//简单选择排序,O(n平方),但是性能优于冒泡排序
void SelectionSort1(int array[], unsigned int len)
{
    for (int i = 0; i < len; i++)
    {
        int k = i; //将当前下标定义为最小值下标

        //通过这个循环就可以找到最小的那个元素所在的位置
        for (int j = i + 1; j < len; j++)
        {
            if (array[j] < array[k])
            {
                k = j; //标志位转换
            }
        }
        if (k != i) //若当真发生了最小值转换，那么就交换值吧
        {
            MySwap(array, i, k);
        }
    }
}

// 采用递归实现的方法。
// 参数array是待排序数组的首地址，len是数组元素的个数
void SelectionSort2(int array[], unsigned int len)
{
    if (len < 2)
    {
        return; // 数组小于2个元素不需要排序
    }

    int min = 0; // 每趟循环选出的最小值的位置（数组的下标）

    for (int i = 1; i < len; i++)
    {
        if (array[i] < array[min])
        {
            min = i;
        }
    }

    // 如果本趟循环的最小的元素不是起始位置的元素，则交换它们的位置
    if (min != 0)
    {
        MySwap(array, 0, min);
    }

    SelectionSort2(array + 1, --len);
}

// 采用两层循环实现的方法
// 参数arr是待排序数组的首地址，len是数组元素的个数
void SelectionSort3(int array[], unsigned int len)
{
    if (len < 2)
    {
        return; // 数组小于2个元素不需要排序
    }

    unsigned int max; // 每趟循环选出的最小值的位置（数组的下标）
    unsigned int min; // 每趟循环选出的最大值的位置（数组的下标）

    unsigned int left = 0;
    unsigned int right = len - 1; // left从0开始，right从len-1开始

    while (left < right)
    {
        max = min = left;

        for (int i = left; i <= right; ++i) // 每趟循环从ileft和iright之间选取元素
        {
            if (array[i] < array[min])
            {
                min = i; // 找出值更小的元素，记下它的位置
            }
            if (array[i] > array[max])
            {
                max = i; // 找出值更大的元素，记下它的位置
            }
        }

        if (min != left)
        {
            MySwap(array, left, min); // 如果本趟循环的最小的元素不是最左边的元素，则交换它们的位置
        }

        // 如果imaxpos的位置是ileft，在上面的代码中ileft已被交换到了iminpos的位置
        // 所以imaxpos的值要修改为iminpos
        if (max == left)
        {
            max = min;
        }

        if (max != right)
        {
            MySwap(array, right, max); // 如果本趟循环的最大的元素不是最右边的元素，则交换它们的位置
        }

        ++left;
        --right;
    }
}

// 采用递归实现的方法
// 参数arr是待排序数组的首地址，len是数组元素的个数
void SelectionSort4(int array[], unsigned int len)
{
    if (len < 2)
    {
        return;
    }

    unsigned int max = 0; // 每趟循环选出的最小值的位置（数组的下标）
    unsigned int min = 0; // 每趟循环选出的最大值的位置（数组的下标）

    unsigned int left = 0;
    unsigned int right = len - 1; // left从0开始，right从len-1开始

    for (int i = left; i <= right; ++i) // 每趟循环从ileft和iright之间选取元素
    {
        if (array[i] < array[min])
        {
            min = i; // 找出值更小的元素，记下它的位置
        }
        if (array[i] > array[max])
        {
            max = i; // 找出值更大的元素，记下它的位置
        }
    }

    if (min != left)
    {
        MySwap(array, left, min); // 如果本趟循环的最小的元素不是最左边的元素，则交换它们的位置
    }

    // 如果imaxpos的位置是ileft，在上面的代码中ileft已被交换到了iminpos的位置
    // 所以imaxpos的值要修改为iminpos
    if (max == left)
    {
        max = min;
    }

    if (max != right)
    {
        MySwap(array, right, max); // 如果本趟循环的最大的元素不是最右边的元素，则交换它们的位置
    }

    len = len - 2;

    SelectionSort4(++array, len);
}

int main()
{
    int array[] = {9, 1, 5, 8, 3, 7, 4, 6, 2};
    int len = sizeof(array) / sizeof(*array);

    printfIn(array, len);

    SelectionSort1(array, len);
    printfIn(array, len);

    SelectionSort2(array, len);
    printfIn(array, len);

    SelectionSort3(array, len);
    printfIn(array, len);

    SelectionSort4(array, len);
    printfIn(array, len);

    return 0;
}
