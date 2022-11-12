#include <stdio.h>
#include <stdlib.h>

#define MAX_VERtEX_NUM 20 //顶点的最大个数
#define VRType int        //表示顶点之间的关系的变量类型
#define InfoType char     //存储弧或者边额外信息的指针变量类型
#define VertexType int    //图中顶点的数据类型
#define MAXVEX 10         //图中顶点的数据类型

typedef struct
{
    VRType adj;     //对于无权图，用 1 或 0 表示是否相邻；对于带权图，直接为权值。
    InfoType *info; //弧或边额外含有的信息指针
} ArcCell, AdjMatrix[MAX_VERtEX_NUM][MAX_VERtEX_NUM];

typedef struct
{
    VertexType vexs[MAX_VERtEX_NUM]; //存储图中顶点数据
    AdjMatrix arcs;                  //二维数组，记录顶点之间的关系
    int vexnum, arcnum;              //记录图的顶点数和弧（边）数
} MGraph;

//根据顶点本身数据，找到他们在一维数组中的位置，进而判断出顶点在二维数组中的位置
int LocateVex(MGraph *G, VertexType v)
{
    int i = 0;
    //遍历一维数组，找到变量v
    for (; i < G->vexnum; i++)
    {
        if (G->vexs[i] == v)
        {
            break;
        }
    }
    //如果找不到，输出提示语句，返回-1
    if (i > G->vexnum)
    {
        printf("no such vertex.\n");
        return -1;
    }
    return i;
}

//构造无向网。和无向图唯一的区别就是二阶矩阵中存储的是权值
void CreateUDN(MGraph *G)
{
    printf("请输入节点数目和边(弧)的数目(用逗号隔开):");
    scanf("%d,%d", &(G->vexnum), &(G->arcnum));

    for (int i = 0; i < G->vexnum; i++)
    {
        printf("请输入第%d个顶点值:", i + 1);
        scanf("%d", &(G->vexs[i]));
    }
    for (int i = 0; i < G->vexnum; i++)
    {
        for (int j = 0; j < G->vexnum; j++)
        {
            G->arcs[i][j].adj = 65535; //这里要设置为65535，修改Prim中的算法后可以将这里的65535修改为0
            G->arcs[i][j].info = NULL;
            if (i == j)
            {
                G->arcs[i][j].adj = 0;
            }
        }
    }
    for (int i = 0; i < G->arcnum; i++)
    {
        int v1, v2, w;

        printf("请输入两个相互连接的顶点值和权值(用逗号隔开):");
        scanf("%d,%d,%d", &v1, &v2, &w);

        int n = LocateVex(G, v1);
        int m = LocateVex(G, v2);

        printf("这两个点在一维矩阵中的位置分别为：");
        printf("%d,%d。", n, m);
        printf("即邻接矩阵中的arcs[%d][%d]位置将会被置为%d\n", n, m, w);

        if ((m == -1) || (n == -1))
        {
            printf("no this vertex\n");
            return;
        }
        G->arcs[n][m].adj = w;
        G->arcs[m][n].adj = w; //矩阵对称
    }
}

//Prim 算法生成最小生成树
void MiniSpanTree_Prim(MGraph G)
{
    int lowcost[MAXVEX]; //保存相关顶点边的权值
    int adjvex[MAXVEX];  //保存相关顶点的下标

    //将所有与v0连接的顶点的边的权值存入数组
    for (int i = 0; i < G.vexnum; i++)
    {
        lowcost[i] = G.arcs[0][i].adj;
        adjvex[i] = 0; //初始化都为0
    }
    //构造最小生成树的过程
    for (int i = 1; i < G.vexnum; i++) //从集合A(横坐标)中一个一个拿 点去比较
    {
        int min = 65535; //初始化最小权值为无穷大
        int k = 0;       //k是用来存储最小权值的顶点坐标

        //这段代码是为了找到当前顶点边中权值最小的边
        for (int j = 1; j < G.vexnum; j++) //找到集合A中所有点到集合B中所有点之间的最小值，然后将B中的那个点纳入生成树
        {
            if ((lowcost[j] != 0) && (lowcost[j] < min)) //如果权值不为0且权值小于min
            {
                min = lowcost[j]; //更新当前权值为最小权值
                k = j;            //更新当前权值坐标
            }
        }

        printf("(%d,%d)", adjvex[k], k); //打印当前顶点边中权值最小的边
        lowcost[k] = 0;                  //将当前顶点的权值设置为0,表示此顶点已纳入最小生成树

        //查找下一个应该被纳入树中的顶点
        for (int j = 1; j < G.vexnum; j++)
        {
            //如果下标为k(已经加入生成树)的顶点边集中权值小于已存在的权值(再前一个加入生成树的顶点)
            //将第k行的值拿出来与前一个节点(比如v0)的各边权值进行比较,更新lowcost数组，进而进入第二轮循环找下一个纳入节点
            if ((lowcost[j] != 0) && (G.arcs[k][j].adj < lowcost[j]))
            {
                lowcost[j] = G.arcs[k][j].adj; //将较小的权值存入 lowcost 相应位置
                adjvex[j] = k;                 //这里的k表示正在第几个节点处找纳入点
            }
        }
    }
}

//打印邻接矩阵
void Print(MGraph G, int length, int width)
{
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%d ", G.arcs[i][j].adj);
        }
        printf("\n");
    }
}

int main()
{
    MGraph G;
    CreateUDN(&G);
    //Print(G, G.vexnum, G.vexnum);
    MiniSpanTree_Prim(G);

    return 0;
}
