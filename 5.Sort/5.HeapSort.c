/*堆排序：堆用完全二叉树表示时，其表示方法不唯一，但是可以确定的是树的根结点要么是无序表中的最小值，
要么是最大值。通过将无序表转化为堆，可以直接找到表中最大值或者最小值，然后将其提取出来，令剩余的记录再重建一个堆，
取出次大值或者次小值，如此反复执行就可以得到一个有序序列，此过程为堆排序。O(nlogn)*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 10

//记录表的结构体
struct S_SeqList
{
    int Data[MAX];
    int Length;
} SqList;

typedef struct S_SeqList SeqList;

//交换两个记录的位置
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void MySwap(int array[], int i, int j)
{
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void MyPrint(int array[], int len)
{
    for (int i = 0; i < len; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

/**************************************堆排序(算法一)******************************************/
//将以 Data[s]为根结点的子树构成大根堆，堆中每个根结点的值都比其孩子结点的值大
void HeapAdjust1(SeqList *List, int s, int m)
{
    int temp = List->Data[s]; //先对操作位置上的结点数据进行保存备份，用以交换数值

    //沿关键字比较大的孩子节点向下筛选
    for (int j = 2 * s; j <= m; j *= 2)
    {
        if ((j + 1 < m) && (List->Data[j] < List->Data[j + 1])) //如果左孩子小于右孩子
        {
            j++; //j为当前节点左右孩子中的较大值的下标
        }
        //如果当前结点比最大的孩子结点的值还大，则不需要对此结点进行筛选，直接略过
        if (temp >= List->Data[j])
        {
            break;
        }
        //如果当前结点的值比孩子结点中最大的值小，则将最大的值移至该结点，由于 rc 记录着该结点的值，所以该结点的值不会丢失
        List->Data[s] = List->Data[j];
        s = j; //s相当于指针的作用，指向其孩子结点，继续进行筛选
    }
    List->Data[s] = temp; //最终需将rc的值添加到正确的位置
}

//堆排序，一是将待排序序列构建成大根堆，二是将大根堆的根节点移除，并且将剩余待排序序列再构建成大根堆
void HeapSort1(SeqList *List)
{
    //将待排序序列构建成一个大顶堆，只需要从length/2开始即可
    for (int i = List->Length / 2; i > 0; i--)
    {
        HeapAdjust1(List, i, List->Length);
    }
    //通过不断地筛选出最大值，并且将剩余待排序序列再构建成大根堆
    for (int i = List->Length; i > 1; i--)
    {
        swap(&(List->Data[1]), &(List->Data[i])); //将堆顶记录和当前未排序子序列的最后一个记录交换
        HeapAdjust1(List, 1, i - 1);              //将待排序序列构建成一个大顶堆
    }
}
/**************************************堆排序(算法一)******************************************/

/**************************************堆排序(算法二)******************************************/
// 采用循环实现HeapAdjust（元素下沉）。
// array是待排序数组的地址，start是待HeapAdjust节点的下标，end是待排序数组最后一个元素的下标。
void HeapAdjust2(int array[], int start, int end)
{
    // 确定父节点和左子节点的数组下标(注意这里的数组从0开始，所以左子节点的坐标为 dad*2+1)
    int dad = start;
    int son = dad * 2 + 1;

    // 如果子节点的下标没有超出范围，循环继续
    while (son <= end)
    {
        // 先比较两個子节点大小，选择最大的
        if ((son + 1 <= end) && (array[son] < array[son + 1]))
        {
            son++;
        }

        // 如果父节点大于子节点代表调整完毕，直接跳出函数
        if (array[dad] > array[son])
        {
            return;
        }

        // 否则交换父子內容再继续子节点和孙节点比较
        MySwap(array, dad, son);
        dad = son;
        son = dad * 2 + 1;
    }
}

// 采用递归实现HeapAdjust
void HeapAdjust3(int array[], int start, int end)
{
    // 确定父节点和左子节点的数组下标。
    int dad = start;
    int son = dad * 2 + 1;

    // 如果子节点的下标没有超出范围，循环继续。
    if (son > end)
    {
        return;
    }

    // 先比较两個子节点大小，选择最大的。
    if ((son + 1 <= end) && (array[son] < array[son + 1]))
    {
        son++;
    }

    // 如果父节点大于子节点代表调整完毕，直接跳出函数。
    if (array[dad] > array[son])
    {
        return;
    }

    // 否则交换父子內容再继续子节点和孙节点比较。
    MySwap(array, dad, son);

    HeapAdjust3(array, son, end);
}

void HeapSort2(int array[], int len)
{
    // 初始化堆，从最后一個父节点开始调整
    for (int i = len / 2; i >= 0; --i)
    {
        HeapAdjust2(array, i, len - 1);
        //HeapAdjust3(array, i, len - 1);
    }

    // 把第一个元素和堆最后一个元素交换，然后重新调整，直到排序完毕
    for (int i = len - 1; i > 0; --i)
    {
        MySwap(array, 0, i);
        HeapAdjust2(array, 0, i - 1);
        //HeapAdjust3(array, i, len - 1);
    }
}
/**************************************堆排序(算法二)******************************************/

int main()
{
    SeqList *List = (SeqList *)malloc(sizeof(struct S_SeqList));

    List->Length = 8;
    List->Data[1] = 49;
    List->Data[2] = 38;
    List->Data[3] = 65;
    List->Data[4] = 97;
    List->Data[5] = 76;
    List->Data[6] = 13;
    List->Data[7] = 27;
    List->Data[8] = 49;

    HeapSort1(List);
    for (int i = 1; i <= List->Length; i++)
    {
        printf("%d ", List->Data[i]);
    }
    printf("\n");

    free(List);

    int array[] = {9, 1, 5, 8, 3, 7, 4, 6, 2};
    int len = sizeof(array) / sizeof(*array);

    //MyPrint(array, len);
    HeapSort2(array, len);
    MyPrint(array, len);

    return 0;
}
