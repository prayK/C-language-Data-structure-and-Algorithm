#include <stdio.h>
#include <stdlib.h>

#define MAX_VERtEX_NUM 20 //�����������
#define VRType int        //��ʾ����֮��Ĺ�ϵ�ı�������
#define InfoType char     //�洢�����߱߶�����Ϣ��ָ���������
#define VertexType int    //ͼ�ж������������
#define MAXVEX 10         //ͼ�ж������������

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

//Prim �㷨������С������
void MiniSpanTree_Prim(MGraph G)
{
    int lowcost[MAXVEX]; //������ض���ߵ�Ȩֵ
    int adjvex[MAXVEX];  //������ض�����±�

    //��������v0���ӵĶ���ıߵ�Ȩֵ��������
    for (int i = 0; i < G.vexnum; i++)
    {
        lowcost[i] = G.arcs[0][i].adj;
        adjvex[i] = 0; //��ʼ����Ϊ0
    }
    //������С�������Ĺ���
    for (int i = 1; i < G.vexnum; i++) //�Ӽ���A(������)��һ��һ���� ��ȥ�Ƚ�
    {
        int min = 65535; //��ʼ����СȨֵΪ�����
        int k = 0;       //k�������洢��СȨֵ�Ķ�������

        //��δ�����Ϊ���ҵ���ǰ�������Ȩֵ��С�ı�
        for (int j = 1; j < G.vexnum; j++) //�ҵ�����A�����е㵽����B�����е�֮�����Сֵ��Ȼ��B�е��Ǹ�������������
        {
            if ((lowcost[j] != 0) && (lowcost[j] < min)) //���Ȩֵ��Ϊ0��ȨֵС��min
            {
                min = lowcost[j]; //���µ�ǰȨֵΪ��СȨֵ
                k = j;            //���µ�ǰȨֵ����
            }
        }

        printf("(%d,%d)", adjvex[k], k); //��ӡ��ǰ�������Ȩֵ��С�ı�
        lowcost[k] = 0;                  //����ǰ�����Ȩֵ����Ϊ0,��ʾ�˶�����������С������

        //������һ��Ӧ�ñ��������еĶ���
        for (int j = 1; j < G.vexnum; j++)
        {
            //����±�Ϊk(�Ѿ�����������)�Ķ���߼���ȨֵС���Ѵ��ڵ�Ȩֵ(��ǰһ�������������Ķ���)
            //����k�е�ֵ�ó�����ǰһ���ڵ�(����v0)�ĸ���Ȩֵ���бȽ�,����lowcost���飬��������ڶ���ѭ������һ������ڵ�
            if ((lowcost[j] != 0) && (G.arcs[k][j].adj < lowcost[j]))
            {
                lowcost[j] = G.arcs[k][j].adj; //����С��Ȩֵ���� lowcost ��Ӧλ��
                adjvex[j] = k;                 //�����k��ʾ���ڵڼ����ڵ㴦�������
            }
        }
    }
}

//��ӡ�ڽӾ���
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
