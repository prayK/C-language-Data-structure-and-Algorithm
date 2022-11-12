#include <stdio.h>
#include <stdlib.h>

#define keyType int

typedef struct
{
    keyType key;//���ұ���ÿ������Ԫ�ص�ֵ
    //�����Ҫ�������������������
}ElemType;

typedef struct
{
    ElemType *elem;//��Ų��ұ�������Ԫ�ص�����
    int length;//��¼���ұ������ݵ�������
}SSTable;

//�������ұ�
void Create(SSTable **st, int length)
{
    (*st) = (SSTable*)malloc(sizeof(SSTable));
    (*st)->length = length;
    (*st)->elem = (ElemType*)malloc((length+1)*sizeof(ElemType));
    printf("������е�%d������Ԫ�أ�\n", length);

    //���ݲ��ұ�������Ԫ�ص��ܳ��ȣ��ڴ洢ʱ���������±�Ϊ 1 �Ŀռ俪ʼ�洢����
    for(int i=1; i<=length; i++)
    {
        printf("�������%d������: ", i);
        scanf("%d", &((*st)->elem[i].key));
    }
}

//쳲����������㷨
//����쳲������������ƽ�ָ�
int FibonacciSearch(SSTable *ST,keyType key)
{
    int low = 1;//��ʼ״̬ low ָ��ָ���һ���ؼ���
    int high = ST->length;//high ָ�����һ���ؼ���
    int mid;
    while(low <= high)
    {
        mid = (low + high) / 2;//int ����Ϊ���Σ����ԣ�mid ÿ��Ϊȡ��������
        if (ST->elem[mid].key == key)//��� mid ָ���ͬҪ���ҵ���ȣ����� mid ��ָ���λ��
        {
            return mid;
        }
        else if(ST->elem[mid].key > key)//���midָ��Ĺؼ��ֽϴ������ high ָ���λ��
        {
            high = mid - 1;
        }
        //��֮������� low ָ���λ��
        else
        {
            low = mid + 1;
        }
    }
    return 0;
}

int main(int argc, const char * argv[])
{
    SSTable *st;
    Create(&st, 11);
    getchar();
    printf("������������ݵĹؼ��֣�\n");
    int key;
    scanf("%d", &key);
    int location = FibonacciSearch(st, key);

    //�������ֵΪ 0����֤�����ұ���δ�鵽 key ֵ��
    if(location == 0)
    {
        printf("���ұ����޸�Ԫ��");
    }
    else
    {
        printf("�����ڲ��ұ��е�λ��Ϊ��%d", location);
    }
    return 0;
}
