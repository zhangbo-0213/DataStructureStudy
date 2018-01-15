// ����������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"    

#define ERROE -1
#define OK 1
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100

typedef int Status;

typedef struct BiTNode {
	int data;
	struct BiTNode *lchild, *rchild;
}BiTNode,*BiTree;

//�ݹ���Ҷ������������Ƿ����key
//fָ����˫�ף���ʼֵΪNULL
//�����ҳɹ�����ָ��pָ������Ԫ�ؽڵ㣬������True
//����ָ��pָ��·�������һ��Ԫ�ؽ�㲢����False  

Status SearchBST(BiTree T,int key,BiTree f,BiTree *p) {
	if (!T) {
		*p = f;
		return FALSE;
	}
	else if ( key==T->data) {
		*p = T;
		return TRUE;
	}
	else if (key < T->data) {
		f = T;
		T = T->lchild;
		return SearchBST(T, key, f, p);
	}
	else {
		f = T;
		T = T->rchild;
		return SearchBST(T,key,f,p);
	}
}

//�������ݣ��������������в����ڹؼ���==keyʱ�����벢����TRUE,���򷵻�FALSE
Status InsertBST(BiTree *T, int key) {
	BiTree p, s;
	if (!SearchBST(*T, key, NULL, &p)) {   //������ɺ�p��ֵ�Ѿ��ı�Ϊ��ӽ������Ľ��
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = key;
		s->lchild = NULL;
		s->rchild = NULL;
		if (!p)
			*T = s;
		else if (key < p->data)
			p->lchild = s;
		else
			p->rchild = s;
		return TRUE;
	}
	else
		return FALSE;
}

//ɾ�������������еĽ�㲢������������
Status Delete(BiTree *	p) {
	BiTree q, s;
	if ((*p)->lchild == NULL) {
		q = *p;
		*p = (*p)->rchild;
		free(q);
	}
	else if ((*p)->rchild == NULL) {
		q = *p;
		*p = (*p)->lchild;
		free(q);
	}
	else {
		q = *p;
		s = (*p)->lchild;
		while (s->rchild) {
			q = s;
			s = s->rchild;
		}
		(*p)->data = s->data;
		if ((q != *p))
			q->rchild = s->lchild;
		else
			q->lchild = s->lchild;
		free(s);
	}
	return TRUE;
}

//���������������ڹؼ���Ϊkey������Ԫ��ʱ��ɾ���ý�㲢����TRUE�����򷵻�FLASE
Status DeleteBST(BiTree *T, int key) {
	if (!*T)
		return FALSE;
	else if (key == (*T)->data)
		return Delete(T);
	else if (key < (*T)->data)
		return DeleteBST(&(*T)->lchild, key);
	else
		return DeleteBST(&(*T)->rchild, key);
}

void  ShowBST(BiTree T) {
	if (T == NULL)
		return;
	ShowBST(T->lchild);
	printf("%d--", T->data);
	ShowBST(T->rchild);
}
int main()
{
	int i;
	int a[10] = { 62,88,58,47,35,73,51,99,37,93 };
	BiTree T = NULL;

	for (i = 0; i < 10; i++) {
		InsertBST(&T,a[i]);
	}
	printf("������������\n");
	ShowBST(T);
	DeleteBST(&T,93);
	printf("\nɾ������������\n");
	ShowBST(T);

	getchar();
    return 0;
}

