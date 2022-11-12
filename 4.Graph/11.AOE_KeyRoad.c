#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20 //��󶥵����
#define VertexType int    //�������ݵ�����

//�߱�ṹ��
typedef struct ArcNode
{
    int weight;              //Ȩ��
    int adjvex;              //�ڽӵ��򣬴洢�õ��Ӧ���±�
    struct ArcNode *nextarc; //ָ����һ���ڽӵ��ָ��
} ArcNode;

//�����ṹ��
typedef struct VNode
{
    VertexType InDegree; //��������ͼÿ�����㻹����Ⱥͳ���
    VertexType OutDegree;
    VertexType data;              //�����������
    ArcNode *firstarc;            //ָ���ڽӵ��ָ��
} VNode, AdjList[MAX_VERTEX_NUM]; //�洢������ͷ��������

//ͼ�ṹ��
typedef struct
{
    AdjList vertices;   //ͼ�ж��������
    int vexnum, arcnum; //��¼ͼ�ж������ͱ߻���
} ALGraph;

//��ʵ��Ҫע�⣬ÿ�����ն˴�ӡ�����Ķ����±�ֵ��������ʾ1�����������±�ֵ���ڲ�������V10��
//Ϊ����ʾ���������ڲ��Դ��������±�ֵ���ڲ�һ��
//���ڽӱ�������ͼ
void CreateDG(ALGraph *G)
{
    //printf("������ڵ���Ŀ�ͱ�(��)����Ŀ(�ö��Ÿ���):");
    scanf("%d, %d", &(G->vexnum), &(G->arcnum)); //���붥��������(��)��

    for (int i = 0; i < G->vexnum; i++)
    {
        //printf("�������%d������ֵ:", i+1);
        scanf("%d", &(G->vertices[i].data)); //����ÿ�����㱾���ֵ
        G->vertices[i].firstarc = NULL;      //���߱���Ϊ�ձ�
        G->vertices[i].InDegree = 0;         //��ʼ��ÿ���������Ϊ0
        G->vertices[i].OutDegree = 0;        //��ʼ��ÿ���������Ϊ0
    }

    //�����߱�(ǰ�巨)
    for (int i = 0; i < G->arcnum; i++)
    {
        int vi, vj, w;
        //printf("�����������໥���ӵĶ����Ȩ��(��ͷ,��β��Ȩ��)ֵ(�ö��Ÿ���):");
        scanf("%d,%d,%d", &vi, &vj, &w);

        ArcNode *e = (ArcNode *)malloc(sizeof(ArcNode)); //���ڴ�����ռ����ɱ߱�ڵ�
        e->weight = w;
        e->adjvex = vj;                        //�ڽӶ������Ϊvj
        e->nextarc = G->vertices[vi].firstarc; //��eָ��ָ��ǰ����ָ��Ľڵ�
        G->vertices[vi].firstarc = e;          //����ǰ�����ָ��ָ��e
        G->vertices[vi].OutDegree++;           //��β���ȼ�һ
        G->vertices[vj].InDegree++;            //��ͷ��ȼ�һ
    }
}

int *etv;    //earliest time of vertex���¼������緢��ʱ�䣨���ޣ�
int *ltv;    //latest time of vertex���¼���������ʱ�䣨���ޣ�
int *stack2; //���ڴ洢���������ջ
int top2;    //����stack2��ָ��

//�����������޻�·��������������򲢷���1�������·����0
int TopologicalSort(ALGraph *G)
{
    int top = 0;                                         //����ջָ���±�
    int count = 0;                                       //����ͳ���������ĸ���
    int *stack = (int *)malloc(G->vexnum * sizeof(int)); //��ջ�洢���Ϊ0�Ķ���

    for (int i = 0; i < G->vexnum; i++)
    {
        if (G->vertices[i].InDegree == 0)
        {
            stack[top++] = i; //�����Ϊ0�Ķ�����ջ
        }
    }

    //�ؼ�·���㷨ר������
    {
        top2 = 0;
        etv = (int *)malloc(G->vexnum * sizeof(int)); //�¼����緢��ʱ��
        for (int i = 0; i < G->vexnum; i++)
        {
            etv[i] = 0;
        }
        stack2 = (int *)malloc(G->vexnum * sizeof(int));
    }

    //��ÿ�����Ϊ0�Ķ��㣬�������ǵ������ӵĶ����ҳ���
    while (top != 0)
    {
        int gettop = stack[--top]; //��ջ
        //printf("%d->", G->vertices[gettop].data);//��ӡ�˶���
        count++; //ͳ�����������

        //�ؼ�·���㷨ר������
        {
            stack2[top2++] = gettop; //�������Ķ������ѹ��洢�������е�ջ
            if (top2 == G->vexnum)   //ΪʲôҪ��ô������Ϊtop2��G->vexnum�Ǿͻᵼ������Խ����
            {
                top2 = G->vexnum - 1;
            }
        }

        //�Դ˶��㻡�����������ɾ����������ͷ����ȼ�һ
        for (ArcNode *e = G->vertices[gettop].firstarc; e != NULL; e = e->nextarc)
        {
            G->vertices[e->adjvex].InDegree--;        //��e->adjvex�Ŷ����ڽӵ����ȼ�һ
            if (G->vertices[e->adjvex].InDegree == 0) //���Լ������ж�����ǲ���0���ж���Ϊ����ջ
            {
                stack[top++] = e->adjvex; //��Ϊ0����ջ���Ա����´�ѭ�����
            }

            //�ؼ�·���㷨ר������
            {
                if ((etv[gettop] + e->weight) > etv[e->adjvex]) //��������¼����緢��ʱ��ֵ
                {
                    etv[e->adjvex] = etv[gettop] + e->weight;
                }
            }
        }
    }

    if (count < G->vexnum) //���countС��count����˵�����ڻ�
    {
        printf("��ͼ�л�·\n");
        return 0;
    }
    else
    {
        printf("\n");
        return 1;
    }
}

