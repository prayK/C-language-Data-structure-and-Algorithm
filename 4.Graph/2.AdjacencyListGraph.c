#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20 //最大顶点个数
#define VertexType int    //顶点数据的类型

//边表结构体
typedef struct ArcNode
{
  int adjvex;              //邻接点域，存储该点对应的下标
  struct ArcNode *nextarc; //指向下一个邻接点的指针
} ArcNode;

//顶点表结构体
typedef struct VNode
{
  VertexType InDegree; //对于有向图每个顶点还有入度和出度
  VertexType OutDegree;
  VertexType data;                //顶点的数据域
  ArcNode *firstarc;              //指向邻接点的指针
} VNode, AdjList[MAX_VERTEX_NUM]; //存储各链表头结点的数组

//图结构体
typedef struct
{
  AdjList vertices;   //图中顶点的数组
  int vexnum, arcnum; //记录图中顶点数和边或弧数
} ALGraph;

//用邻接表构造有向图
void CreateDG(ALGraph *G)
{
  printf("请输入节点数目和边(弧)的数目(用逗号隔开):");
  scanf("%d, %d", &(G->vexnum), &(G->arcnum)); //输入顶点数、弧(边)数

  for (int i = 0; i < G->vexnum; i++)
  {
    printf("请输入第%d个顶点值:", i + 1);
    scanf("%d", &(G->vertices[i].data)); //输入每个顶点本身的值
    G->vertices[i].firstarc = NULL;      //将边表置为空表
    G->vertices[i].InDegree = 0;         //初始化每个顶点入度为0
    G->vertices[i].OutDegree = 0;        //初始化每个顶点出度为0
  }

  //建立边表(前插法)
  for (int i = 0; i < G->arcnum; i++)
  {
    int vi, vj;
    printf("请输入两个相互连接的顶点(弧头,弧尾)值(用逗号隔开):");
    scanf("%d,%d", &vi, &vj);

    ArcNode *e = (ArcNode *)malloc(sizeof(ArcNode)); //向内存申请空间生成边表节点
    e->adjvex = vj;                                  //邻接顶点序号为vj
    e->nextarc = G->vertices[vi].firstarc;           //将e指针指向当前顶点指向的节点
    G->vertices[vi].firstarc = e;                    //将当前顶点的指针指向e
    G->vertices[vi].OutDegree++;                     //弧尾出度加一
    G->vertices[vj].InDegree++;                      //弧头入度加一
  }
}

int main()
{
  ALGraph G;       //建立一个图的变量
  CreateDN(&G);    //调用创建函数，传入地址参数
  PrintGrapth(&G); //输出图的二阶矩阵

  return 0;
}
