// 二叉平衡树实现.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdlib.h"
#include "stdio.h"   

#define TRUE 1
#define FALSE 0
#define ERROR -1
#define OK 1
#define MAXSIZE 100

typedef int Status;
typedef struct BiTNode {
	int data;
	int bf;
	struct BiTNode *lchild, *rchild;
}BiTNode,*BiTree;    

//对以p为根结点的二叉排序树做右旋转
//处理之后，p指向新的根结点，即旋转之前根结点的左孩子
void R_Rotate(BiTree *p) {
	BiTree L;
	L = (*p)->lchild;
	(*p)->lchild = L->rchild;
	L->rchild = *p;
	*p = L;
	printf("进行了一次右旋转\n");
}

//对以p为根结点的二叉排序树做左旋转
//处理之后，p指向新的根结点，即旋转之前的根结点的右孩子
void L_Rotate(BiTree *p) {
	BiTree R;
	R = (*p)->rchild;
	(*p)->rchild = R->lchild;
	R->lchild = *p;
	*p = R;
	printf("进行了一次左旋转\n");
}

#define LH 1
#define EH 0
#define RH -1

//对二叉排序树做左平衡处理
//需要做左平衡处理，说明左侧的平衡因子绝对值大于1
void LeftBalance(BiTree *T) {
	printf("\n进行一次左平衡处理，其中");
	BiTree L, Lr;
	L = (*T)->lchild;   //查看T的左孩子的平衡因子
	switch (L->bf) {
	case LH:    //说明结点在左孩子的左子树，同向只需做单次右旋转即可
		(*T)->bf = L->bf=EH;
		R_Rotate(T);
		break;
	case RH:  //说明结点在左孩子的右子树，出现不同向，需要做左平衡处理，旋转两次
		Lr = L->rchild;  //找到左子树的右孩子，并查看其平衡因子，该结点的位置决定旋转后的T和T的左孩子平衡因子
		switch (Lr->bf) {
		case LH:    //结点在左孩子的右子树根结点下的左侧，进行两次旋转后，其平衡点的改变
			(*T)->bf = RH;
			L->bf = EH;
			break;
		case EH:
			(*T)->bf = L->bf = EH;
			break;
		case RH:
			(*T)->bf = EH;
			L->bf = LH;
			break;
		}
		L_Rotate(&(*T)->lchild);
		R_Rotate(T);
	}
	printf("左平衡处理完成后，T所指的结点数据：%d\n", (*T)->data);
}

//对二叉排序树做右平衡处理
//需要做右平衡处理，说明右侧的平衡因子绝对值大于1
void RightBalance(BiTree *T) {
	printf("\n进行一次右平衡处理，其中");
	BiTree R, Rl;
	R = (*T)->rchild; //查看T右孩子的平衡因子
	switch (R->bf) {
	case RH: //说明结点在右孩子的右子树，同向只需向左做单旋处理
		L_Rotate(T);
		(*T)->bf = R->bf = EH;
		break;
	case LH: //说明结点在右孩子的左子树，不同向需要做右平衡处理，做两次旋转
		Rl = R->lchild; //查看右孩子的左子树的平衡因子
		switch (Rl->bf) {
		case LH:
			(*T)->bf = EH;
			R->bf = RH;
			break;
		case EH:
			(*T)->bf = R->bf = EH;
			break;
		case RH:
			(*T)->bf = LH;
			R->bf = EH;
			break;
		}
		R_Rotate(&(*T)->rchild);
		L_Rotate(T);
	}
	printf("右平衡处理完成后，T所指的结点数据：%d\n", (*T)->data);
}

Status InsertAVL(BiTree *T, int e, Status *taller) {
	if (!*T) {    //如果没有该结点，添加该节点
		(*T) = (BiTree)malloc(sizeof(BiTNode));
		(*T)->data = e;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->bf = EH;
		*taller = TRUE;
	}
	else {
		if (e==(*T)->data) {    //如果已经存在结点，则插入不成功
			*taller = FALSE;
			return FALSE;
		}
		if (e < (*T)->data) {  //在左子树中继续搜索
			if (!(InsertAVL(&(*T)->lchild, e, taller)))   //结点未插入
				return FALSE;
			if (*taller) {   //如果在左侧插入成功
				switch ((*T)->bf) {
				case LH:    //原本就是左侧高，左侧插入后需要做平衡处理
					LeftBalance(T);
					*taller = FALSE;
					break;
				case EH:   //原本是等高，左侧插入后T的平衡因子为左侧高
					(*T)->bf = LH;
					*taller = TRUE;
					break;
				case RH: //原本是右侧高，左侧插入后T的平衡因子为等高
					(*T)->bf = EH;
					*taller = FALSE;
					break;
				}
			}
		}
		else {//在右侧子树中搜索
			if (!InsertAVL(&(*T)->rchild, e, taller))   //未插入
				return FALSE;
			if (*taller) {  //如果在右侧插入成功
				switch ((*T)->bf) {
				case LH:  //原本是左侧高，插入后T的平衡因子为等高
					(*T)->bf = EH;
					*taller = FALSE;
					break;
				case EH: //原本是等高，插入后T的平衡因子为右侧高
					(*T)->bf = RH;
					*taller = TRUE;
					break;
				case RH: //原本是右侧高，右侧插入后需要进行平衡处理
					RightBalance(T);
					*taller = FALSE;
					break;
				}
			}
		}
	}
	return TRUE;
}

void ShowBiTree_Mid(BiTree T) {
	if (T == NULL)
		return;
	ShowBiTree_Mid(T->lchild);
	printf("%d--",T->data);
	ShowBiTree_Mid(T->rchild);
}

int main(void)
{
	int i;
	int a[10] = { 3,2,1,4,5,6,7,10,9,8 };
	BiTree T = NULL;
	Status taller;
	printf("按照中序排列输出：\n");
	for (i = 0; i < 10; i++)
	{
		InsertAVL(&T, a[i], &taller);
		ShowBiTree_Mid(T);
		printf("\nT所指的结点数据:%d, 其地址是:%d,其存储的地址是:%d\n",T->data,&T,T);
	}


	getchar();
	return 0;
}


