#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

//ltag == 0时指向该节点的左孩子， == 1时指向该节点的前驱
//rtag == 0时指向该节点的右孩子， == 1时指向该节点的后继
struct ThreadNode
{
    ElemType data;
    struct ThreadNode *lChild, *rChild;
    int ltag, rtag;
};
typedef struct ThreadNode ThreadNode;
typedef struct ThreadNode *ThreadTree;

ThreadTree pre = NULL; //全局变量,指向当前访问节点的前驱

//先序创建二叉树
int CreateBiTree(ThreadTree *T)
{
    ElemType ch;
    scanf("%d", &ch);

    if (ch == -1)
    {
        *T = NULL;
    }
    else
    {
        *T = (ThreadTree)malloc(sizeof(ThreadNode));
        if (!(*T))
        {
            exit(-1);
        }
        (*T)->data = ch;
        (*T)->ltag = 0; //初始化左指针域指向左孩子(非前驱)
        (*T)->rtag = 0; //初始化右指针域指向右孩子(非后继)

        printf("输入%d的左子结点：", ch);
        CreateBiTree(&(*T)->lChild);
        printf("输入%d的右子结点：", ch);
        CreateBiTree(&(*T)->rChild);
    }
    return 1;
}

//层序遍历
void LevelOrder(ThreadNode *root)
{
    ThreadNode *q = NULL;
    ThreadNode *Q[100];

    int front = -1;
    int rear = -1;

    if (root == NULL)
    {
        return;
    }
    Q[++rear] = root;
    while (front != rear)
    {
        q = Q[++front];
        printf("%d", q->data);

        if (q->lChild != NULL)
        {
            Q[++rear] = q->lChild;
        }
        if (q->rChild != NULL)
        {
            Q[++rear] = q->rChild;
        }
    }
}

//二叉树的深度
int TreeDeep(ThreadTree T)
{
    int deep = 0;
    if (T)
    {
        int leftdeep = TreeDeep(T->lChild);
        int rightdeep = TreeDeep(T->rChild);
        deep = (leftdeep >= rightdeep) ? (leftdeep + 1) : (rightdeep + 1);
    }
    return deep;
}

//求二叉树叶子结点个数
void Leafcount(ThreadTree T, int *num)
{
    if (T == NULL)
    {
        return;
    }
    else
    {
        if ((T->lChild == NULL) && (T->rChild == NULL))
        {
            *num += 1;
        }
        Leafcount(T->lChild, num);
        Leafcount(T->rChild, num);
    }
}

//中序遍历进行中序线索化
void InThreading(ThreadTree T)
{
    if (T == NULL)
    {
        return;
    }
    InThreading(T->lChild); //递归左孩子线索化
    //线索化代码块
    {
        if (T->lChild == NULL) //没有左孩子，建立前驱
        {
            T->ltag = 1;
            T->lChild = pre;
        }

        //if((pre->rChild == NULL) && (pre != NULL))//前驱没有右孩子，建立前驱节点的后继线索
        if (pre && !pre->rChild)
        {
            pre->rtag = 1;
            pre->rChild = T;
        }
        pre = T; //将pre指针指向当前节点
    }
    InThreading(T->rChild); //递归右孩子线索化
}

//中序遍历
void InOrderTraverse(ThreadTree T)
{
    ThreadTree p;
    p = T->lChild;

    while (p != NULL) //空树或者遍历结束时，p==T
    {
        //一直找左孩子，当ltag == 0时，循环到中序序列第一个节点
        while (p->ltag == 0)
        {
            p = p->lChild;
        }
        //此时p指向中序遍历序列的第一个结点（最左下的结点）
        printf("%d", p->data); //打印其左子树为空的结点

        //当结点右标志位为1时，直接找到其后继结点
        while ((p->rtag == 1) && (p->rChild != NULL))
        {
            p = p->rChild;
            printf("%d", p->data); //访问后继节点
        }
        //当p所指结点的rchild指向的是孩子结点为不是线索时，p的后继应该是其右子树的最左下的结点，即遍历其右子树时访问的第一个节点
        p = p->rChild;
    }
    printf("\n");
}

//主函数
int main(void)
{
    ThreadTree T;
    int deepth, num = 0;

    printf("请输入前序二叉树，-1表示没有叶结点：\n");
    CreateBiTree(&T);

    deepth = TreeDeep(T);
    printf("数的深度为：%d", deepth);
    printf("\n");

    Leafcount(T, &num);
    printf("数的叶子结点个数为：%d", num);
    printf("\n");

    printf("层序遍历二叉树：");
    LevelOrder(T);
    printf("\n");

    InThreading(T);
    printf("中序遍历二叉树：");
    InOrderTraverse(T);
    printf("\n");

    return 0;
}
