// 二叉树链表实现2.cpp : 定义控制台应用程序的入口点。
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

//用于构造二叉树的全局变量
int index = 1;
typedef char String[24];
String str; //字符数组的别名    

Status StrAssign(String T, char *chars) {
	int i;
	if (strlen(chars) > MAXSIZE)
		return ERROR;
	else {
		T[0] = strlen(chars);
		for (i = 1; i <= T[0]; i++)
			T[i] = *(chars + i - 1);
		return OK;
	}
}

typedef char TElemType;
TElemType Nil = ' ';

Status visit(TElemType e) {
	printf("%c", e);
	return OK;
}

typedef struct BiTNode {
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

Status InitBiTree(BiTree *T) {
	*T = NULL;
	return OK;
}

//销毁二叉树
void DestroyBiTree(BiTree *T) {
	if (*T) {
		if ((*T)->lchild)
			DestroyBiTree(&(*T)->lchild);
		if ((*T)->rchild)
			DestroyBiTree(&(*T)->rchild);
		free(*T);//释放结点空间
		*T = NULL;
	}
}

void CreatBiTree(BiTree *T) {
	TElemType ch;
	ch = str[index++];
	if (ch == '#')
		*T = NULL;
	else {
		*T = (BiTree)malloc(sizeof(BiTNode));
		if (!T)
			exit(OVERFLOW);
		//使用前根序的次序创建二叉树
		(*T)->data = ch;
		CreatBiTree(&(*T)->lchild);   //构造左子树
		CreatBiTree(&(*T)->rchild);   //构造右子树
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


//二叉树前根序遍历
void PreOrderTraverse(BiTree T) {
	if (T == NULL)
		return;
	printf("%c", T->data);                    //先显示结点数据
	PreOrderTraverse(T->lchild);       //再遍历左子树
	PreOrderTraverse(T->rchild);      //再遍历右子树
}

//二叉树中根序遍历
void InOrderTraverse(BiTree T) {
	if (T == NULL)
		return;
	InOrderTraverse(T->lchild);       //先遍历左子树
	printf("%c", T->data);                //再显示结点数据
	InOrderTraverse(T->rchild);      //再遍历右子树
}

//二叉树后根序遍历
void PostOrderTraverse(BiTree T) {
	if (T == NULL)
		return;
	PostOrderTraverse(T->lchild);  //先遍历左子树
	PostOrderTraverse(T->rchild);  //再遍历右子树
	printf("%c", T->data);                //显示结点数据
}


int main()
{
	int i;
	BiTree T;
	TElemType e1;
	InitBiTree(&T);

	StrAssign(str, "ABDH#K###E##CFI###G#J##");

	CreatBiTree(&T);

	printf("构造空二叉树后，树空否？%d(0:否,1:是) 树的深度=%d\n", BiTreeEmpty(T), BiTreeDepth(T));
	e1 = Root(T);
	printf("二叉树的根结点:%c\n",e1);

	printf("二叉树前根序排列:\n");
	PreOrderTraverse(T);
	printf("\n二叉树中根序排列:\n");
	InOrderTraverse(T);
	printf("\n二叉树前跟序排列:\n");
	PostOrderTraverse(T);
	
	getchar();
	return 0;
}

