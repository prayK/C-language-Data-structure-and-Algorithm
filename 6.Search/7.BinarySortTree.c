#include <stdio.h>
#include <stdlib.h>

//二叉排序树本身是动态查找表，所以有插入和删除操作。插入元素之前要先查找这个排序树中有没有这个数，没有就插入
#define ElemType int

//二叉排序树的节点结构定义
struct BiTNode
{
    ElemType data;
    struct BiTNode *lchild, *rchild;
};

typedef struct BiTNode *BiTree;

int SearchBiTree(BiTree T, ElemType e, BiTree *p, BiTree f)
{
    if (T == NULL) //传进来的树为空，就用指针p返回查找路径上访问的最后一个节点并返回0
    {
        *p = f;
        return 0;
    }
    else if (e == T->data) //查找成功,就用指针p返回该节点
    {
        *p = T;
        return 1;
    }
    else if (e < T->data) //向左子树递归查找
    {
        return SearchBiTree(T->lchild, e, p, T);
    }
    else //向右子树递归查找
    {
        return SearchBiTree(T->rchild, e, p, T);
    }
}

//当二叉树中不存在关键字e时就插入并且返回1，否则返回0
int InsertBiTree(BiTree *T, ElemType e)
{
    BiTree p;

    if (SearchBiTree(*T, e, &p, NULL) == 0) //查找不成功
    {
        BiTree s = (BiTree)malloc(sizeof(struct BiTNode));
        s->data = e;
        s->lchild = s->rchild = NULL;

        if (p == NULL)
        {
            *T = s; //插入s为新的根节点
        }
        else if (e < p->data)
        {
            p->lchild = s; //插入s为左孩子
        }
        else
        {
            p->rchild = s; //插入s为右孩子
        }
        return 1;
    }
    else
    {
        return 0; //树中已经有相同的关键字，不再插入
    }
}

int Delete(BiTree *T)
{
    if (((*T)->lchild == NULL) && ((*T)->rchild == NULL)) //左右子树都为空，直接删除该叶子节点即可
    {
        *T = NULL;
    }
    else if ((*T)->lchild == NULL) //左子树为空，用该节点的右子树代替即可
    {
        BiTree q = *T;
        *T = (*T)->rchild;
        free(q);
    }
    else if ((*T)->rchild == NULL) //右子树为空，用该节点的左子树代替即可
    {
        BiTree q = *T;
        *T = (*T)->lchild;
        free(q);
    }
    else //左右子树皆不为空(用直接前驱或者后继的方式来代替待删除节点)
    {
        BiTree q = *T;
        BiTree s = (*T)->lchild; //利用s去找前驱(前驱在左子树中)

        while (s->rchild != NULL) //遍历，找到节点T的直接前驱，向右到尽头
        {
            q = s;
            s = s->rchild;
        }
        (*T)->data = s->data; //直接利用待删除节点的直接前驱s的值去改变待删除节点T的值
        if (q != *T)          //判断节点T的左子树是否有右子树(如果有，就会在前面的while循环中迭代使得q!=(*T))，分为两种情况讨论
        {
            q->rchild = s->lchild; //若有，则在删除直接前驱结点的同时，令前驱的左孩子节点改为q 指向结点的孩子结点
        }
        else
        {
            q->lchild = s->lchild; //否则，直接将左子树上移即可
        }

        free(s);
    }
    return 1;
}

//若二叉排序树T中存在记录e就删除该元素并返回1，否则返回0
int DeleteBiTree(BiTree *T, ElemType e)
{
    if (*T == NULL) //不存在记录等于e的节点
    {
        return 0;
    }
    else
    {
        if (e == (*T)->data)
        {
            return Delete(T); //找到记录等于e的节点
        }
        else if (e < (*T)->data)
        {
            return DeleteBiTree(&(*T)->lchild, e);
        }
        else
        {
            return DeleteBiTree(&(*T)->rchild, e);
        }
    }
}

void PrintOrder(BiTree T)
{
    if (T != NULL)
    {
        PrintOrder(T->lchild);
        printf("%d ", T->data);
        PrintOrder(T->rchild);
    }
}

int main()
{
    int a[6] = {3, 4, 2, 5, 9, 11};
    BiTree T = NULL;

    for (int i = 0; i < 6; i++)
    {
        InsertBiTree(&T, a[i]);
    }
    printf("中序遍历二叉排序树：\n");
    PrintOrder(T);
    printf("\n删除3后，中序遍历二叉排序树：\n");
    DeleteBiTree(&T, 3);
    PrintOrder(T);

    return 0;
}