#include <bits/stdc++.h>
using namespace std;

#define MAX_VERtEX_NUM 20 //顶点的最大个数
#define VRType int        //表示顶点之间的关系的变量类型
#define InfoType char     //存储弧或者边额外信息的指针变量类型
#define VertexType int    //图中顶点的数据类型

typedef enum
{
    DG = 1,
    DN,
    UDG,
    UDN
} GraphKind; //枚举图的 4 种类型

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
    GraphKind kind;                  //记录图的种类
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

//构造有向图
void CreateDG(MGraph *G)
{
    printf("请输入顶点数目和边(弧)的数目(用逗号隔开):");
    //输入图含有的顶点数和弧的个数
    scanf("%d,%d", &(G->vexnum), &(G->arcnum));
    //依次输入顶点本身的数据
    for (int i = 0; i < G->vexnum; i++)
    {
        printf("请输入第%d个顶点值:", i + 1);
        scanf("%d", &(G->vexs[i]));
    }
    //初始化二维矩阵，全部归0，指针指向NULL
    for (int i = 0; i < G->vexnum; i++)
    {
        for (int j = 0; j < G->vexnum; j++)
        {
            G->arcs[i][j].adj = 0;
            G->arcs[i][j].info = NULL;
        }
    }
    //在二维数组中添加弧的数据
    for (int i = 0; i < G->arcnum; i++)
    {
        int v1, v2;
        //输入弧头和弧尾
        printf("请输入弧头和弧尾值(用逗号隔开):");
        scanf("%d,%d", &v1, &v2);

        //确定顶点位置
        int n = LocateVex(G, v1);
        int m = LocateVex(G, v2);

        printf("这两个点在一维矩阵中的位置分别为：");
        printf("%d,%d。", n, m);
        printf("即邻接矩阵中的arcs[%d][%d]位置将会被置一\n", n, m);

        //排除错误数据
        if ((m == -1) || (n == -1))
        {
            printf("no this vertex\n");
            return;
        }
        //将正确的弧的数据加入二维数组
        G->arcs[n][m].adj = 1;
    }
}

//构造无向图
void CreateUDG(MGraph *G)
{
    printf("请输入节点数目和边(弧)的数目(用逗号隔开):");
    scanf("%d, %d", &(G->vexnum), &(G->arcnum)); //输入顶点数、弧(边)数
    for (int i = 0; i < G->vexnum; i++)
    {
        printf("请输入第%d个顶点值:", i + 1);
        scanf("%d", &(G->vexs[i])); //输入每个顶点本身的值
    }
    //先初始化每个顶点之间没有联系
    for (int i = 0; i < G->vexnum; i++)
    {
        for (int j = 0; j < G->vexnum; j++)
        {
            G->arcs[i][j].adj = 0;
            G->arcs[i][j].info = NULL;
        }
    }
    //找到相连接顶点在存储顶点矩阵中的位置，不然在二维矩阵中无法得知要把哪个位置置一
    for (int i = 0; i < G->arcnum; i++)
    {
        int v1, v2;
        printf("请输入两个相互连接的顶点值(用逗号隔开):");
        scanf("%d,%d", &v1, &v2);

        int n = LocateVex(G, v1);
        int m = LocateVex(G, v2);

        printf("这两个点在一维矩阵中的位置分别为：");
        printf("%d,%d。", n, m);
        printf("即邻接矩阵中的arcs[%d][%d]位置将会被置一\n", n, m);

        if ((m == -1) || (n == -1))
        {
            printf("no this vertex\n");
            return;
        }
        G->arcs[n][m].adj = 1;
        G->arcs[m][n].adj = 1; //无向图的二阶矩阵沿主对角线对称
    }
}

//构造有向网，和有向图不同的是二阶矩阵中存储的是权值。
void CreateDN(MGraph *G)
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
            G->arcs[i][j].adj = 0;
            G->arcs[i][j].info = NULL;
        }
    }
    for (int i = 0; i < G->arcnum; i++)
    {
        int v1, v2, w;
        printf("请输入弧头、弧尾值和权值(用逗号隔开):");
        scanf("%d,%d,%d", &v1, &v2, &w);

        int n = LocateVex(G, v1);
        int m = LocateVex(G, v2);

        printf("这两个点在一维矩阵中的位置分别为：");
        printf("%d,%d。", n, m);
        printf("即邻接矩阵中的arcs[%d][%d]位置将会被置%d\n", n, m, w);

        if ((m == -1) || (n == -1))
        {
            printf("no this vertex\n");
            return;
        }
        G->arcs[n][m].adj = w;
    }
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
            G->arcs[i][j].adj = 0;
            G->arcs[i][j].info = NULL;
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
        printf("即邻接矩阵中的arcs[%d][%d]位置将会被置%d\n", n, m, w);

        if ((m == -1) || (n == -1))
        {
            printf("no this vertex\n");
            return;
        }
        G->arcs[n][m].adj = w;
        G->arcs[m][n].adj = w; //矩阵对称
    }
}

//创建
void CreateGraph(MGraph *G)
{
    //选择图的类型
    printf("请输入要构造的图类型:");
    scanf("%d", &(G->kind));

    //根据所选类型，调用不同的函数实现构造图的功能
    switch (G->kind)
    {
    case DG:
        return CreateDG(G);
        break; //0 有向图
    case DN:
        return CreateUDG(G);
        break; //1 无向图
    case UDG:
        return CreateDN(G);
        break; //2 有向网
    case UDN:
        return CreateUDN(G);
        break; //3 无向网
    default:
        break;
    }
}

//输出函数
void PrintGraph(MGraph G)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        for (int j = 0; j < G.vexnum; j++)
        {
            printf("%d ", G.arcs[i][j].adj);
        }
        printf("\n");
    }
}

int main()
{
    MGraph G;        //建立一个图的变量
    CreateGraph(&G); //调用创建函数，传入地址参数

    printf("邻接矩阵为:\n");
    PrintGraph(G); //输出图的二阶矩阵

    return 0;
}
