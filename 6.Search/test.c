#include <stdio.h>
#include <stdlib.h>

//分别定义平衡因子数
#define LH +1 //左高
#define EH 0  //等高
#define RH -1 //右高

typedef int ElemType;

//定义二叉排序树
struct BSTNode
{
    ElemType data;
    int bf; //balance flag
    struct BSTNode *lchild, *rchild;
};

typedef struct BSTNode *BSTree;

//对以 T 为根结点的二叉树做右旋处理，令 T 指针指向新的树根结点
void R_Rotate(BSTree *T)
{
    BSTree LeftChild = (*T)->lchild;  //LeftChild指向T的左子树根节点
    (*T)->lchild = LeftChild->rchild; //LeftChild的右子树挂接为T的左子树
    LeftChild->rchild = *T;
    *T = LeftChild; //根节点替换为LeftChild
}

//对以 T 为根结点的二叉树做左旋处理，令 T 指针指向新的树根结点
void L_Rotate(BSTree *T)
{
    BSTree RightChild = (*T)->rchild;  //RightChild指向T的右子树根节点
    (*T)->rchild = RightChild->lchild; //RightChild的左子树挂接为T的右子树
    RightChild->lchild = *T;
    *T = RightChild; //根节点替换为RightChild
}

//对以指针 T 所指向结点为根结点的二叉树作左子树的平衡处理，令指针 T 指向新的根结点
void LeftBalance(BSTree *T)
{
    BSTree LeftChild = (*T)->lchild; //LeftChild指向T的左子树根节点
    BSTree RightChild;
    //检查T的左子树的平衡度，并做相应处理
    switch (LeftChild->bf)
    {
    case LH: //新的节点插在T的左孩子的左子树上，直接让左孩子右旋即可
        (*T)->bf = LeftChild->bf = EH;
        R_Rotate(T);
        break;
    case RH:                            //新的节点插在T的左孩子的右子树上，要做两次旋转
        RightChild = LeftChild->rchild; //RightChild指向T的左孩子的右子树根
        switch (RightChild->bf)         //修改T及其左孩子的bf
        {
        case LH:
            (*T)->bf = RH;
            LeftChild->bf = EH;
            break;
        case EH:
            (*T)->bf = LeftChild->bf = EH;
            break;
        case RH:
            (*T)->bf = EH;
            LeftChild->bf = LH;
            break;
        }
        RightChild->bf = EH;
        L_Rotate(&(*T)->lchild); //对T的左子树做左旋处理
        R_Rotate(T);             //对T做右旋处理
        break;
    }
}

//对以指针 T 所指向结点为根结点的二叉树作右子树的平衡处理，令指针 T 指向新的根结点   单位
void RightBalance(BSTree *T)
{
    BSTree RightChild = (*T)->rchild;
    BSTree LeftChild;
    switch (RightChild->bf)
    {
    case RH:
        (*T)->bf = RightChild->bf = EH;
        L_Rotate(T);
        break;
    case LH:
        LeftChild = RightChild->lchild;
        switch (LeftChild->bf)
        {
        case LH:
            (*T)->bf = EH;
            RightChild->bf = RH;
            break;
        case EH:
            (*T)->bf = RightChild->bf = EH;
            break;
        case RH:
            (*T)->bf = EH;
            RightChild->bf = LH;
            break;
        }
        LeftChild->bf = EH;
        R_Rotate(&(*T)->rchild);
        L_Rotate(T);
        break;
    }
}

int InsertAVL(BSTree *T, ElemType e, int *taller)
{
    //如果本身为空树，则直接添加 e 为根结点
    if ((*T) == NULL)
    {
        (*T) = (BSTree)malloc(sizeof(struct BSTNode));
        (*T)->bf = EH;
        (*T)->data = e;
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
        *taller = 1;
    }
    //如果二叉排序树中已经存在 e ，则不做任何处理
    else if (e == (*T)->data)
    {
        *taller = 0;
        return 0;
    }
    //如果 e 小于结点 T 的数据域，则插入到 T 的左子树中
    else if (e < (*T)->data)
    {
        //如果插入过程，不会影响树本身的平衡，则直接结束
        if (!InsertAVL(&(*T)->lchild, e, taller))
            return 0;
        //判断插入过程是否会导致整棵树的深度 +1
        if (*taller)
        {
            //判断根结点 T 的平衡因子是多少，由于是在其左子树添加新结点的过程中导致失去平衡，所以当 T 结点的平衡因子本身为 1 时，
            //需要进行左子树的平衡处理，否则更新树中各结点的平衡因子数
            switch ((*T)->bf)
            {
            case LH:
                LeftBalance(T);
                *taller = 0;
                break;
            case EH:
                (*T)->bf = LH;
                *taller = 1;
                break;
            case RH:
                (*T)->bf = EH;
                *taller = 0;
                break;
            }
        }
    }
    //同样，当 e>T->data 时，需要插入到以 T 为根结点的树的右子树中，同样需要做和以上同样的操作
    else
    {
        if (!InsertAVL(&(*T)->rchild, e, taller))
            return 0;
        if (*taller)
        {
            switch ((*T)->bf)
            {
            case LH:
                (*T)->bf = EH;
                *taller = 0;
                break;
            case EH:
                (*T)->bf = RH;
                *taller = 1;
                break;
            case RH:
                RightBalance(T);
                *taller = 0;
                break;
            }
        }
    }
    return 1;
}

//判断现有平衡二叉树中是否已经具有数据域为 e 的结点
int FindNode(BSTree root, ElemType e, BSTree *pos)
{
    BSTree pt = root;
    (*pos) = NULL;
    while (pt)
    {
        if (pt->data == e)
        {
            //找到节点，pos指向该节点并返回true
            (*pos) = pt;
            return 1;
        }
        else if (pt->data > e)
        {
            pt = pt->lchild;
        }
        else
            pt = pt->rchild;
    }
    return 0;
}

//中序遍历平衡二叉树
void PrintOrder(BSTree T)
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
    int i, nArr[] = {1, 23, 45, 34, 98, 9, 4, 35, 23};

    BSTree root = NULL, pos;
    int taller;
    //用 nArr查找表构建平衡二叉树（不断插入数据的过程）
    for (i = 0; i < 9; i++)
    {
        InsertAVL(&root, nArr[i], &taller);
    }
    //中序遍历输出
    PrintOrder(root);
    //判断平衡二叉树中是否含有数据域为 103 的数据
    if (FindNode(root, 103, &pos))
    {
        printf("\n%d\n", pos->data);
    }
    else
    {
        printf("\nNot find this Node\n");
    }

    return 0;
}
