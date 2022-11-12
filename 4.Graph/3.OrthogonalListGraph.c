#include <stdio.h>

#define MAX_VERTEX_NUM 20
#define InfoType int //ͼ�л�������Ϣ����������
#define VertexType int

typedef struct ArcBox
{
    int tailvex, headvex;        //��β����ͷ��Ӧ�����������е�λ���±�
    struct ArcBox *hlik, *tlink; //�ֱ�ָ��ͷ��ͬ�ͻ�β��ͬ����һ����
    InfoType *info;              //�洢�������Ϣ��ָ��(������������)
} ArcBox;

typedef struct VexNode
{
    VertexType data;            //�����������
    ArcBox *firstin, *firstout; //ָ���Ըö���Ϊ��ͷ�ͻ�β�������׸����
} VexNode;

typedef struct
{
    VexNode xlist[MAX_VERTEX_NUM]; //�洢�����һά����
    int vexnum, arcnum;            //��¼ͼ�Ķ������ͻ���
} OLGraph;

int LocateVex(OLGraph *G, VertexType v)
{
    int i = 0;
    //����һά���飬�ҵ�����v
    for (; i < G->vexnum; i++)
    {
        if (G->xlist[i].data == v)
        {
            break;
        }
    }
    //����Ҳ����������ʾ��䣬���� -1
    if (i > G->vexnum)
    {
        printf("no such vertex.\n");
        return -1;
    }
    return i;
}

//����ʮ��������
void CreateDG(OLGraph *G)
{
    //��������ͼ�Ķ������ͻ���
    printf("����������ͼ�Ķ������ͻ���(�ö��Ÿ���):");
    scanf("%d,%d", &(G->vexnum), &(G->arcnum));

    //ʹ��һά����洢�������ݣ���ʼ��ָ����ΪNULL
    for (int i = 0; i < G->vexnum; i++)
    {
        printf("�������%d������ֵ:", i + 1);
        scanf("%d", &(G->xlist[i].data));
        G->xlist[i].firstin = NULL;
        G->xlist[i].firstout = NULL;
    }
    //����ʮ������
    for (int k = 0; k < G->arcnum; k++)
    {
        int v1, v2;

        printf("�����뻡ͷ�ͻ�βֵ(�ö��Ÿ���):");
        scanf("%d,%d", &v1, &v2);

        //ȷ��v1��v2�������е�λ���±�
        int i = LocateVex(G, v1);
        int j = LocateVex(G, v2);

        //�������Ľ��
        ArcBox *p = (ArcBox *)malloc(sizeof(ArcBox));
        p->tailvex = i;
        p->headvex = j;

        //����ͷ�巨�����µ�p���
        p->hlik = G->xlist[j].firstin;
        p->tlink = G->xlist[i].firstout;
        G->xlist[j].firstin = G->xlist[i].firstout = p;
    }
}

//�������
void PrintGrapth(OLGraph *G)
{
    for (int i = 0; i < G->vexnum; i++)
    {
        printf("%d->", i);
        while (1)
        {
            if (G->xlist[i].firstin == NULL)
            {
                printf("^");
                break;
            }
            printf("%d->", G->xlist[i].firstin->headvex);
            G->xlist[i].firstin = G->xlist[i].firstin->tlink; //����
        }
        printf("\n");
    }
}

int main(void)
{
    OLGraph G;    //����һ��ͼ�ı���
    CreateDG(&G); //���ô��������������ַ����

    printf("ʮ������Ϊ:\n");
    PrintGrapth(&G); //���ͼ�Ķ��׾���

    return 0;
}
