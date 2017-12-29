// ����������ʵ��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "io.h"
#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100

typedef int Status;

//���ڹ����������ȫ�ֱ���
int index = 1;
typedef char String[24];
String str; //�ַ�����ı���    

Status StrAssign(String T, char *chars) {
	int i;
	if (strlen(chars) > MAXSIZE)
		return ERROR;
	else {
		T[0] = strlen(chars);
		for (i = 1; i <= T[0]; i++)
			T[i] = *(chars+i-1);
		return OK;
	}
}

typedef char TElemType;
TElemType Nil = ' ';

Status visit(TElemType e) {
	printf("%c",e);
	return OK;
}

typedef struct BiTNode {
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode,*BiTree;   

Status InitBiTree(BiTree *T) {
	*T = NULL;
	return OK;
}

//���ٶ�����
void DestroyBiTree(BiTree *T) {
	if (*T) {
		if ((*T)->lchild)
			DestroyBiTree(&(*T)->lchild);
		if ((*T)->rchild)
			DestroyBiTree(&(*T)->rchild);
		free(*T);//�ͷŽ��ռ�
		*T = NULL;
	}
}

void CreatBiTree(BiTree *T) {
	TElemType ch;
	ch = str[index++];
	if (ch=='#')
		*T = NULL;
	else {
		*T =(BiTree)malloc(sizeof(BiTNode));
		if (!*T)
			exit(OVERFLOW);
		//ʹ��ǰ����Ĵ��򴴽�������
		(*T)->data = ch;
		CreatBiTree(&(*T)->lchild);   //����������
		CreatBiTree(&(*T)->rchild);   //����������
	}
}

Status BiTreeEmpty(BiTree T) {
	if (T)
		return FALSE;
	else
		return TRUE;
}

int BiTreeDepth(BiTree T) {
	int i, j;
	if (!T)
		return 0;
	if (T->lchild)
		i = BiTreeDepth(T->lchild);
	else
		i = 0;
	if (T->rchild)
		j = BiTreeDepth(T->rchild);
	else
		j = 0;
	return i > j ? i + 1 : j + 1;
}   

TElemType Root(BiTree T) {
	if (BiTreeEmpty(T))
		return Nil;
	else
		return T->data;
}

TElemType Value(BiTree p) {
	return p->data;
}

void Assign(BiTree p, TElemType e) {
	p->data = e;
}


//������ǰ�������
void PreOrderTraverse(BiTree T) {
	if (T == NULL)
		return;
	printf("%c",T->data);                    //����ʾ�������
	PreOrderTraverse(T->lchild);       //�ٱ���������
	PreOrderTraverse(T->rchild);      //�ٱ���������
}   

//�������и������
void InOrderTraverse(BiTree T) {
	if (T == NULL)
		return;
	InOrderTraverse(T->lchild);       //�ȱ���������
	printf("%c", T->data);                //����ʾ�������
	InOrderTraverse(T->rchild);      //�ٱ���������
}   

//��������������
void PostOrderTraverse(BiTree T) {
	if (T == NULL)
		return;
	PostOrderTraverse(T->lchild);  //�ȱ���������
	PostOrderTraverse(T->rchild);  //�ٱ���������
	printf("%c", T->data);                //��ʾ�������
}


int main()
{
	int i;
	BiTree T;
	TElemType e1;
	InitBiTree(&T);

	StrAssign(str, "ABDH#K###E##CFI###G#J##");

	CreatBiTree(&T);

	printf("����ն����������շ�%d(0:��,1:��) �������=%d\n",BiTreeEmpty(T),BiTreeDepth(T));

	getchar();
    return 0;
}

