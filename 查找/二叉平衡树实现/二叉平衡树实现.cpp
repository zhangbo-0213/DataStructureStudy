// ����ƽ����ʵ��.cpp : �������̨Ӧ�ó������ڵ㡣
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

//����pΪ�����Ķ���������������ת
//����֮��pָ���µĸ���㣬����ת֮ǰ����������
void R_Rotate(BiTree *p) {
	BiTree L;
	L = (*p)->lchild;
	(*p)->lchild = L->rchild;
	L->rchild = *p;
	*p = L;
	printf("������һ������ת\n");
}

//����pΪ�����Ķ���������������ת
//����֮��pָ���µĸ���㣬����ת֮ǰ�ĸ������Һ���
void L_Rotate(BiTree *p) {
	BiTree R;
	R = (*p)->rchild;
	(*p)->rchild = R->lchild;
	R->lchild = *p;
	*p = R;
	printf("������һ������ת\n");
}

#define LH 1
#define EH 0
#define RH -1

//�Զ�������������ƽ�⴦��
//��Ҫ����ƽ�⴦��˵������ƽ�����Ӿ���ֵ����1
void LeftBalance(BiTree *T) {
	printf("\n����һ����ƽ�⴦������");
	BiTree L, Lr;
	L = (*T)->lchild;   //�鿴T�����ӵ�ƽ������
	switch (L->bf) {
	case LH:    //˵����������ӵ���������ͬ��ֻ������������ת����
		(*T)->bf = L->bf=EH;
		R_Rotate(T);
		break;
	case RH:  //˵����������ӵ������������ֲ�ͬ����Ҫ����ƽ�⴦����ת����
		Lr = L->rchild;  //�ҵ����������Һ��ӣ����鿴��ƽ�����ӣ��ý���λ�þ�����ת���T��T������ƽ������
		switch (Lr->bf) {
		case LH:    //��������ӵ�������������µ���࣬����������ת����ƽ���ĸı�
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
	printf("��ƽ�⴦����ɺ�T��ָ�Ľ�����ݣ�%d\n", (*T)->data);
}

//�Զ�������������ƽ�⴦��
//��Ҫ����ƽ�⴦��˵���Ҳ��ƽ�����Ӿ���ֵ����1
void RightBalance(BiTree *T) {
	printf("\n����һ����ƽ�⴦������");
	BiTree R, Rl;
	R = (*T)->rchild; //�鿴T�Һ��ӵ�ƽ������
	switch (R->bf) {
	case RH: //˵��������Һ��ӵ���������ͬ��ֻ����������������
		L_Rotate(T);
		(*T)->bf = R->bf = EH;
		break;
	case LH: //˵��������Һ��ӵ�����������ͬ����Ҫ����ƽ�⴦����������ת
		Rl = R->lchild; //�鿴�Һ��ӵ���������ƽ������
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
	printf("��ƽ�⴦����ɺ�T��ָ�Ľ�����ݣ�%d\n", (*T)->data);
}

Status InsertAVL(BiTree *T, int e, Status *taller) {
	if (!*T) {    //���û�иý�㣬��Ӹýڵ�
		(*T) = (BiTree)malloc(sizeof(BiTNode));
		(*T)->data = e;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->bf = EH;
		*taller = TRUE;
	}
	else {
		if (e==(*T)->data) {    //����Ѿ����ڽ�㣬����벻�ɹ�
			*taller = FALSE;
			return FALSE;
		}
		if (e < (*T)->data) {  //���������м�������
			if (!(InsertAVL(&(*T)->lchild, e, taller)))   //���δ����
				return FALSE;
			if (*taller) {   //�����������ɹ�
				switch ((*T)->bf) {
				case LH:    //ԭ���������ߣ����������Ҫ��ƽ�⴦��
					LeftBalance(T);
					*taller = FALSE;
					break;
				case EH:   //ԭ���ǵȸߣ��������T��ƽ������Ϊ����
					(*T)->bf = LH;
					*taller = TRUE;
					break;
				case RH: //ԭ�����Ҳ�ߣ��������T��ƽ������Ϊ�ȸ�
					(*T)->bf = EH;
					*taller = FALSE;
					break;
				}
			}
		}
		else {//���Ҳ�����������
			if (!InsertAVL(&(*T)->rchild, e, taller))   //δ����
				return FALSE;
			if (*taller) {  //������Ҳ����ɹ�
				switch ((*T)->bf) {
				case LH:  //ԭ�������ߣ������T��ƽ������Ϊ�ȸ�
					(*T)->bf = EH;
					*taller = FALSE;
					break;
				case EH: //ԭ���ǵȸߣ������T��ƽ������Ϊ�Ҳ��
					(*T)->bf = RH;
					*taller = TRUE;
					break;
				case RH: //ԭ�����Ҳ�ߣ��Ҳ�������Ҫ����ƽ�⴦��
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
	printf("�����������������\n");
	for (i = 0; i < 10; i++)
	{
		InsertAVL(&T, a[i], &taller);
		ShowBiTree_Mid(T);
		printf("\nT��ָ�Ľ������:%d, ���ַ��:%d,��洢�ĵ�ַ��:%d\n",T->data,&T,T);
	}


	getchar();
	return 0;
}


