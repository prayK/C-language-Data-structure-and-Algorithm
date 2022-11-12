#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;//数据类型
//定义二叉树结构，与单链表相似，多了一个右孩子结点
struct BiTNode
{
	ElemType data;
	struct BiTNode *lChild,*rChild;
};
typedef struct BiTNode BiTNode;
typedef struct BiTNode* BiTree;

//先序创建二叉树
int CreateBiTree(BiTree *T)
{
	ElemType ch;
	scanf("%d",&ch);

	if(ch == -1)
	{
		*T = NULL;
	}
	else
	{
		*T = (BiTree)malloc(sizeof(BiTNode));
		if(!(*T))
		{
			exit(-1);
		}
		(*T)->data = ch;
		printf("输入%d的左子结点：",ch);
		CreateBiTree(&(*T)->lChild);
		printf("输入%d的右子结点：",ch);
		CreateBiTree(&(*T)->rChild);
	}
	return 1;
}

//先序遍历二叉树
void TraverseBiTree(BiTree T)
{
	if(T==NULL)
	{
		return;
	}
	printf("%d",T->data);
	TraverseBiTree(T->lChild);
	TraverseBiTree(T->rChild);
}

//中序遍历二叉树
void InOrderBiTree(BiTree T)
{
	if(T==NULL)
	{
		return;
	}
	InOrderBiTree(T->lChild);
	printf("%d",T->data);
	InOrderBiTree(T->rChild);
}

//后序遍历二叉树
void PostOrderBiTree(BiTree T)
{
	if(T==NULL)
	{
		return;
	}
	PostOrderBiTree(T->lChild);
	PostOrderBiTree(T->rChild);
	printf("%d",T->data);
}

//层序遍历
void LevelOrder(BiTNode* root)
{
    BiTNode* q = NULL;
    BiTNode* Q[100];

    int front = -1;
    int rear = -1;

    if(root == NULL)
    {
        return;
    }
    Q[++rear] = root;
    while(front != rear)
    {
        q = Q[++front];
        printf("%d", q->data);

        if(q->lChild != NULL)
        {
            Q[++rear] = q->lChild;
        }
        if(q->rChild != NULL)
        {
            Q[++rear] = q->rChild;
        }
    }
}

//二叉树的深度
int TreeDeep(BiTree T)
{
	int deep=0;
	if(T)
	{
		int leftdeep=TreeDeep(T->lChild);
		int rightdeep=TreeDeep(T->rChild);
		deep=leftdeep>=rightdeep?leftdeep+1:rightdeep+1;
	}
	return deep;
}

//求二叉树叶子结点个数
void Leafcount(BiTree T, int* num)
{
    if(T == NULL)
    {
        return;
    }
	else
	{
		if((T->lChild == NULL) && (T->rChild==NULL))
		{
			*num += 1;
		}
		Leafcount(T->lChild, num);
		Leafcount(T->rChild, num);
	}

}

//主函数
int main(void)
{
	BiTree T;
	int deepth = 0, num = 0;

	printf("请输入第一个结点的值，-1表示没有叶结点：\n");
	CreateBiTree(&T);

	printf("先序遍历二叉树：\n");
	TraverseBiTree(T);
	printf("\n");

	printf("中序遍历二叉树：\n");
	InOrderBiTree(T);
	printf("\n");

	printf("后序遍历二叉树：\n");
	PostOrderBiTree(T);
	printf("\n");

	printf("层序遍历二叉树：\n");
	LevelOrder(T);
	printf("\n");

	deepth=TreeDeep(T);
	printf("数的深度为：%d",deepth);
	printf("\n");

	Leafcount(T, &num);
	printf("数的叶子结点个数为：%d",num);
	printf("\n");

	return 0;
}
