#include <stdio.h>
#include <stdlib.h>

#define MAX_VERtEX_NUM 20 //顶点的最大个数
#define VRType int        //表示顶点之间的关系的变量类型
#define InfoType char     //存储弧或者边额外信息的指针变量类型
#define VertexType int    //图中顶点的数据类型
#define MAXVEX 10         //图中顶点的数据类型
#define MAXEDGE 10

typedef struct
{
    int Begin;
    int End;
    int Weight;
} Edge;

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

//打印边集数组
void PrintArray(Edge edges[], int N)
{
    printf("边集数组为: \n");
    for (int i = 0; i < N; i++)
    {
        printf("(%d,%d,%d)", edges[i].Begin, edges[i].End, edges[i].Weight);
    }
    printf("\n");
}

//输出邻接矩阵函数
void PrintGrapth(MGraph G)
{
    printf("邻接矩阵为: \n");
    for (int i = 0; i < G.vexnum; i++)
    {
        for (int j = 0; j < G.vexnum; j++)
        {
            printf("%d ", G.arcs[i][j].adj);
        }
        printf("\n");
    }
}

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

//交换值函数
void swap(Edge edges[], int i, int j)
{
    int Weight = edges[i].Weight;
    edges[i].Weight = edges[j].Weight;
    edges[j].Weight = Weight;

    int Begin = edges[i].Begin;
    edges[i].Begin = edges[j].Begin;
    edges[j].Begin = Begin;

    int End = edges[i].End;
    edges[i].End = edges[j].End;
    edges[j].End = End;
}

//冒泡排序算法
void BubbleSort(Edge edges[], int len)
{
    int flag = 1;

    for (int i = 0; (i < len && flag); i++)
    {
        flag = 0;
        for (int j = len - 1; j > i; j--)
        {
            if (edges[j - 1].Weight > edges[j].Weight)
            {
                swap(edges, j - 1, j);
                flag = 1;
            }
        }
    }
}

//将邻接矩阵G转化为边集数组，并且对边集数组进行冒泡排序
void MatrixToArray(Edge edges[], MGraph *G)
{
    int k = 0;

    //先把所有带权值边找出来
    for (int i = 0; i < G->vexnum; i++)
    {
        for (int j = 0; j < G->vexnum; j++)
        {
            //要把大量的0以及65535滤除并且由于对称性，所以只打印上三角
            if ((G->arcs[i][j].adj > 0) && (G->arcs[i][j].adj < 65535) && (j >= i))
            {
                edges[k].Begin = i;
                edges[k].End = j;
                edges[k].Weight = G->arcs[i][j].adj;
                k++;
            }
        }
    }
    for (int i = 0; i < G->arcnum; i++)
    {
        printf("(%d,%d,%d)", edges[i].Begin, edges[i].End, edges[i].Weight);
    }
    printf("\n");
    //对找出来的带权值边进行冒泡排序
    BubbleSort(edges, G->arcnum);
}

//查找连线顶点的尾部下标
int Find(int *parent, int f)
{
    while (parent[f] > 0)
    {
        f = parent[f];
    }
    return f;
}

//Kruskal算法生成最小生成树
void MiniSpanTree_Kruskal(MGraph G)
{
    Edge edges[MAXEDGE]; //定义边集数组
    int parent[MAXVEX];  //定义一数组用来判断边与边是否形成回路

    MatrixToArray(edges, &G); //将邻接矩阵G转化为边集数组，并且对边集数组按照权值进行冒泡排序

    PrintArray(edges, G.arcnum); //打印边集数组

    for (int i = 0; i < G.vexnum; i++)
    {
        parent[i] = 0; //初始化数组值为0
    }

    for (int i = 0; i < G.arcnum; i++) //循环每一条边(对边集数组做循环遍历)
    {
        int n = Find(parent, edges[i].Begin);
        int m = Find(parent, edges[i].End);

        if (n != m) //假如n与m不相等，说明此边没有与现有生成树形成回路
        {
            parent[n] = m; //将此边的结尾顶点放入下标为起点的parent中(parent[起始]=结尾)，表示此边已经在生成树集合中
            printf("(%d,%d,%d)", edges[i].Begin, edges[i].End, edges[i].Weight);
        }
    }
}

int main()
{
    MGraph G;
    CreateUDN(&G); //构造无向树
    PrintGrapth(G);
    MiniSpanTree_Kruskal(G); //对无向树使用Kruskal算法生成最小生成树

    return 0;
}
