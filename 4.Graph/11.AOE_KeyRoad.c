#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20 //最大顶点个数
#define VertexType int    //顶点数据的类型

//边表结构体
typedef struct ArcNode
{
    int weight;              //权重
    int adjvex;              //邻接点域，存储该点对应的下标
    struct ArcNode *nextarc; //指向下一个邻接点的指针
} ArcNode;

//顶点表结构体
typedef struct VNode
{
    VertexType InDegree; //对于有向图每个顶点还有入度和出度
    VertexType OutDegree;
    VertexType data;              //顶点的数据域
    ArcNode *firstarc;            //指向邻接点的指针
} VNode, AdjList[MAX_VERTEX_NUM]; //存储各链表头结点的数组

//图结构体
typedef struct
{
    AdjList vertices;   //图中顶点的数组
    int vexnum, arcnum; //记录图中顶点数和边或弧数
} ALGraph;

//其实你要注意，每个在终端打印出来的都是下标值。比如显示1，但是这是下标值，内部可能是V10。
//为了显示方便所以在测试代码中让下标值与内部一致
//用邻接表构造有向图
void CreateDG(ALGraph *G)
{
    //printf("请输入节点数目和边(弧)的数目(用逗号隔开):");
    scanf("%d, %d", &(G->vexnum), &(G->arcnum)); //输入顶点数、弧(边)数

    for (int i = 0; i < G->vexnum; i++)
    {
        //printf("请输入第%d个顶点值:", i+1);
        scanf("%d", &(G->vertices[i].data)); //输入每个顶点本身的值
        G->vertices[i].firstarc = NULL;      //将边表置为空表
        G->vertices[i].InDegree = 0;         //初始化每个顶点入度为0
        G->vertices[i].OutDegree = 0;        //初始化每个顶点出度为0
    }

    //建立边表(前插法)
    for (int i = 0; i < G->arcnum; i++)
    {
        int vi, vj, w;
        //printf("请输入两个相互连接的顶点和权重(弧头,弧尾，权重)值(用逗号隔开):");
        scanf("%d,%d,%d", &vi, &vj, &w);

        ArcNode *e = (ArcNode *)malloc(sizeof(ArcNode)); //向内存申请空间生成边表节点
        e->weight = w;
        e->adjvex = vj;                        //邻接顶点序号为vj
        e->nextarc = G->vertices[vi].firstarc; //将e指针指向当前顶点指向的节点
        G->vertices[vi].firstarc = e;          //将当前顶点的指针指向e
        G->vertices[vi].OutDegree++;           //弧尾出度加一
        G->vertices[vj].InDegree++;            //弧头入度加一
    }
}

int *etv;    //earliest time of vertex，事件的最早发生时间（上限）
int *ltv;    //latest time of vertex，事件的最晚发生时间（下限）
int *stack2; //用于存储拓扑排序的栈
int top2;    //用于stack2的指针

//拓扑排序，若无回路，则输出拓扑排序并返回1，否则回路返回0
int TopologicalSort(ALGraph *G)
{
    int top = 0;                                         //用于栈指针下标
    int count = 0;                                       //用于统计输出顶点的个数
    int *stack = (int *)malloc(G->vexnum * sizeof(int)); //建栈存储入度为0的顶点

    for (int i = 0; i < G->vexnum; i++)
    {
        if (G->vertices[i].InDegree == 0)
        {
            stack[top++] = i; //将入度为0的顶点入栈
        }
    }

    //关键路径算法专属代码
    {
        top2 = 0;
        etv = (int *)malloc(G->vexnum * sizeof(int)); //事件最早发生时间
        for (int i = 0; i < G->vexnum; i++)
        {
            etv[i] = 0;
        }
        stack2 = (int *)malloc(G->vexnum * sizeof(int));
    }

    //对每个入度为0的顶点，把与他们的相连接的顶点找出来
    while (top != 0)
    {
        int gettop = stack[--top]; //出栈
        //printf("%d->", G->vertices[gettop].data);//打印此顶点
        count++; //统计输出顶点数

        //关键路径算法专属代码
        {
            stack2[top2++] = gettop; //将弹出的顶点序号压入存储拓扑序列的栈
            if (top2 == G->vexnum)   //为什么要这么处理？因为top2到G->vexnum是就会导致数组越界了
            {
                top2 = G->vexnum - 1;
            }
        }

        //对此顶点弧表遍历，将弧删除，并将弧头的入度减一
        for (ArcNode *e = G->vertices[gettop].firstarc; e != NULL; e = e->nextarc)
        {
            G->vertices[e->adjvex].InDegree--;        //将e->adjvex号顶点邻接点的入度减一
            if (G->vertices[e->adjvex].InDegree == 0) //先自减，再判断入度是不是0，判断是为了入栈
            {
                stack[top++] = e->adjvex; //若为0则入栈，以便于下次循环输出
            }

            //关键路径算法专属代码
            {
                if ((etv[gettop] + e->weight) > etv[e->adjvex]) //求各顶点事件最早发生时间值
                {
                    etv[e->adjvex] = etv[gettop] + e->weight;
                }
            }
        }
    }

    if (count < G->vexnum) //如果count小于count数，说明存在环
    {
        printf("该图有环路\n");
        return 0;
    }
    else
    {
        printf("\n");
        return 1;
    }
}

