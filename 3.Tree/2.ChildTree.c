#include <stdio.h>
#include <stdlib.h>

//树的孩子表示法(顺序存储)
#define MAX_SIZE 20
#define TElemType char

/*孩子节点*/
typedef struct CTNode
{
    int child;           //孩子节点在数组中的位置
    struct CTNode *next; //下一个孩子
} ChildPtr;

/*表头结构*/
typedef struct
{
    TElemType data;       //结点的数据类型
    ChildPtr *firstchild; //孩子链表的头指针(第一个孩子)
} CTBox;

/*树结构*/
typedef struct
{
    CTBox nodes[MAX_SIZE]; //存储结点的数组
    int n, r;              //结点数量和树根的位置
} CTree;

//孩子表示法存储普通树
CTree initTree(CTree tree)
{
    printf("输入节点数量：\n");
    scanf("%d", &(tree.n));
    for (int i = 0; i < tree.n; i++)
    {
        printf("输入第 %d 个节点的值：\n", i + 1);
        fflush(stdin);
        scanf("%c", &(tree.nodes[i].data));
        tree.nodes[i].firstchild = (ChildPtr *)malloc(sizeof(ChildPtr));
        tree.nodes[i].firstchild->next = NULL;
        printf("输入节点 %c 的孩子节点数量：\n", tree.nodes[i].data);
        int Num;
        scanf("%d", &Num);
        if (Num != 0)
        {
            ChildPtr *p = tree.nodes[i].firstchild;
            for (int j = 0; j < Num; j++)
            {
                ChildPtr *newEle = (ChildPtr *)malloc(sizeof(ChildPtr));
                newEle->next = NULL;
                printf("输入第 %d 个孩子节点在顺序表中的位置", j + 1);
                scanf("%d", &(newEle->child));
                p->next = newEle;
                p = p->next;
            }
        }
    }
    return tree;
}

void findKids(CTree tree, char a)
{
    int hasKids = 0;
    for (int i = 0; i < tree.n; i++)
    {
        if (tree.nodes[i].data == a)
        {
            ChildPtr *p = tree.nodes[i].firstchild->next;
            while (p)
            {
                hasKids = 1;
                printf("%c ", tree.nodes[p->child].data);
                p = p->next;
            }
            break;
        }
    }
    if (hasKids == 0)
    {
        printf("此节点为叶子节点");
    }
}

int main()
{
    CTree tree;
    tree = initTree(tree);
    //默认数根节点位于数组notes[0]处
    tree.r = 0;
    printf("找出节点 F 的所有孩子节点：");
    findKids(tree, 'F');

    return 0;
}
