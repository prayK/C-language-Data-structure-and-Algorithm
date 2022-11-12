#include <stdio.h>
#include <stdlib.h>

#define MAX_VERtEX_NUM 20 //�����������
#define VRType int        //��ʾ����֮��Ĺ�ϵ�ı�������
#define InfoType char     //�洢�����߱߶�����Ϣ��ָ���������
#define VertexType int    //ͼ�ж������������
#define MAXVEX 10         //ͼ�ж������������
#define MAXEDGE 10

typedef struct
{
    int Begin;
    int End;
    int Weight;
} Edge;

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

//��ӡ�߼�����
void PrintArray(Edge edges[], int N)
{
    printf("�߼�����Ϊ: \n");
    for (int i = 0; i < N; i++)
    {
        printf("(%d,%d,%d)", edges[i].Begin, edges[i].End, edges[i].Weight);
    }
    printf("\n");
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

//����ֵ����
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

//ð�������㷨
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

//���ڽӾ���Gת��Ϊ�߼����飬���ҶԱ߼��������ð������
void MatrixToArray(Edge edges[], MGraph *G)
{
    int k = 0;

    //�Ȱ����д�Ȩֵ���ҳ���
    for (int i = 0; i < G->vexnum; i++)
    {
        for (int j = 0; j < G->vexnum; j++)
        {
            //Ҫ�Ѵ�����0�Լ�65535�˳��������ڶԳ��ԣ�����ֻ��ӡ������
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
    //���ҳ����Ĵ�Ȩֵ�߽���ð������
    BubbleSort(edges, G->arcnum);
}

//�������߶����β���±�
int Find(int *parent, int f)
{
    while (parent[f] > 0)
    {
        f = parent[f];
    }
    return f;
}

//Kruskal�㷨������С������
void MiniSpanTree_Kruskal(MGraph G)
{
    Edge edges[MAXEDGE]; //����߼�����
    int parent[MAXVEX];  //����һ���������жϱ�����Ƿ��γɻ�·

    MatrixToArray(edges, &G); //���ڽӾ���Gת��Ϊ�߼����飬���ҶԱ߼����鰴��Ȩֵ����ð������

    PrintArray(edges, G.arcnum); //��ӡ�߼�����

    for (int i = 0; i < G.vexnum; i++)
    {
        parent[i] = 0; //��ʼ������ֵΪ0
    }

    for (int i = 0; i < G.arcnum; i++) //ѭ��ÿһ����(�Ա߼�������ѭ������)
    {
        int n = Find(parent, edges[i].Begin);
        int m = Find(parent, edges[i].End);

        if (n != m) //����n��m����ȣ�˵���˱�û���������������γɻ�·
        {
            parent[n] = m; //���˱ߵĽ�β��������±�Ϊ����parent��(parent[��ʼ]=��β)����ʾ�˱��Ѿ���������������
            printf("(%d,%d,%d)", edges[i].Begin, edges[i].End, edges[i].Weight);
        }
    }
}

int main()
{
    MGraph G;
    CreateUDN(&G); //����������
    PrintGrapth(G);
    MiniSpanTree_Kruskal(G); //��������ʹ��Kruskal�㷨������С������

    return 0;
}
