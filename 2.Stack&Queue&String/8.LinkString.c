#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 3 //全局设置链表中节点存储数据的个数

struct L_LinkNode
{
    char a[MAXSIZE];         //数据域可存放 linkNum 个数据
    struct L_LinkNode *next; //代表指针域，指向直接后继元素
};                           // nk为节点名，每个节点都是一个 link 结构体

typedef struct L_LinkNode *Link;

//初始化链表，其中head为头指针，str为存储的字符串
Link initLink(Link head, char *str)
{
    int length = strlen(str);

    //根据字符串的长度，计算出链表中使用节点的个数
    int num = length / MAXSIZE;
    if (length % MAXSIZE)
    {
        num++;
    }
    //创建并初始化首元节点
    head = (Link)malloc(sizeof(struct L_LinkNode));
    head->next = NULL;
    Link temp = head;
    //初始化链表
    for (int i = 0; i < num; i++)
    {
        int j = 0;
        for (; j < MAXSIZE; j++)
        {
            if (i * MAXSIZE + j < length)
            {
                temp->a[j] = str[i * MAXSIZE + j];
            }
            else
                temp->a[j] = '#';
        }
        if (i * MAXSIZE + j < length)
        {
            Link newlink = (Link)malloc(sizeof(struct L_LinkNode));
            newlink->next = NULL;
            temp->next = newlink;
            temp = newlink;
        }
    }
    return head;
}

//输出链表
void displayLink(Link head)
{
    Link temp = head;
    while (temp)
    {
        for (int i = 0; i < MAXSIZE; i++)
        {
            printf("%c", temp->a[i]);
        }
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    Link head = NULL;

    head = initLink(head, "data.biancheng.net");
    displayLink(head);

    return 0;
}
