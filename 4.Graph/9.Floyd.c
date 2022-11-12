#include <stdio.h>
#include <stdlib.h>

#define MAX_VERtEX_NUM 20 //�����������
#define VRType int        //��ʾ����֮��Ĺ�ϵ�ı�������
#define InfoType char     //�洢�����߱߶�����Ϣ��ָ���������
#define VertexType int    //ͼ�ж������������
#define INFINITY 65535
#define VertexNum 4

typedef struct
{
    VRType adj;     //������Ȩͼ���� 1 �� 0 ��ʾ�Ƿ����ڣ����ڴ�Ȩͼ��ֱ��ΪȨֵ��
    InfoType *info; //����߶��⺬�е���Ϣָ��
} ArcCell, AdjMatrix[MAX_VERtEX_NUM][MAX_VERtEX_NUM];

typedef struct
{
    VertexType vexs[MAX_VERtEX_NUM]; //�洢ͼ�ж�������
    AdjMatrix arcs;                  //��ά���飬��¼����֮��Ĺ�ϵ
    int vexnum, arcnum;              //��¼ͼ�Ķ������ͻ����ߣ���
} MGraph;

//���ݶ��㱾�����ݣ��ҵ�������һά�����е�λ�ã������жϳ������ڶ�ά�����е�λ��
int LocateVex(MGraph *G, VertexType v)
{
    int i = 0;
    //����һά���飬�ҵ�����v
    for (; i < G->vexnum; i++)
    {
        if (G->vexs[i] == v)
        {
            break;
        }
    }
    //����Ҳ����������ʾ��䣬����-1
    if (i > G->vexnum)
    {
        printf("no such vertex.\n");
        return -1;
    }
    return i;
}

//������������������ͼΨһ��������Ƕ��׾����д洢����Ȩֵ
void CreateUDN(MGraph *G)
{
    printf("������ڵ���Ŀ�ͱ�(��)����Ŀ(�ö��Ÿ���):");
    scanf("%d,%d", &(G->vexnum), &(G->arcnum));

    for (int i = 0; i < G->vexnum; i++)
    {
        printf("�������%d������ֵ:", i + 1);
        scanf("%d", &(G->vexs[i]));
    }
    for (int i = 0; i < G->vexnum; i++)
    {
        for (int j = 0; j < G->vexnum; j++)
        {
            G->arcs[i][j].adj = 65535; //����Ҫ����Ϊ65535���޸�Prim�е��㷨����Խ������65535�޸�Ϊ0
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

        printf("�����������໥���ӵĶ���ֵ��Ȩֵ(�ö��Ÿ���):");
        scanf("%d,%d,%d", &v1, &v2, &w);

        int n = LocateVex(G, v1);
        int m = LocateVex(G, v2);

        printf("����������һά�����е�λ�÷ֱ�Ϊ��");
        printf("%d,%d��", n, m);
        printf("���ڽӾ����е�arcs[%d][%d]λ�ý��ᱻ��Ϊ%d\n", n, m, w);

        if ((m == -1) || (n == -1))
        {
            printf("no this vertex\n");
            return;
        }
        G->arcs[n][m].adj = w;
        G->arcs[m][n].adj = w; //����Գ�
    }
}

//����ڽӾ�����
void PrintGrapth(MGraph G)
{
    printf("�ڽӾ���Ϊ: \n");
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
    Function: Floyd�㷨�����·��
    brief: ShortestPath[][G.vexnum]�����㵽��������·��Ȩֵ�͵ľ���
    brief: FrontEngine[][G.vexnum]�����Ӧ�������С·����ǰ������
*/
void Floyd(MGraph G, int ShortestPath[][VertexNum], int FrontEngine[][VertexNum])
{
    for (int i = 0; i < G.vexnum; ++i)
    {
        for (int j = 0; j < G.vexnum; ++j)
        {
            ShortestPath[i][j] = G.arcs[i][j].adj; //��ʼ������֮�����·���;���Ϊ�ڽӾ���
            FrontEngine[i][j] = j;                 //��ʼ��ǰ������ÿһ��ֵΪ���±�
        }
    }

    for (int k = 0; k < G.vexnum; k++)
    {
        for (int i = 0; i < G.vexnum; i++)
        {
            for (int j = 0; j < G.vexnum; j++)
            {
                //��������±�Ϊk����·����ԭ�������·�����̣�����ǰ�����Ȩֵ����Ϊ��С��һ��
                if (ShortestPath[i][j] > ShortestPath[i][k] + ShortestPath[k][j])
                {
                    ShortestPath[i][j] = ShortestPath[i][k] + ShortestPath[k][j];
                    FrontEngine[i][j] = FrontEngine[i][k]; //·�����þ����±�Ϊk�Ķ���
                }
            }
        }
    }
}

//��ӡ���·��(�������⣬������)
void PrintShortestPath(MGraph G, int ShortestPath[][VertexNum], int FrontEngine[][VertexNum])
{
    for (int i = 0; i < G.vexnum; i++)
    {
        for (int j = i + 1; j < G.vexnum; j++)
        {
            printf("V%d->V%d Weight: ", i, j, ShortestPath[i][j]);
            int k = FrontEngine[i][j]; //��õ�һ��·�������±�
            printf("Path: %d", i);     //��ӡԴ��
            while (k != j)             //���·�������±겻���յ�
            {
                printf("->%d", k);      //��ӡ·������
                k = ShortestPath[k][j]; //�����һ��·�������±�
            }
            printf("->%d\n", j); //��ӡ�յ�
        }
    }
    printf("\n");
}

int main(void)
{
    MGraph G;
    CreateUDN(&G);  //����������
    PrintGrapth(G); //��ӡ�ڽ�����

    int ShortestPath[G.vexnum][G.vexnum];
    int FrontEngine[G.vexnum][G.vexnum];

    Floyd(G, ShortestPath, FrontEngine);
    //PrintShortestPath(G, ShortestPath, FrontEngine);

    printf("��������Ȩֵ����̾���:\n");
    for (int i = 0; i < G.vexnum; i++)
    {
        for (int j = 0; j < G.vexnum; j++)
        {
            printf("%d ", ShortestPath[i][j]);
        }
        printf("\n");
    }

    printf("��������ǰ������:\n");
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
