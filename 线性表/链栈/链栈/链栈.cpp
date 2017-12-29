// ��ջ.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdio.h"
#include "io.h"
#include "math.h"
#include "time.h"
#include "stdlib.h"


#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20

typedef int Status;
typedef int SElemType;

//����ڵ�
typedef struct StackNode {
	SElemType data;
	struct StackNode *next;
}StackNode,*LinkStackPtr;

typedef struct {
	LinkStackPtr top;
	int count;
}LinkStack;

//�����ջ
Status InitStack(LinkStack *S) {
	S->top = (LinkStackPtr)malloc(sizeof(StackNode));
	if (!S->top)
		return ERROR;
	S->top = NULL;
	S->count = 0;
	return OK;
}

//���ջ
Status ClearStack(LinkStack *S) {
	LinkStackPtr p, q;
	p = S->top;
	while (p) {
		q = p;
		p = p->next;
		free(q);
	}
	S->count = 0;
	return OK;
}

//ջ�Ƿ�Ϊ��
Status StackEmpty(LinkStack S) {
	if (S.count == 0)
		return TRUE;
	else
		return FALSE;
}

int StackLength(LinkStack S) {
	return S.count;
}

//���ջ��Ԫ��
Status GetTop(LinkStack S, SElemType *e) {
	if (S.top == NULL)
		return ERROR;
	else
		*e = S.top->data;
	return OK;
}

//��ջ����
Status Push(LinkStack *S, SElemType e) {
	LinkStackPtr s = (LinkStackPtr)malloc(sizeof(StackNode));
	s->data = e;
	s->next = S->top;
	S->top = s;
	S->count++;
	return OK;
}

//��ջ����
Status Pop(LinkStack *S, SElemType *e) {
	if (StackEmpty(*S))
		return ERROR;
	LinkStackPtr p;
	p = S->top;
	*e = p->data;
	S->top = p->next;
	free(p);
	S->count--;
	return OK;
}

Status visit(SElemType c)
{
	printf("%d ", c);
	return OK;
}

Status StackTraverse(LinkStack S) {
	LinkStackPtr p;
	p = S.top;
	while (p) {
		visit(p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}
int main()
{
	int j;
	LinkStack s;
	int e;
	if (InitStack(&s) == OK)
		for (j = 1; j <= 10; j++)
			Push(&s,j);
	printf("ջ�е�Ԫ������Ϊ��");
	StackTraverse(s);
	Pop(&s,&e);
	printf("������Ԫ�� e=%d\n",e);
	printf("ջ�շ�%d(1:�� 0:��)\n",StackEmpty(s));
	GetTop(s,&e);
	printf("ջ��Ԫ�� e=%d ջ�ĳ���Ϊ%d\n",e,StackLength(s));
	ClearStack(&s);
	printf("���ջ��ջ�շ�%d(1:�� 0:��",StackEmpty(s));

    return 0;
}

