#include <stdio.h>
#include <stdlib.h>

#define MAX_VERtEX_NUM 20 //�����������
#define VRType int        //��ʾ����֮��Ĺ�ϵ�ı�������
#define InfoType char     //�洢�����߱߶�����Ϣ��ָ���������
#define VertexType int    //ͼ�ж������������
#define INFINITY 65535

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
    Function: �Ͻ�˹�����㷨�����·��
    brief: Path[v]��ֵΪǰ������
    brief: Distance[v]��ʾV0��V�����·�����Ⱥ�
    brief: Final[]��Ǹ������Ƿ��Ѿ��ҵ����·��(Final[w]==1��ʾ���V0��Vw�����·��)

    brief: ����㷨�������⣬��ǰֻ�ܴ�V0��ʼ���д����
*/
void Dijkstra(MGraph G, int v0, int Final[], int Path[], int Distance[])
{
  int k = 0;

  //��ʼ������
  for (int i = 0; i < G.vexnum; i++)
  {
    Final[i] = 0;                                       //��ʼ��ÿ������֮�仹û���ҵ����·��
    Distance[i] = G.arcs[v0][i].adj;                    //����V0�������ߵĶ������Ȩֵ
    Path[i] = (G.arcs[v0][i].adj == INFINITY) ? -1 : 0; //��ʼ��·��ǰ������V0֮��û�б߾���-1���б���ôǰ������V0��0
  }
  Path[0] = -1; // V0û��ǰ��
  Final[0] = 1; // V0��V0����Ҫ·��

  //��ʼ��ѭ����ÿ�����V0��ĳ��V��������·��
  for (int i = 0; i < G.vexnum; i++)
  {
    /*
    {
        printf("V%d->", v0);//��ӡ��ʼ��
        if(i<(G.vexnum-1) && (i>v0))
            printf("V%d->", k);
        if(i==(G.vexnum-1))
            printf("V%d", k);//��ӡ·���Ĵ��룬Ϊʲô��������Ϊ�˽�k==0ʱ��ӡ��ȥ
    }
    */
    (i < (G.vexnum - 1)) ? printf("V%d->", k) : printf("V%d", k); //��ӡ·���Ĵ��룬Ϊʲô��������Ϊ�˽�k==0ʱ��ӡ��ȥ

    int Min = INFINITY;                //��ǰ��֪��V0������������
    for (int j = 0; j < G.vexnum; j++) //Ѱ����V0����Ķ���
    {
      //���V0��Vj֮�仹û���ҵ���̾��룬����V0��Vj֮��ľ���С��֮ǰ����Сֵ
      if ((Final[j] == 0) && (Distance[j] < Min))
      {
        Min = Distance[j]; // Vj������V0����
        k = j;
      }
    }
    Final[k] = 1; //��Ŀǰ�ҵ�������Ķ�����һ

    //��δ����Ŀ�����ڸղ��Ѿ��ҵ�V0��V1�����·�������ϣ���V1����������ı߽��м���,�õ�V0�����ǵĵ�ǰ��̾���
    for (int j = 0; j < G.vexnum; j++) //������ǰ���·��������
    {
      //�������v�����·����������������·���ĳ��ȸ��̵Ļ�
      //Ҫ֪��Distance[v]��ʾV0��V�����·�����Ⱥͣ������ǵ����ģ���ǰdistance��֮ǰ��distance���ϵ�ǰֵ
      if ((Final[j] == 0) && (Min + G.arcs[k][j].adj < Distance[j]))
      {                                       //˵���ҵ��˸��̵�·�����޸�D[j]��P[j]
        Distance[j] = Min + G.arcs[k][j].adj; //�޸ĵ�ǰ·������
        Path[j] = k;
      }
    }
  }
}

