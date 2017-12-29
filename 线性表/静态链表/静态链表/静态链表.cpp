// ��̬����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "ctype.h"

#include "stdio.h"
#include "io.h"
#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 1000

typedef int Status;   //StatusΪ�����������ͣ���ֵʱ�������״̬�룬��OK��
typedef char ElemType; //ElemType����ʵ�����ݵ��������

Status visit(ElemType c)
{
	printf("%c", c);
	return OK;
}

//���徲̬����Ĵ洢�ṹ
typedef struct {
	ElemType data;
	int cur;  //��Ϊ�α�ʹ��
} Component,StaticLinkList[MAXSIZE];   

Status InitList(StaticLinkList space) {
	int i;
	for (i = 0; i < MAXSIZE-1; i++)
		space[i].cur = i + 1;
	space[MAXSIZE - 1].cur= 0;   //��ʼ���ľ�̬����Ϊ�գ����һ��Ԫ�ص��α�ָ��0
	return OK;
}

//���侲̬����ռ�
int Malloc_SSL(StaticLinkList space) {
	int i = space[0].cur;
	if (space[0].cur) {
		space[0].cur = space[i].cur;    //���ص�ǰ���������ͷ���������������������һ��Ԫ��С���space[0].cur
	}
	return i;
}

//�ͷŻ��վ�̬����Ŀ��нڵ�
void Free_SSL(StaticLinkList space, int i) {
	space[i].cur = space[0].cur;
	space[0].cur = i;
	//iλ�ÿճ�����Ϊ���µĿ��нڵ㣬��space[0].curʼ��ָ�����µĿ��нڵ㣬�����Ƚ�ԭ�е�space[0].cur����space[i].cur������space[0].curָ��space[i];
}

//ȡ������������Ԫ�س���
int ListLength(StaticLinkList space) {
	int j = 0;
	int i = space[MAXSIZE - 1].cur;  //��̬���������һ��Ԫ�ص�curʼ��ָ���һ����Ԫ�����ݵĵ�Ԫ
	while (i) {
		j++;
		i = space[i].cur;
	}
	return j;
}

//�������в���������Ԫ��
Status ListInsert(StaticLinkList space, int i, ElemType e) {
	int j, k, l;
	j = MAXSIZE - 1;
	if (i<1 || i>ListLength(space) + 1)
		return ERROR;
	k = Malloc_SSL(space);
	if (k) {
		space[k].data = e;
		for (l = 1; l <= i - 1; l++)
			j = space[j].cur;
		space[k].cur = space[j].cur;
		space[j].cur = k;
		return OK;
	}
	return ERROR;
}

//ɾ����̬�����е�����Ԫ��
	Status ListDelete(StaticLinkList space, int i) {
		int j, k;
		if (i<1 || i>ListLength(space) - 1)
			return ERROR;
		j = MAXSIZE - 1;
		for (k = 1; k <= i - 1; k++) 
			j = space[j].cur;
		k = space[j].cur;
		space[j].cur = space[k].cur;
		Free_SSL(space, k);
		return OK;
	}

//�����ʽ������
	Status ListTraverse(StaticLinkList space) {
		int j = 0;
		int i = space[MAXSIZE - 1].cur;
		while (i) {
			visit(space[i].data);
			i = space[i].cur;
			j++;
		}
		return j;
		printf("\n");
		return OK;
	}
int main()
{
	StaticLinkList L;
	Status i;
	i = InitList(L);
	printf("��ʼ����L.length=%d\n",ListLength(L));

	i = ListInsert(L, 1, 'H');
	i = ListInsert(L, 2, 'E');
	i = ListInsert(L, 3, 'L');
	i = ListInsert(L, 4, 'L');
	i = ListInsert(L, 5, 'O');

	printf("\n��L�ı�ͷ���β���OLLEH��\nL.data=");
	ListTraverse(L);

	i = ListInsert(L, 3, 'W');
	printf("\n��E��L֮�����W��\n L.data=");
	ListTraverse(L);

	i = ListDelete(L, 1);
	printf("\n��ɾ��H��\nL.data=");
	ListTraverse(L);

	printf("\n");
	printf("���������������");
	getchar();
    return 0;
}

