#include <stdio.h>
#include <stdlib.h>

#define MAX_VERtEX_NUM 20 //顶点的最大个数
#define VRType int        //表示顶点之间的关系的变量类型
#define InfoType char     //存储弧或者边额外信息的指针变量类型
#define VertexType int    //图中顶点的数据类型
#define INFINITY 65535
#define VertexNum 4

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

/*
    Function: Floyd算法求最短路径
    brief: ShortestPath[][G.vexnum]代表顶点到顶点的最短路径权值和的矩阵
    brief: FrontEngine[][G.vexnum]代表对应顶点的最小路径的前驱矩阵
*/
void Floyd(MGraph G, int ShortestPath[][VertexNum], int FrontEngine[][VertexNum])
{
    for (int i = 0; i < G.vexnum; ++i)
    {
        for (int j = 0; j < G.vexnum; ++j)
        {
            ShortestPath[i][j] = G.arcs[i][j].adj; //初始化顶点之间最短路径和矩阵为邻接矩阵
            FrontEngine[i][j] = j;                 //初始化前驱矩阵每一列值为列下标
        }
    }

    for (int k = 0; k < G.vexnum; k++)
    {
        for (int i = 0; i < G.vexnum; i++)
        {
            for (int j = 0; j < G.vexnum; j++)
            {
                //如果经过下标为k顶点路径比原来两点间路径更短，将当前两点间权值设置为更小的一个
                if (ShortestPath[i][j] > ShortestPath[i][k] + ShortestPath[k][j])
                {
                    ShortestPath[i][j] = ShortestPath[i][k] + ShortestPath[k][j];
                    FrontEngine[i][j] = FrontEngine[i][k]; //路径设置经过下标为k的顶点
                }
            }
        }
    }
}

//打印最短路径(还有问题，待修正)
void PrintShortestPath(MGraph G, int ShortestPath[][VertexNum], int FrontEngine[][VertexNum])
{
    for (int i = 0; i < G.vexnum; i++)
    {
        for (int j = i + 1; j < G.vexnum; j++)
        {
            printf("V%d->V%d Weight: ", i, j, ShortestPath[i][j]);
            int k = FrontEngine[i][j]; //获得第一个路径顶点下标
            printf("Path: %d", i);     //打印源点
            while (k != j)             //如果路径顶点下标不是终点
            {
                printf("->%d", k);      //打印路径顶点
                k = ShortestPath[k][j]; //获得下一个路径顶点下标
            }
            printf("->%d\n", j); //打印终点
        }
    }
    printf("\n");
}

int main(void)
{
    MGraph G;
    CreateUDN(&G);  //构造无向树
    PrintGrapth(G); //打印邻接数组

    int ShortestPath[G.vexnum][G.vexnum];
    int FrontEngine[G.vexnum][G.vexnum];

    Floyd(G, ShortestPath, FrontEngine);
    //PrintShortestPath(G, ShortestPath, FrontEngine);

    printf("各顶点间的权值和最短矩阵:\n");
    for (int i = 0; i < G.vexnum; i++)
    {
        for (int j = 0; j < G.vexnum; j++)
        {
            printf("%d ", ShortestPath[i][j]);
        }
        printf("\n");
    }

    printf("各顶点间的前驱矩阵:\n");
    for (int i = 0; i < G.vexnum; i++)
    {
        for (int j = 0; j < G.vexnum; j++)
        {
            printf("%d ", FrontEngine[i][j]);
        }
        printf("\n");
    }

    return 0;
}
