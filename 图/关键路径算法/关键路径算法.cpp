// 关键路径算法.cpp : 定义控制台应用程序的入口点。
//关键路径算法：      
//找到AOE图中的每个活动的最早开始时间和最晚开始时间，
//然后比较他们，如果相等就说明这个活动在路径中没有空闲时间，
//此活动则为关键活动，活动之间的路径就为关键路径

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

int *etv, *ltv;  //存储活动最早开始时间和最晚开始时间
int *stack2;    //存储拓扑序列的反向顺序栈，用来求最晚开始时间
int top2;        //stack2的栈顶下标

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

//使用邻接矩阵构建邻接表    
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

//使用拓扑排序，得到活动最早开始时间数组*etv,并得到拓扑序列的反向顺序栈 *stack2
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
	etv = (int *)malloc(sizeof(int)*GL->numVex);  //活动最早发生时间数组
	for (i = 0; i < GL->numVex; i++) {
		etv[i] = 0;
	}
	stack2 = (int *)malloc(sizeof(int)*GL->numVex);   //存储拓扑序列反向顺序的栈
	printf("\nTopoLogicalSort:\n");
	while (top >= 0) {
		gettop = stack[top--];
		printf("%d->", GL->adjList[gettop].data);
		count++;
		stack2[++top2] = gettop;                                  //按照入度为0的顶点出stack栈入stack2栈
		for (e = GL->adjList[gettop].firstedge; e; e = e->next) {
			k = e->adjvex;
			if (!(--GL->adjList[k].in))
				stack[++top] = k;
			if (etv[gettop] + e->weight > etv[k])         //求各顶点最早活动发生时间
				etv[k] = etv[gettop] + e->weight;
		}
	}
	printf("\n");
	if (count < GL->numVex)
		return ERROR;
	else
		return OK;
}

//求关键路径，GL为无环有向网
void CriticalPath(GraphAdjList GL) {
	int i, j, k;
	int gettop;
	int ete, lte;
	int lengthSum;
	EdgeNode *e;


	TopoLogicalSort(GL);
	ltv = (int *)malloc(sizeof(int)*GL->numVex);
	for (i = 0; i < GL->numVex; i++)
		ltv[i] = etv[GL->numVex - 1];      //初始化最晚活动发生时间

	while (top2 != 0) {
		gettop = stack2[top2--];
		for (e = GL->adjList[gettop].firstedge; e; e = e->next) {    //求各顶点活动最迟发生的时间
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
	//遍历每一条边，得到某个活动最早开始时间和最迟开始时间
	for (i = 0; i < GL->numVex; i++) {
		for (e = GL->adjList[i].firstedge; e; e = e->next) {
			k = e->adjvex;
			ete = etv[i];    //活动最早发生时间
			lte = ltv[k] - e->weight;   //活动最晚发生时间
			if (ete == lte)    //该路径上没有空余，为关键路径
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

