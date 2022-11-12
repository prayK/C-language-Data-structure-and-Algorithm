#include <stdio.h>
#include <stdlib.h>

//�����������ṹ
typedef struct
{
    int weight;              //���Ȩ��
    int parent, left, right; //����㡢���ӡ��Һ����������е�λ���±�
} HTNode, *HuffmanTree;

//HT�����д�ŵĹ���������end��ʾHT�����д�Ž�������λ�ã�
//s1��s2���ݵ���HT������Ȩ��ֵ��С����������������е�λ��
void Select(HuffmanTree HT, int end, int *s1, int *s2)
{
    int min1, min2; //���������ʼ�±�Ϊ 1
    int i = 1;      //�ҵ���û�������Ľ��

    while (HT[i].parent != 0 && i <= end)
    {
        i++;
    }
    min1 = HT[i].weight;
    *s1 = i;

    i++;
    while (HT[i].parent != 0 && i <= end)
    {
        i++;
    }
    //���ҵ����������Ƚϴ�С��min2Ϊ��ģ�min1ΪС��
    if (HT[i].weight < min1)
    {
        min2 = min1;
        *s2 = *s1;
        min1 = HT[i].weight;
        *s1 = i;
    }
    else
    {
        min2 = HT[i].weight;
        *s2 = i;
    }
    //�������ͺ���������δ���������Ľ�����Ƚ�
    for (int j = i + 1; j <= end; j++)
    {
        //����и���㣬ֱ��������������һ��
        if (HT[j].parent != 0)
        {
            continue;
        }
        //�������С�Ļ�С����min2=min1��min1��ֵ�µĽ����±�
        if (HT[j].weight < min1)
        {
            min2 = min1;
            min1 = HT[j].weight;
            *s2 = *s1;
            *s1 = j;
        }
        //�����������֮�䣬min2��ֵΪ�µĽ���λ���±�
        else if (HT[j].weight >= min1 && HT[j].weight < min2)
        {
            min2 = HT[j].weight;
            *s2 = j;
        }
    }
}

//HTΪ��ַ���ݵĴ洢�������������飬wΪ�洢���Ȩ��ֵ�����飬nΪ������
void CreateHuffmanTree(HuffmanTree *HT, int *w, int n)
{
    if (n <= 1)
    {
        return; // ���ֻ��һ��������൱��0
    }

    int m = 2 * n - 1;                                   // ���������ܽڵ�����n����Ҷ�ӽ��
    *HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode)); // 0��λ�ò���
    HuffmanTree p = *HT;

    // ��ʼ�����������е����н��
    for (int i = 1; i <= n; i++)
    {
        (p + i)->weight = *(w + i - 1);
        (p + i)->parent = 0;
        (p + i)->left = 0;
        (p + i)->right = 0;
    }
    //��������±� n+1 ��ʼ��ʼ�����������г�Ҷ�ӽ����Ľ��
    for (int i = n + 1; i <= m; i++)
    {
        (p + i)->weight = 0;
        (p + i)->parent = 0;
        (p + i)->left = 0;
        (p + i)->right = 0;
    }
    //������������
    for (int i = n + 1; i <= m; i++)
    {
        int s1, s2;
        Select(*HT, i - 1, &s1, &s2);
        (*HT)[s1].parent = (*HT)[s2].parent = i;
        (*HT)[i].left = s1;
        (*HT)[i].right = s2;
        (*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;

        //printf("%d ", (*HT)[i].weight);
    }
}

int main(void)
{
    HuffmanTree array1[5];
    int array2[5] = {2, 8, 7, 6, 5};

    CreateHuffmanTree(array1, array2, 5);

    return 0;
}
