// ������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "io.h"
#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20  

typedef int Status;
typedef int QElemType;

typedef struct QNode {
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct {
	QueuePtr front, rear;
}LinkQueue;

Status visit(QElemType e) {
	printf("%d\n",e);
	return OK;
}

//��ʼ��������
Status InitQueue(LinkQueue *Q) {
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front)
		return ERROR;
	Q->front->next = NULL;
	return OK;
}

//���ٶ���,ͷ�����ڴ�ռ䱻���
Status DestroyQueue(LinkQueue *Q) {
	while (Q->front) {
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
	return OK;
}

//��ն��У�ͷ�����ڴ�ռ仹��
Status ClearQueue(LinkQueue *Q) {
	QueuePtr p, q;
	Q->rear = Q->front;
	p = Q->front->next;
	Q->front->next = NULL;
	while (p) {
		q = p;
		p = p->next;
		free(q);
	}
	return OK;
}

Status QueueEmpty(LinkQueue Q) {
	if (Q.front == Q.rear)
		return TRUE;
	else
		return FALSE;
}

int QueueLength(LinkQueue Q) {
	int i = 0;
	QueuePtr p;
	p = Q.front;
	while (p != Q.rear) {
		i++;
		p = p->next;
	}
	return i;
}

Status GetHead(LinkQueue Q, QElemType *e) {
	if (Q.front == Q.rear)
		return ERROR;
	*e = Q.front->next->data;
	return OK;
}

Status InQueue(LinkQueue *Q, QElemType e) {
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
		exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
	return OK;
}

Status DeQueue(LinkQueue *Q,QElemType *e) {
	QueuePtr p;
	if (Q->front == Q->rear)
		return ERROR;
	p = Q->front->next;
	*e = p->data;
	Q->front->next = p->next;
	if (Q->rear == p)
		Q->rear = Q->front;
	free(p);
	return OK;
	free(p);
}

Status QueueTraverse(LinkQueue Q) {
	QueuePtr p;
	p = Q.front->next;
	while (p) {
		visit(p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}
int main()
{
	int i;
	QElemType d;
	LinkQueue q;
	i = InitQueue(&q);
	if (i)
		printf("�ɹ��ع�����һ���ն���!\n");
	printf("�Ƿ�ն��У�%d(1:�� 0:��)  ", QueueEmpty(q));
	printf("���еĳ���Ϊ%d\n", QueueLength(q));
	InQueue(&q, -5);
	InQueue(&q, 5);
	InQueue(&q, 10);
	printf("����3��Ԫ��(-5,5,10)��,���еĳ���Ϊ%d\n", QueueLength(q));
	printf("�Ƿ�ն��У�%d(1:�� 0:��)  ", QueueEmpty(q));
	printf("���е�Ԫ������Ϊ��");
	QueueTraverse(q);
	i = GetHead(q, &d);
	if (i == OK)
		printf("��ͷԪ���ǣ�%d\n", d);
	DeQueue(&q, &d);
	printf("ɾ���˶�ͷԪ��%d\n", d);
	i = GetHead(q, &d);
	if (i == OK)
		printf("�µĶ�ͷԪ���ǣ�%d\n", d);
	ClearQueue(&q);
	printf("��ն��к�,q.front=%u q.rear=%u q.front->next=%u\n", (unsigned int)q.front, (unsigned int)q.rear, (unsigned int)q.front->next);
	DestroyQueue(&q);
	printf("���ٶ��к�,q.front=%u q.rear=%u\n", q.front, q.rear);

	getchar();
	return 0;
}

