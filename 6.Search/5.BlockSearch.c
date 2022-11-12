#include <stdio.h>

//块查找(索引查找)，块间有序(后块内全部数据都要大于前块中的数据)，块内无序
//块间可以采用折半查找，块内可以使用顺序查找，目前的代码还是要手动输入升序数才可以实现查找
//可以优化一下，先排序再分块，再查找
struct index
{
    int key;   //块的关键字
    int start; //块的起始值
    int end;   //块的结束值
};

struct index index_table[4]; //定义结构体数组

int BlockSearch(int key, int a[]) //自定义实现分块查找
{
    int pos = 0;
    for (int i = 1; i <= 3; i++) //分为三个块
    {
        index_table[i].start = pos + 1; //确定每个块范围的起始值
        pos = pos + 1;
        index_table[i].end = pos + 4; //确定每个块范围的结束值
        pos = pos + 4;
        index_table[i].key = a[pos]; //确定每个块范围中元素的最大值
    }

    int i = 1;
    while (i <= 3 && key > index_table[i].key) //确定在哪个块中
    {
        i++;
    }
    if (i > 3) //大于分得的块数，则返回0
    {
        return 0;
    }

    int j = index_table[i].start;                  //j等于块范围的起始值
    while (j <= index_table[i].end && a[j] != key) //在确定的块内进行顺序查找
    {
        j++;
    }
    if (j > index_table[i].end) //如果大于块范围的结束值，则说明没有要査找的数，j置0
    {
        j = 0;
    }

    return j;
}

int main()
{
    int a[16];
    printf("请输入15个数：\n");
    for (int i = 1; i < 16; i++)
    {
        printf("请输入第%d个数据：", i);
        scanf("%d", &a[i]); //输入由小到大的15个数(我们应该对每个块中的数据进行排序)
    }

    int key;
    printf("请输入你想査找的元素：");
    scanf("%d", &key);

    int k = BlockSearch(key, a); //调用函数进行杳找

    if (k == 0)
    {
        printf("查找失败!"); //若未找到，则输出提示信息
    }
    else
    {
        printf("查找成功，其位置是：%d\n", k); //如果找到该数，则输出其位置
    }

    return 0;
}