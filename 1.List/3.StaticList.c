#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"

typedef int ElemType;
#define MAXSIZE 1000 //假定链表最大长度是1000

/*数组元素都是由两个数据域组成，data和cur。data相当于数据域，cur相当与单链表中的next指针域,
cur用来存放该元素的后继在数组中的下标数组第一个和最后一个元素作为特殊元素处理，不存数据。
第一个元素存备用链表的第一个节点的下标，最后一个元素存第一个元素的下标*/
struct StaticListNode
{
    ElemType data;
    int cur; //游标(cursor)，为0时表示无指向
};

struct StaticList
{
    struct StaticListNode node[MAXSIZE];
};

struct StaticList CreateList()
{
    struct StaticList List;
    for (int i = 0; i < MAXSIZE - 1; i++)
    {
        List.node[i].cur = i + 1;
    }
    List.node[MAXSIZE - 1].cur = 0; //目前静态链表为空，最后一个元素的cur为0

    return List;
}

/*在动态链表中节点的申请和释放是依赖malloc和free函数来实现的，在静态链表中，
操作的是数组，不存在节点的申请和释放，所以要自己实现这两个函数，才可以作插入和删除操作。
为了辨明数组中哪些分量未被使用，解决的办法是将所有未被使用和已被删除的分量用游标链成一个备用的链表
每当进行插入操作时，便可以从备用链表上取得第一个节点作为待插入的新节点*/

/*若备用空间链表非空，则返回分配的节点下标，否则返回0*/
int StaticListNodeMalloc(struct StaticList List)
{
    int i = List.node[0].cur; //当前数组第一个元素的cur存的值就是要返回的第一个备用空间的下标
    if (List.node[0].cur)
    {
        List.node[0].cur = List.node[i].cur; //由于要拿出一个分量出来使用，所以得把下一个分量用来做备用
    }
    return i;
}

/*将下标为k的空闲节点回收到备用链表*/
/*让删除的位置成为第一个优先空位*/
/*第一个元素的cur值代表StaticListNodeMalloc的地址*/
void StaticListNodeFree(struct StaticList List, int k)
{
    List.node[k].cur = List.node[0].cur; //把第一个元素cur值赋给要删除的分量cur
    List.node[0].cur = k;                //把要删除的分量下标赋值给第一个元素的cur
}

/*在静态链表中第i个元素之前插入新的数据元素e*/
int StaticListInsert(struct StaticList List, int index, ElemType e)
{
    int k = MAXSIZE - 1; //注意k是最后一个元素的下标
    if ((index < 1) || (index > MAXSIZE))
    {
        return 0;
    }
    int j = StaticListNodeMalloc(List); //获取空闲分量的下标
    if (j)
    {
        List.node[j].data = e;
        for (int i = 0; i < (index - 1); i++) //找到第i个元素之前的位置
        {
            k = List.node[k].cur;
        }
        List.node[j].cur = List.node[k].cur; //将第i个元素之前的cur赋值给新元素的cur
        List.node[k].cur = j;                //把新元素的cur的下标值给第i个元素之前元素的cur

        return 1;
    }
    else
    {
        return 0;
    }
}

/*删除静态链表中第ig个分量*/
int StaticListDelete(struct StaticList List, int index)
{
    if ((index < 1) || (index > MAXSIZE))
    {
        return 0;
    }
    int k = MAXSIZE - 1;
    int j = 0;
    for (int j = 1; j < (index - 1); j++)
    {
        k = List.node[k].cur;
    }
    j = List.node[k].cur;
    List.node[k].cur = List.node[j].cur;
    StaticListNodeFree(List, j);

    return 1;
}

/*获取链表的长度*/
int StaticListLength(struct StaticList List)
{
    int j;
    int i = List.node[MAXSIZE - 1].cur;

    while (i)
    {
        i = List.node[i].cur;
        j++;
    }
    return j;
}

int main(void)
{
    struct StaticList List = CreateList();
    for (int i = 0; i < 3; i++)
    {
        printf("%d %d\n", List.node[i].data, List.node[i].cur);
        printf("\n");
    }
    return 1;
}
