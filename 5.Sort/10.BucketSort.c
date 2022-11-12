#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void MyPrint(int array[], int len)
{
    for (int i = 0; i < len; i++)
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

void BubbleSort(int array[], int len)
{
    int flag = 1;
    for (unsigned int i = 0; (i < len) && (flag = 1); ++i)
    {
        flag = 0;
        for (unsigned int j = len - 1; j > i; --j)
        {
            if (array[j] < array[j - 1])
            {
                MySwap(array, j, j - 1);
                flag = 1;
            }
        }
    }
}

void BucketSort(int array[], int len)
{
    int Bucket[50];     //50个桶
    int BucketSize[50]; //每个桶中存的数据个数

    for (unsigned int i = 0; i < 50; ++i)
    {
        int k = array[i] / 10;
        Bucket[k] = 0;
        BucketSize[i] = 0;
    }
}

int main(void)
{
    srand((unsigned int)time(NULL));
    int len = 50;
    int array[len];

    for (int i = 0; i < 50; i++)
    {
        array[i] = rand() % 99;
    }

    MyPrint(array, len);
    BucketSort(array, len);
    MyPrint(array, len);

    return 0;
}