//��ӡ·��(��������ȱ��Ҳ����Ҫ���������ӡ·����)
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
  CreateUDN(&G);  //����������
  PrintGrapth(G); //��ӡ�ڽ�����

  int Final[G.vexnum];
  int Path[G.vexnum];     // P[]���������洢���·���±������
  int Distance[G.vexnum]; // D[]���������洢���·����Ȩֵ��

  Dijkstra(G, 1, Final, Path, Distance); //�Ͻ�˹�����㷨�����·��
  // PrintRoad(Path, G.vexnum);//��·����ӡ����

  return 0;
}

/*

#include <stdio.h>

#define V 20 //�����������
#define INFINITY 65535

typedef struct
{
    int vexs[V];        //�洢ͼ�ж�������
    int arcs[V][V];     //��ά���飬��¼����֮��Ĺ�ϵ
    int vexnum, arcnum; //��¼ͼ�Ķ������ͻ����ߣ���
} MGraph;

//���ݶ��㱾�����ݣ��жϳ������ڶ�ά�����е�λ��
int LocateVex(MGraph *G, int v)
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

//����������Ȩͼ
void CreateDG(MGraph *G)
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
            G->arcs[i][j] = INFINITY;
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

        if (m == -1 || n == -1)
        {
            return;
        }
        G->arcs[n][m] = w;
        G->arcs[m][n] = w;
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

//�Ͻ�˹�����㷨��v0��ʾ����������ʼ�����������е��±�
void Dijkstra_minTree(MGraph G, int v0, int p[V], int D[V])
{
    int final[V]; //Ϊ������������һ�����ֵ������ȷ�ϸö����Ƿ��Ѿ��ҵ����·��  final[x] = 1��ʾ v0 �� vx �����·���Ѿ����
    //�Ը�������г�ʼ��
    for (int v = 0; v < G.vexnum; v++)
    {
        final[v] = 0;
        D[v] = G.arcs[v0][v];
        p[v] = 0;
    }
    //������v0λ�±�Ķ���Ϊ��ʼ�㣬���Բ������ж�
    D[v0] = 0;
    final[v0] = 1;
    int k = 0;
    for (int i = 0; i < G.vexnum; i++)
    {
        int min = INFINITY;
        //ѡ�񵽸�����Ȩֵ��С�Ķ��㣬��Ϊ������ȷ�����·���Ķ���
        for (int w = 0; w < G.vexnum; w++)
        {
            if ((final[w] == 0) && (D[w] < min))
            {
                k = w;
                min = D[w];
            }
        }
        //���øö���ı�־λΪ1�������´��ظ��ж�
        final[k] = 1;

        //��v0���������Ȩֵ���и���
        for (int w = 0; w < G.vexnum; w++)
        {
            if ((final[w] == 0) && (min + G.arcs[k][w] < D[w]))
            {
                D[w] = min + G.arcs[k][w];
                p[w] = k; //��¼�������·���ϴ��ڵĶ���
            }
        }
    }
}

//��ӡ·��(��������ȱ��Ҳ����Ҫ���������ӡ·����)
void PrintRoad(int path[], int Len)
{
    printf("���·��Ϊ��\n");
    for (int i = 1; i < G.vexnum; i++)
    {
        printf("%d - %d�����·���еĶ����У�", i, 0);
        printf(" %d-", i);
        int j = i;
        //����ÿһ�����·���϶���¼�ž����Ķ��㣬���Բ���Ƕ�׵ķ�ʽ������ɵõ��������·���ϵ����ж���
        while (P[j] != 0)
        {
            printf("%d-", P[j]);
            j = P[j];
        }
        printf("0\n");
    }
    printf("Դ�㵽����������·������Ϊ:\n");
    for (int i = 1; i < G.vexnum; i++)
    {
        printf("%d - %d : %d \n", G.vexs[0], G.vexs[i], D[i]);
    }
}

int main()
{
    MGraph G;
    CreateDG(&G);
    PrintGrapth(G); //��ӡ�ڽ�����

    int Path[V] = {0};     // ��¼���� 0 �������������̵�·��
    int Distance[V] = {0}; // ��¼���� 0 �������������Ȩֵ
    Dijkstra_minTree(G, 0, Path, Distance);

    return 0;
}

*/