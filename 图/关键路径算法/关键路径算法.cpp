// �ؼ�·���㷨.cpp : �������̨Ӧ�ó������ڵ㡣
//�ؼ�·���㷨��      
//�ҵ�AOEͼ�е�ÿ��������翪ʼʱ�������ʼʱ�䣬
//Ȼ��Ƚ����ǣ������Ⱦ�˵��������·����û�п���ʱ�䣬
//�˻��Ϊ�ؼ�����֮���·����Ϊ�ؼ�·��

#include "stdafx.h"
#include "stdlib.h"
#include "io.h"
#include "time.h"
#include "math.h"

#define ERROR -1
#define OK 1
#define INFINITY 65535
#define MAXSIZE 30
#define MAXVEX 30   

typedef int Status;

typedef struct MGraph {
	int vex[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVex, numEdges;
}MGraph;

typedef struct EdgeNode {
	int adjvex;
	int weight;
	struct EdgeNode *next;
}EdgeNode;

typedef struct VertexNode {
	int in;
	int data;
	EdgeNode *firstedge;
}VertexNode, AdjList[MAXVEX];

typedef struct {
	AdjList adjList;
	int numVex, numEdges;
}graphAdjList, *GraphAdjList;

int *etv, *ltv;  //�洢����翪ʼʱ�������ʼʱ��
int *stack2;    //�洢�������еķ���˳��ջ������������ʼʱ��
int top2;        //stack2��ջ���±�

void CreatMGraph(MGraph *G) {
	int i, j;
	G->numVex = 10;
	G->numEdges = 13;

	for (i = 0; i < G->numVex; i++) {
		G->vex[i] = i;
	}
	for (i = 0; i < G->numVex; i++) {
		for (j = 0; j < G->numVex; j++) {
			if (i == j)
				G->arc[i][j] = 0;
			else
				G->arc[i][j] = INFINITY;
		}
	}
	G->arc[0][1] = 3;
	G->arc[0][2] = 4;
	G->arc[1][3] = 5;
	G->arc[1][4] = 6;
	G->arc[2][3] = 8;
	G->arc[2][5] = 7;
	G->arc[3][4] = 3;
	G->arc[4][6] = 9;
	G->arc[4][7] = 4;
	G->arc[5][7] = 6;
	G->arc[6][9] = 2;
	G->arc[7][8] = 5;
	G->arc[8][9] = 3;
}

//ʹ���ڽӾ��󹹽��ڽӱ�    
void CreateALGraph(MGraph MG, GraphAdjList *GL) {
	int i, j;
	EdgeNode *e;
	(*GL) = (GraphAdjList)malloc(sizeof(graphAdjList));

	(*GL)->numVex = MG.numVex;
	(*GL)->numEdges = MG.numEdges;
	for (i = 0; i < (*GL)->numVex; i++) {
		(*GL)->adjList[i].in = 0;
		(*GL)->adjList[i].firstedge = NULL;
		(*GL)->adjList[i].data = MG.vex[i];
	}
	for (i = 0; i < (*GL)->numVex; i++) {
		for (j = 0; j < (*GL)->numVex; j++) {
			if (MG.arc[i][j] != 0 && MG.arc[i][j] != INFINITY) {
				e = (EdgeNode *)malloc(sizeof(EdgeNode));
				e->adjvex = j;
				e->weight = MG.arc[i][j];
				e->next = (*GL)->adjList[i].firstedge;
				(*GL)->adjList[i].firstedge = e;
				(*GL)->adjList[j].in++;
			}
		}
	}
}

//ʹ���������򣬵õ�����翪ʼʱ������*etv,���õ��������еķ���˳��ջ *stack2
Status TopoLogicalSort(GraphAdjList GL) {
	int i, j, k;
	int *stack;
	int top = 0, gettop = 0;
	int count = 0;
	EdgeNode *e;

	stack = (int *)malloc(sizeof(int)*GL->numVex);
	printf("\nstack:\n");
	for (i = 0; i < GL->numVex; i++) {
		if (GL->adjList[i].in == 0) {
			stack[top++] = i;
			printf("stack[%d]:%d\n", top - 1, stack[top - 1]);
		}

	}
	top--;

	top2 = 0;
	etv = (int *)malloc(sizeof(int)*GL->numVex);  //����緢��ʱ������
	for (i = 0; i < GL->numVex; i++) {
		etv[i] = 0;
	}
	stack2 = (int *)malloc(sizeof(int)*GL->numVex);   //�洢�������з���˳���ջ
	printf("\nTopoLogicalSort:\n");
	while (top >= 0) {
		gettop = stack[top--];
		printf("%d->", GL->adjList[gettop].data);
		count++;
		stack2[++top2] = gettop;                                  //�������Ϊ0�Ķ����stackջ��stack2ջ
		for (e = GL->adjList[gettop].firstedge; e; e = e->next) {
			k = e->adjvex;
			if (!(--GL->adjList[k].in))
				stack[++top] = k;
			if (etv[gettop] + e->weight > etv[k])         //���������������ʱ��
				etv[k] = etv[gettop] + e->weight;
		}
	}
	printf("\n");
	if (count < GL->numVex)
		return ERROR;
	else
		return OK;
}

//��ؼ�·����GLΪ�޻�������
void CriticalPath(GraphAdjList GL) {
	int i, j, k;
	int gettop;
	int ete, lte;
	int lengthSum;
	EdgeNode *e;


	TopoLogicalSort(GL);
	ltv = (int *)malloc(sizeof(int)*GL->numVex);
	for (i = 0; i < GL->numVex; i++)
		ltv[i] = etv[GL->numVex - 1];      //��ʼ����������ʱ��

	while (top2 != 0) {
		gettop = stack2[top2--];
		for (e = GL->adjList[gettop].firstedge; e; e = e->next) {    //���������ٷ�����ʱ��
			k = e->adjvex;
			if (ltv[k] - e->weight < ltv[gettop])
				ltv[gettop] = ltv[k] - e->weight;
		}
	}
	printf("\nltv:\t");
	for (i = 0; i < GL->numVex; i++) {
		printf("%d->", ltv[i]);
	}
	printf("\netv:\t");
	for (i = 0; i < GL->numVex; i++) {
		printf("%d->", etv[i]);
	}
	printf("\n\n");

	lengthSum = 0;
	//����ÿһ���ߣ��õ�ĳ������翪ʼʱ�����ٿ�ʼʱ��
	for (i = 0; i < GL->numVex; i++) {
		for (e = GL->adjList[i].firstedge; e; e = e->next) {
			k = e->adjvex;
			ete = etv[i];    //����緢��ʱ��
			lte = ltv[k] - e->weight;   //�������ʱ��
			if (ete == lte)    //��·����û�п��࣬Ϊ�ؼ�·��
			{
				printf("<v%d--v%d> length:%d\n", GL->adjList[i].data, GL->adjList[k].data, e->weight);
				lengthSum += e->weight;
			}
		}
	}
	printf("\nlengthSum: %d", lengthSum);
}

int main()
{
	MGraph MG;
	GraphAdjList GL;
	CreatMGraph(&MG);
	CreateALGraph(MG, &GL);
	CriticalPath(GL);

	getchar();
	return 0;
}

