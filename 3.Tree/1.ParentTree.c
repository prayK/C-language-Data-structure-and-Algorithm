#include <stdio.h>
#include <stdlib.h>

//树的双亲表示法(顺序存储)
#define MAX_SIZE 20
typedef char ElemType;

typedef struct Snode //结点结构
{
    ElemType data;
    int parent;
} PNode;

typedef struct //树结构
{
    PNode tnode[MAX_SIZE];
    int n;
} PTree;

//初始化各个节点的值以及他们父母的位置
PTree InitPNode(PTree tree)
{
    printf("请输入节点个数: ");
    scanf("%d", &(tree.n));

    //初始化时将每个结点值赋值为'#',且每个结点的父母位置在-2处
    for (int i = 0; i < MAX_SIZE; i++)
    {
        tree.tnode[i].data = '#';
        tree.tnode[i].parent = -2;
    }

    printf("请输入结点的值及其双亲位于数组中的位置下标:\n");
    for (int i = 0; i < tree.n; i++)
    {
        int j = 0;
        char ch = 0;
        fflush(stdin);
        scanf("%c %d", &ch, &j);
        tree.tnode[i].data = ch;
        tree.tnode[i].parent = j;
    }
    return tree;
}

//插入一个节点
//还可以优化，比如在创建时就计算出有多少个节点，然后插入式就不需要遍历
void InsertPNode(PTree *tree)
{
    char ch = 0;
    int pos = -2;
    printf("请输入插入的结点值及其双亲位置：");
    fflush(stdin);
    scanf("%c %d", &ch, &pos);

    for (int i = 0; i < MAX_SIZE; i++)
    {
        //找到空闲位置了，把新的节点插进去
        if ((tree->tnode[i].data == '#') && (tree->tnode[i].parent == -2))
        {
            tree->tnode[i].data = ch;
            tree->tnode[i].parent = pos;
            break;
        }
    }
}

//删除一个节点，方案：将最后一个节点的放到已经删除的节点的位置上
void DeletePNode(PTree *tree)
{
}

//找到父母位置
void FindParent(PTree tree)
{
    char a;
    int isfind = 0;
    printf("请输入要查询的结点值: ");
    fflush(stdin);
    scanf("%c", &a);
    for (int i = 0; i < tree.n; i++)
    {
        if (tree.tnode[i].data == a)
        {
            isfind = 1;
            int ad = tree.tnode[i].parent;
            printf("%c 的父节点为：%c,存储位置下标为：%d", a, tree.tnode[ad].data, ad);
            printf("\n");
            break;
        }
    }
    if (isfind == 0)
    {
        printf("树中无此节点");
    }
}

int main()
{
    PTree tree;

    tree = InitPNode(tree);
    FindParent(tree);

    InsertPNode(&tree);
    for (int i = 0; i < MAX_SIZE; i++)
    {
        printf("%c ", tree.tnode[i].data);
        //printf("%d ", tree.tnode[i].parent);
    }

    return 0;
}