//求关键路径，G为有向网，输出G的各项关键活动
void CriticalPath(ALGraph *G)
{
    int lte, ete; //声明活动最早发生时间和最迟发生时间变量

    TopologicalSort(G);                           //求拓扑序列，计算书组etv和stack2的值
    ltv = (int *)malloc(G->vexnum * sizeof(int)); //事件最晚发生时间
    for (int i = 0; i < G->vexnum; i++)
    {
        ltv[i] = etv[G->vexnum - 1]; //初始化ltv，用etv数组最后一个值去初始化ltv数组里面的全部值
    }
    //计算ltv(ltv的值要从汇点往源点反推)
    while (top2 >= 0)
    {
        //这里注意，因为循环条件中top!=0，但是stack2[0] == 源点，亦即有值，但是不重要，lte[源点] == 0
        //但是为了让lte数组完整，所以改了条件
        int gettop = stack2[top2--]; //将拓扑序列出栈，现进后出

        //求各顶点事件的最迟发生时间ltv值
        for (ArcNode *e = G->vertices[gettop].firstarc; e != NULL; e = e->nextarc)
        {
            if ((ltv[e->adjvex] - e->weight) < ltv[gettop]) //求各顶点事件的最迟发生时间ltv值
            {
                ltv[gettop] = ltv[e->adjvex] - e->weight;
            }
        }
    }
    for (int j = 0; j < G->vexnum; j++) //求ete，lte和关键活动
    {
        for (ArcNode *e = G->vertices[j].firstarc; e != NULL; e = e->nextarc)
        {
            ete = etv[j];                     //活动最早发生时间
            lte = ltv[e->adjvex] - e->weight; //活动最迟发生时间
            if (ete == lte)
            {
                printf("<V%d,V%d>length: %d\n", G->vertices[j].data, G->vertices[e->adjvex].data, e->weight);
            }
        }
    }
}

//输出图(网)的邻接表
void PrintGrapth(ALGraph G)
{
    printf("邻接表为:\n");
    for (int i = 0; i < G.vexnum; i++)
    {
        printf("%d->", i);
        while (1)
        {
            if (G.vertices[i].firstarc == NULL)
            {
                printf("^");
                break;
            }
            printf("%d->", G.vertices[i].firstarc->adjvex);
            G.vertices[i].firstarc = G.vertices[i].firstarc->nextarc; //迭代
        }
        printf("\n");
    }
    printf("各个顶点的入度分别为: ");
    for (int i = 0; i < G.vexnum; i++)
    {
        printf("%d ", G.vertices[i].InDegree);
    }
    printf("\n");
    printf("各个顶点的出度分别为: ");
    for (int i = 0; i < G.vexnum; i++)
    {
        printf("%d ", G.vertices[i].OutDegree);
    }
    printf("\n");
}

//输出拓扑排序后的序列图，各个顶点最早发生事件数组，各个顶点最晚发生事件数组
void PrintArray(ALGraph G)
{
    printf("\n拓扑排序后的顺序为:\n");
    for (int i = 0; i < G.vexnum; i++)
        printf("%d ", stack2[i]);

    printf("\n最早发生事件数组(etv)为:\n");
    for (int i = 0; i < G.vexnum; i++)
        printf("%d ", etv[i]);

    printf("\n最晚发生事件数组(ltv)为:\n");
    for (int i = 0; i < G.vexnum; i++)
        printf("%d ", ltv[i]);
}

int main()
{
    ALGraph G;      //建立一个图的变量
    CreateDG(&G);   //调用创建函数，传入地址参数
    PrintGrapth(G); //输出图(网)的邻接表
    //TopologicalSort(&G);//拓扑排序
    CriticalPath(&G); //求关键路径
    PrintArray(G);    //打印拓扑排序后的序列图，最早发生事件数组，最晚发生事件数组

    return 0;
}

/*
10,13
0
1
2
3
4
5
6
7
8
9
0,1,3
0,2,4
1,3,5
1,4,6
2,3,8
2,5,7
3,4,3
4,6,9
4,7,4
5,7,6
6,9,2
7,8,5
8,9,3
*/