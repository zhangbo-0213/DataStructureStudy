// B��_BTree.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdlib.h"
#include "io.h"

#define OK 1
#define ERROR -1
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100

#define m  3    //B���Ľ�
#define N  17  //Ԫ�����ݸ���
#define MAX 5 //�ַ�����󳤶�

typedef int Status;

typedef struct BTNode {
	int keynum; //�ڵ��йؼ��ָ���
	struct BTNode *parent; //ָ��˫�׵�ָ��
	struct Node {
		int key; //��¼�ؼ���
		int recptr; //
		BTNode *ptr;//ָ��������ָ��
	}node[m+1]; //��һ���ڵ㲻��¼�ؼ��ֺ�recptr����¼ָ��������ָ��
}BTNode,*BTree;

//�����ѯ����ṹ��
typedef struct Result {
	int tag;  //��¼��ѯ������ɹ�Ϊ1��ʧ��Ϊ0
	int i;  //�ڽڵ��еĹؼ������
	BTNode *pt; //��¼��ѯ���Ľ��ָ��
};
 
//��ѯ�ؼ�����ĳһ���ڵ��е�λ�ã�����λ�����
int Search(BTree p, int K) {
	int i = 0, j;
	for (j = 1; j <= p->keynum; j++)
		if (p->node[j].key <= K)
			i = j;
	return i;
}

//��M�׵�B���ϲ��ҹؼ��֣����ؽ��(tag,i,pt)
//������ɹ���tag=1,�ؼ�����pt��ָ�ڵ�ĵ�i��Ԫ��
//�������ʧ�ܣ�tag=0,�ؼ�����pt��ָ�ڵ�ĵ�i���͵�i+1��Ԫ��֮��
Result SearchBTree(BTree T, int K) {
	BTree p = T, q = NULL;   //���ҹ����У�qָ��˫�׽��;
	Result r;
	int found = false;
	int i = 0;
	while (p && !found) {
		i = Search(p, K);
		if (i > 0 && p->node[i].key == K)
			found = TRUE;
		else {
			q = p;
			p = p->node[i].ptr;
		}
	}
	r.i = i;
	if (found) {
		r.tag = 1;
		r.pt = p;
	}
	else {
		r.tag = 0;
		r.pt = q;
	}
	return r;
}

//���ؼ���key������ָ����뵽p��[i+1]�ڵ㴦
void Insert(BTree *p, int i, int key, BTree ap) {
	int j = 0;
	for (j = (*p)->keynum; j > i; j--) //�ճ�i+1����λ��
		(*p)->node[j + 1] = (*p)->node[j];
	(*p)->node[i + 1].key = key;
	(*p)->node[i + 1].recptr = key;
	(*p)->node[i + 1].ptr = ap;
	(*p)->keynum++;
}  

//�����q����Ϊ�����ڵ㣬ǰһ�뱣������һ�������������ap��
void Split(BTree *q, BTree *ap) {
	int i, s = (m + 1) / 2;
	(*ap) = (BTree)malloc(sizeof(BTNode));  //�����µĽ��
	(*ap)->node[0].ptr = (*q)->node[s].ptr;
	for (i = s + 1; i <= m; i++) {
		(*ap)->node[i - s] = (*q)->node[i];
		if ((*ap)->node[i - s].ptr)
			(*ap)->node[i - s].ptr->parent = *ap;
	}
	(*ap)->keynum = m - s;
	(*ap)->parent = (*q)->parent;
	(*q)->keynum = s - 1;
}

//�����µĸ���㣬������Ϣ(T,r,ap)��ԭT��apΪ������ָ��
void NewRoot(BTree *T, int key, BTree ap) {
	printf("������һ����������\n");
	BTree p;
	p=(BTree)malloc(sizeof(BTNode));
	p->node[0].ptr=*T;
	*T=p;
	if((*T)->node[0].ptr)
		(*T)->node[0].ptr->parent=*T;
	(*T)->parent=NULL;
	(*T)->keynum=1;
	(*T)->node[1].key=key;
	(*T)->node[1].recptr=key;
	(*T)->node[1].ptr=ap;
	if((*T)->node[1].ptr)
		(*T)->node[1].ptr->parent=*T;
}   

//��m�׵�B��T�Ͻ��*q��key[i]��key[i+1]֮�����ؼ���K��ָ��r
//�����������˫�������н����ѵ�����ʹT����m��B��
void InsertBTree(BTree *T,int key,BTree q,int i) {
	BTree ap = NULL;
	Status finished = FALSE;
	int s;
	int rx;
	rx = key;
	while (q && !finished) {
		Insert(&q, i, rx, ap);
		if (q->keynum < m)
			finished = TRUE;
		else {  //���ѽ��
			printf("\n������");
			s = (m + 1) / 2;
			rx = q->node[s].recptr;
			Split(&q, &ap);
			q = q->parent;
			if (q)
				i = Search(q, key);
		}
	}
	if (!finished)
		NewRoot(T,rx,ap);
	printf("\n��ɲ��룬����Ľ���ַΪ��%d",ap);
}

void print(BTNode c, int i)
{
	printf("(%d)", c.node[i].key);
}
int main()
{
	int r[N] = { 22,16,41,58,8,11,12,16,17,22,23,31,41,52,58,59,61 };
	BTree T = NULL;
	Result s;
	int i;
	for (i = 0; i < N; i++)
	{
		s = SearchBTree(T, r[i]);
		if (!s.tag)
			InsertBTree(&T, r[i], s.pt, s.i);
	}
	printf("\n����������Ҽ�¼�Ĺؼ���: ");
	scanf_s("%d", &i);
	s = SearchBTree(T, i);
	if (s.tag)
		print(*(s.pt), s.i);
	else
		printf("û�ҵ�");
	printf("\n");

	getchar();
	getchar();
	return 0;
}