//��ؼ�·����GΪ�����������G�ĸ���ؼ��
void CriticalPath(ALGraph *G)
{
    int lte, ete; //��������緢��ʱ�����ٷ���ʱ�����

    TopologicalSort(G);                           //���������У���������etv��stack2��ֵ
    ltv = (int *)malloc(G->vexnum * sizeof(int)); //�¼�������ʱ��
    for (int i = 0; i < G->vexnum; i++)
    {
        ltv[i] = etv[G->vexnum - 1]; //��ʼ��ltv����etv�������һ��ֵȥ��ʼ��ltv���������ȫ��ֵ
    }
    //����ltv(ltv��ֵҪ�ӻ����Դ�㷴��)
    while (top2 >= 0)
    {
        //����ע�⣬��Ϊѭ��������top!=0������stack2[0] == Դ�㣬�༴��ֵ�����ǲ���Ҫ��lte[Դ��] == 0
        //����Ϊ����lte�������������Ը�������
        int gettop = stack2[top2--]; //���������г�ջ���ֽ����

        //��������¼�����ٷ���ʱ��ltvֵ
        for (ArcNode *e = G->vertices[gettop].firstarc; e != NULL; e = e->nextarc)
        {
            if ((ltv[e->adjvex] - e->weight) < ltv[gettop]) //��������¼�����ٷ���ʱ��ltvֵ
            {
                ltv[gettop] = ltv[e->adjvex] - e->weight;
            }
        }
    }
    for (int j = 0; j < G->vexnum; j++) //��ete��lte�͹ؼ��
    {
        for (ArcNode *e = G->vertices[j].firstarc; e != NULL; e = e->nextarc)
        {
            ete = etv[j];                     //����緢��ʱ��
            lte = ltv[e->adjvex] - e->weight; //���ٷ���ʱ��
            if (ete == lte)
            {
                printf("<V%d,V%d>length: %d\n", G->vertices[j].data, G->vertices[e->adjvex].data, e->weight);
            }
        }
    }
}

//���ͼ(��)���ڽӱ�
void PrintGrapth(ALGraph G)
{
    printf("�ڽӱ�Ϊ:\n");
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
            G.vertices[i].firstarc = G.vertices[i].firstarc->nextarc; //����
        }
        printf("\n");
    }
    printf("�����������ȷֱ�Ϊ: ");
    for (int i = 0; i < G.vexnum; i++)
    {
        printf("%d ", G.vertices[i].InDegree);
    }
    printf("\n");
    printf("��������ĳ��ȷֱ�Ϊ: ");
    for (int i = 0; i < G.vexnum; i++)
    {
        printf("%d ", G.vertices[i].OutDegree);
    }
    printf("\n");
}

//�����������������ͼ�������������緢���¼����飬���������������¼�����
void PrintArray(ALGraph G)
{
    printf("\n����������˳��Ϊ:\n");
    for (int i = 0; i < G.vexnum; i++)
        printf("%d ", stack2[i]);

    printf("\n���緢���¼�����(etv)Ϊ:\n");
    for (int i = 0; i < G.vexnum; i++)
        printf("%d ", etv[i]);

    printf("\n�������¼�����(ltv)Ϊ:\n");
    for (int i = 0; i < G.vexnum; i++)
        printf("%d ", ltv[i]);
}

int main()
{
    ALGraph G;      //����һ��ͼ�ı���
    CreateDG(&G);   //���ô��������������ַ����
    PrintGrapth(G); //���ͼ(��)���ڽӱ�
    //TopologicalSort(&G);//��������
    CriticalPath(&G); //��ؼ�·��
    PrintArray(G);    //��ӡ��������������ͼ�����緢���¼����飬�������¼�����

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