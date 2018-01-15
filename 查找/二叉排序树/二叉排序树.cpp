// 二叉排序树.cpp : 定义控制台应用程序的入口点。
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

//递归查找二叉排序树中是否存在key
//f指向结点双亲，初始值为NULL
//若查找成功，则指针p指向数据元素节点，并返回True
//否则指针p指向路径上最后一个元素结点并返回False  

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

//插入数据，当二叉排序树中不存在关键字==key时，插入并返回TRUE,否则返回FALSE
Status InsertBST(BiTree *T, int key) {
	BiTree p, s;
	if (!SearchBST(*T, key, NULL, &p)) {   //查找完成后p的值已经改变为最接近插入点的结点
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

//删除二叉排序树中的结点并重连左右子树
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

//若二叉排序树存在关键字为key的数据元素时，删除该结点并返回TRUE，否则返回FLASE
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
	printf("中序遍历结果：\n");
	ShowBST(T);
	DeleteBST(&T,93);
	printf("\n删除后遍历结果：\n");
	ShowBST(T);

	getchar();
    return 0;
}

