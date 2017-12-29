// 线索二叉树.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "io.h"
#include "math.h"
#include "time.h"  
#include<iostream>

using namespace  std;
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0  

#define MAXSIZE 100   

typedef int Status;
typedef char TElemType;
typedef enum {Link,Thread}PointerTag;

typedef struct  BiThrNode{
	TElemType data;
	struct BiThrNode *lchild;
	struct BiThrNode *rchild;
	PointerTag lTag;
	PointerTag rTag;
} BiThrNode,*BiThrTree;   

TElemType Nil = '#';   

Status visit(TElemType e) {
	printf("%c",e);
	return OK;
}

//按前序输入二叉树，构造二叉线索树 （设置结点的状态位） 
Status CreateBiThrTree(BiThrTree *T) {
	TElemType h;
	cin>>h;

	if (h == Nil)
		*T = NULL;
	else {
		*T = (BiThrTree)malloc(sizeof(BiThrNode));
		if (!*T)
			exit(OVERFLOW);
		(*T)->data = h;
		CreateBiThrTree(&(*T)->lchild);
		if ((*T)->lchild)
			(*T)->lTag = Link;
		CreateBiThrTree(&(*T)->rchild);
		if ((*T)->rchild)
			(*T)->rTag = Link;
	}
	return OK;
}

//中序遍历二叉树，进行中序线索化
BiThrTree pre;
void InOrderThrTree(BiThrTree p) {
	if (p) {
		InOrderThrTree(p->lchild);
		if (!p->lchild) {
			p->lTag = Thread;
			p->lchild = pre;
		}
		//对于后继的判断，由于p的后继点还没有访问到，因此对p的前驱的右孩子进行判断
		if (!pre->rchild) {
			pre->rTag = Thread;
			pre->rchild = p;
		}
		pre = p;
		InOrderThrTree(p->rchild);
	}
}

//中序遍历二叉树，并添加头结点
Status InOrderThreading(BiThrTree *Thrt, BiThrTree T) {
	*Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
	if (!(*Thrt))
		exit(OVERFLOW);
	(*Thrt)->lTag = Link;
	(*Thrt)->rTag = Thread;
	(*Thrt)->rchild = (*Thrt);
	if (!T)
		(*Thrt)->lchild = (*Thrt);
	else {
		(*Thrt)->lchild = T;
		pre = (*Thrt);
		InOrderThrTree(T);
		pre->rchild = *Thrt;
		pre->rTag = Thread;
		(*Thrt)->rchild = pre;
		}
	return OK;
}

//中序遍历二叉线索树（含头结点）
Status InOrderTraverse_Thr(BiThrTree T) {
	BiThrTree p;
	p = T->lchild;
	while (p!=T) {
		while (p->lTag == Link)
			p = p->lchild;
		if(!visit(p->data))
			return ERROR;
			while (p->rTag == Thread&&p->rchild != T) {
				p = p->rchild;
				visit(p->data);
			}
			p = p->rchild;
	}
	return OK;
}
int main()
{
	BiThrTree H, T;
	printf("请按照前序排列出入二叉树（如：'ABDH##I##EJ###CF##G##'）\n");
	CreateBiThrTree(&T);
	InOrderThreading(&H, T);
	printf("中序遍历（输出）二叉线索树：\n");
	InOrderTraverse_Thr(H);
	printf("\n");

	getchar();
	getchar();
    return 0;
}

