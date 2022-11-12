/*AOV网的一个应用就是拓扑排序*/
#include <stdio.h>
#include <stdlib.h>

#define  MAX_VERTEX_NUM 20  //最大顶点个数
#define  VertexType int     //顶点数据的类型

//边表结构体
typedef struct ArcNode
{
    int adjvex;             //邻接点域，存储该点对应的下标
    struct ArcNode* nextarc;//指向下一个邻接点的指针
}ArcNode;

//顶点表结构体
typedef struct VNode
{
    VertexType InDegree;         //对于有向图每个顶点还有入度和出度
    VertexType OutDegree;
    VertexType data;             //顶点的数据域
    ArcNode* firstarc;           //指向邻接点的指针
}VNode, AdjList[MAX_VERTEX_NUM]; //存储各链表头结点的数组

//图结构体
typedef struct
{
    AdjList vertices;   //图中顶点的数组
    int vexnum, arcnum; //记录图中顶点数和边或弧数
}ALGraph;


//用邻接表构造有向图
void CreateDG(ALGraph* G)
{
    printf("请输入节点数目和边(弧)的数目(用逗号隔开):");
    scanf("%d, %d", &(G->vexnum), &(G->arcnum));//输入顶点数、弧(边)数

    for(int i=0; i<G->vexnum; i++)
    {
        printf("请输入第%d个顶点值:", i+1);
        scanf("%d", &(G->vertices[i].data));//输入每个顶点本身的值
        G->vertices[i].firstarc = NULL;     //将边表置为空表
        G->vertices[i].InDegree = 0;        //初始化每个顶点入度为0
        G->vertices[i].OutDegree = 0;       //初始化每个顶点出度为0
    }

    //建立边表(前插法)
    for(int i=0; i<G->arcnum; i++)
    {
        int vi, vj;
        printf("请输入两个相互连接的顶点(弧头,弧尾)值(用逗号隔开):");
        scanf("%d,%d", &vi, &vj);

        ArcNode* e = (ArcNode*)malloc(sizeof(ArcNode));//向内存申请空间生成边表节点
        e->adjvex = vj;                       //邻接顶点序号为vj
        e->nextarc = G->vertices[vi].firstarc;//将e指针指向当前顶点指向的节点
        G->vertices[vi].firstarc = e;         //将当前顶点的指针指向e
        G->vertices[vi].OutDegree++;          //弧尾出度加一
        G->vertices[vj].InDegree++;           //弧头入度加一
    }
}

//输出图
void PrintGrapth(ALGraph G)
{
    printf("邻接表为:\n");
    for(int i=0; i<G.vexnum; i++)
    {
        printf("%d->", i);
        while(1)
        {
            if(G.vertices[i].firstarc == NULL)
            {
                printf("^");
                break;
            }
            printf("%d->", G.vertices[i].firstarc->adjvex);
            G.vertices[i].firstarc = G.vertices[i].firstarc->nextarc;//迭代
        }
        printf("\n");
    }
    printf("各个顶点的入度分别为: ");
    for(int i=0; i<G.vexnum; i++)
    {
        printf("%d ", G.vertices[i].InDegree);
    }
    printf("\n");
    printf("各个顶点的出度分别为: ");
    for(int i=0; i<G.vexnum; i++)
    {
        printf("%d ", G.vertices[i].OutDegree);
    }
    printf("\n");
}

//拓扑排序，若无回路，则输出拓扑排序并返回1，否则回路返回0
int TopologicalSort(ALGraph* G)
{
    int top = 0;    //用于栈指针下标
    int count = 0;  //用于统计输出顶点的个数
    int* stack = (int*)malloc(G->vexnum * sizeof(int));//建栈存储入度为0的顶点

    for(int i=0; i<G->vexnum; i++)
    {
        if(G->vertices[i].InDegree == 0)
        {
            stack[top++] = i;   //将入度为0的顶点入栈
        }
    }

    //对每个入度为0的顶点，把与他们的相连接的顶点找出来
    while(top != 0)
    {
        int gettop = stack[--top];//出栈
        printf("%d->", G->vertices[gettop].data);//打印此顶点
        count++;    //统计输出顶点数

        //对此顶点弧表遍历，将弧删除，并将弧头的入度减一
        for(ArcNode* e = G->vertices[gettop].firstarc; e!=NULL; e=e->nextarc)
        {
            G->vertices[e->adjvex].InDegree--;       //将e->adjvex号顶点邻接点的入度减一
            if(G->vertices[e->adjvex].InDegree == 0) //先自减，再判断入度是不是0，判断是为了入栈
            {
                stack[top++] = e->adjvex;           //若为0则入栈，以便于下次循环输出
            }
        }
    }
    if(count < G->vexnum)//如果count小于count数，说明存在环
    {
        printf("该图有环路\n");
        return 0;
    }
    else
    {
        return 1;
    }
}

int main()
{
    ALGraph G;          //建立一个图的变量
    CreateDG(&G);       //调用创建函数，传入地址参数
    PrintGrapth(G);    //输出图的二阶矩阵
    TopologicalSort(&G); //拓扑排序

    return 0;
}

/*
6,8
0
1
2
3
4
5
0,1,1
0,3,2
0,2,4
2,1,3
2,4,6
3,4,7
5,3,5
5,4,8

503214
*/