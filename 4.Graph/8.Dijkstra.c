#include <stdio.h>
#include <stdlib.h>

#define MAX_VERtEX_NUM 20 //顶点的最大个数
#define VRType int        //表示顶点之间的关系的变量类型
#define InfoType char     //存储弧或者边额外信息的指针变量类型
#define VertexType int    //图中顶点的数据类型
#define INFINITY 65535

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
    Function: 迪杰斯特拉算法求最短路径
    brief: Path[v]的值为前驱顶点
    brief: Distance[v]表示V0到V的最短路径长度和
    brief: Final[]标记各顶点是否已经找到最短路径(Final[w]==1表示求得V0到Vw的最短路径)

    brief: 这个算法还有问题，当前只能从V0开始，有待解决
*/
void Dijkstra(MGraph G, int v0, int Final[], int Path[], int Distance[])
{
  int k = 0;

  //初始化数据
  for (int i = 0; i < G.vexnum; i++)
  {
    Final[i] = 0;                                       //初始化每个顶点之间还没有找到最短路径
    Distance[i] = G.arcs[v0][i].adj;                    //将与V0点有连线的顶点加上权值
    Path[i] = (G.arcs[v0][i].adj == INFINITY) ? -1 : 0; //初始化路径前驱，与V0之间没有边就是-1，有边那么前驱就是V0的0
  }
  Path[0] = -1; // V0没有前驱
  Final[0] = 1; // V0至V0不需要路径

  //开始主循环，每次求得V0到某个V顶点的最短路径
  for (int i = 0; i < G.vexnum; i++)
  {
    /*
    {
        printf("V%d->", v0);//打印起始点
        if(i<(G.vexnum-1) && (i>v0))
            printf("V%d->", k);
        if(i==(G.vexnum-1))
            printf("V%d", k);//打印路径的代码，为什么放在这是为了将k==0时打印进去
    }
    */
    (i < (G.vexnum - 1)) ? printf("V%d->", k) : printf("V%d", k); //打印路径的代码，为什么放在这是为了将k==0时打印进去

    int Min = INFINITY;                //当前所知离V0顶点的最近距离
    for (int j = 0; j < G.vexnum; j++) //寻找离V0最近的顶点
    {
      //如果V0到Vj之间还没有找到最短距离，并且V0与Vj之间的距离小于之前的最小值
      if ((Final[j] == 0) && (Distance[j] < Min))
      {
        Min = Distance[j]; // Vj顶点离V0更近
        k = j;
      }
    }
    Final[k] = 1; //将目前找到的最近的顶点置一

    //这段代码的目的是在刚才已经找到V0与V1的最短路径基础上，对V1与其他顶点的边进行计算,得到V0与他们的当前最短距离
    for (int j = 0; j < G.vexnum; j++) //修正当前最短路径及距离
    {
      //如果经过v顶点的路径比现在现在这条路径的长度更短的话
      //要知道Distance[v]表示V0到V的最短路径长度和，所以是递增的，当前distance是之前的distance加上当前值
      if ((Final[j] == 0) && (Min + G.arcs[k][j].adj < Distance[j]))
      {                                       //说明找到了更短的路径，修改D[j]和P[j]
        Distance[j] = Min + G.arcs[k][j].adj; //修改当前路径长度
        Path[j] = k;
      }
    }
  }
}

//打印路径(函数还有缺陷也不需要这个函数打印路径了)
void PrintRoad(int path[], int Len)
{
  for (int i = 1; i < Len; i++)
  {
    printf("V%d", path[i]);
    // if
    printf("->");
  }
}

int main(void)
{
  MGraph G;
  CreateUDN(&G);  //构造无向树
  PrintGrapth(G); //打印邻接数组

  int Final[G.vexnum];
  int Path[G.vexnum];     // P[]矩阵，用来存储最短路径下标的数组
  int Distance[G.vexnum]; // D[]矩阵，用来存储最短路径的权值和

  Dijkstra(G, 1, Final, Path, Distance); //迪杰斯特拉算法求最短路径
  // PrintRoad(Path, G.vexnum);//把路径打印出来

  return 0;
}

/*

#include <stdio.h>

#define V 20 //顶点的最大个数
#define INFINITY 65535

typedef struct
{
    int vexs[V];        //存储图中顶点数据
    int arcs[V][V];     //二维数组，记录顶点之间的关系
    int vexnum, arcnum; //记录图的顶点数和弧（边）数
} MGraph;

//根据顶点本身数据，判断出顶点在二维数组中的位置
int LocateVex(MGraph *G, int v)
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

//构造无向有权图
void CreateDG(MGraph *G)
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
            G->arcs[i][j] = INFINITY;
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

        if (m == -1 || n == -1)
        {
            return;
        }
        G->arcs[n][m] = w;
        G->arcs[m][n] = w;
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

//迪杰斯特拉算法，v0表示有向网中起始点所在数组中的下标
void Dijkstra_minTree(MGraph G, int v0, int p[V], int D[V])
{
    int final[V]; //为各个顶点配置一个标记值，用于确认该顶点是否已经找到最短路径  final[x] = 1表示 v0 到 vx 的最短路径已经求得
    //对各数组进行初始化
    for (int v = 0; v < G.vexnum; v++)
    {
        final[v] = 0;
        D[v] = G.arcs[v0][v];
        p[v] = 0;
    }
    //由于以v0位下标的顶点为起始点，所以不用再判断
    D[v0] = 0;
    final[v0] = 1;
    int k = 0;
    for (int i = 0; i < G.vexnum; i++)
    {
        int min = INFINITY;
        //选择到各顶点权值最小的顶点，即为本次能确定最短路径的顶点
        for (int w = 0; w < G.vexnum; w++)
        {
            if ((final[w] == 0) && (D[w] < min))
            {
                k = w;
                min = D[w];
            }
        }
        //设置该顶点的标志位为1，避免下次重复判断
        final[k] = 1;

        //对v0到各顶点的权值进行更新
        for (int w = 0; w < G.vexnum; w++)
        {
            if ((final[w] == 0) && (min + G.arcs[k][w] < D[w]))
            {
                D[w] = min + G.arcs[k][w];
                p[w] = k; //记录各个最短路径上存在的顶点
            }
        }
    }
}

//打印路径(函数还有缺陷也不需要这个函数打印路径了)
void PrintRoad(int path[], int Len)
{
    printf("最短路径为：\n");
    for (int i = 1; i < G.vexnum; i++)
    {
        printf("%d - %d的最短路径中的顶点有：", i, 0);
        printf(" %d-", i);
        int j = i;
        //由于每一段最短路径上都记录着经过的顶点，所以采用嵌套的方式输出即可得到各个最短路径上的所有顶点
        while (P[j] != 0)
        {
            printf("%d-", P[j]);
            j = P[j];
        }
        printf("0\n");
    }
    printf("源点到各顶点的最短路径长度为:\n");
    for (int i = 1; i < G.vexnum; i++)
    {
        printf("%d - %d : %d \n", G.vexs[0], G.vexs[i], D[i]);
    }
}

int main()
{
    MGraph G;
    CreateDG(&G);
    PrintGrapth(G); //打印邻接数组

    int Path[V] = {0};     // 记录顶点 0 到各个顶点的最短的路径
    int Distance[V] = {0}; // 记录顶点 0 到各个顶点的总权值
    Dijkstra_minTree(G, 0, Path, Distance);

    return 0;
}

*/