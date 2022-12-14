//插值查找，利用差值公式加快区间定位，
//但是对于数据极端不均匀的情况不太适用(把二分查找的43行改了就行)
#include <stdio.h>
#include <stdlib.h>

#define keyType int

typedef struct
{
    keyType key;//查找表中每个数据元素的值
    //如果需要，还可以添加其他属性
}ElemType;

typedef struct
{
    ElemType *elem;//存放查找表中数据元素的数组
    int length;//记录查找表中数据的总数量
}SSTable;

//创建查找表
void Create(SSTable **st, int length)
{
    (*st) = (SSTable*)malloc(sizeof(SSTable));
    (*st)->length = length;
    (*st)->elem = (ElemType*)malloc((length+1)*sizeof(ElemType));
    printf("输入表中的%d个数据元素：\n", length);

    //根据查找表中数据元素的总长度，在存储时，从数组下标为 1 的空间开始存储数据
    for(int i=1; i<=length; i++)
    {
        printf("请输入第%d个数据: ", i);
        scanf("%d", &((*st)->elem[i].key));
    }
}

//插值查找算法
int InterpolationSearch(SSTable *ST,keyType key)
{
    int low = 1;//初始状态 low 指针指向第一个关键字
    int high = ST->length;//high 指向最后一个关键字
    int mid;
    while(low <= high)
    {
        mid = low + (high - low) * (key - ST->elem[low].key) / (ST->elem[high].key - ST->elem[low].key);
        if (ST->elem[mid].key == key)//如果 mid 指向的同要查找的相等，返回 mid 所指向的位置
        {
            return mid;
        }
        else if(ST->elem[mid].key > key)//如果mid指向的关键字较大，则更新 high 指针的位置
        {
            high = mid - 1;
        }
        //反之，则更新 low 指针的位置
        else
        {
            low = mid + 1;
        }
    }
    return 0;
}

int main(int argc, const char * argv[])
{
    SSTable *st;
    Create(&st, 11);
    getchar();
    printf("请输入查找数据的关键字：\n");
    int key;
    scanf("%d", &key);
    int location = InterpolationSearch(st, key);

    //如果返回值为 0，则证明查找表中未查到 key 值，
    if(location == 0)
    {
        printf("查找表中无该元素");
    }
    else
    {
        printf("数据在查找表中的位置为：%d", location);
    }
    return 0;
}
