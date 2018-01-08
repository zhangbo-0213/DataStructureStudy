// 拓扑排序算法.cpp : 定义控制台应用程序的入口点。

//拓扑排序是对有向无环图构造拓扑序列的过程
//拓扑排序算法基本思想：
//将图中入度为0的顶点入栈，删除输出该顶点，并删除以该顶点为弧尾的弧
//重复以上步骤
//直到输出全部的顶点或者不存在入度为0的顶点为止

#include "stdafx.h"
#include "stdlib.h"
#include "io.h"
#include "time.h"
#include "math.h"

#define OK 1
#define ERROR -1
#define MAXVEX 14
#define MAXEDGE 20
#define INFINITY 65535

typedef int Status;

typedef struct EdgeNode {
	int adjvex;
	int weight;
	struct EdgeNode *next;
}EdgeNode;

typedef struct VertexNode {
	int in;
	int data;
	EdgeNode *firstedge;
}VertexNode,AdjList[MAXVEX];

typedef struct {
	int numVertex, numEdges;
	AdjList adjList;
}graphAdjList,*GraphAdjList;

//邻接矩阵结构
typedef struct {
	int vex[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertex, numEdge;
}MGraph;

void CreateMGraph(MGraph *G) {
	G->numVertex = MAXVEX;
	G->numEdge = MAXEDGE;
	int i,j;
	for (i = 0; i < G->numVertex; i++)
		G->vex[i] = i;
	for (i = 0; i < G->numVertex; i++) {
		for (j = 0; j < G->numVertex; j++) {
			G->arc[i][j] = 0;
		}
	}
	G->arc[0][4] = 1;
	G->arc[0][5] = 1;
	G->arc[0][11] = 1;
	G->arc[1][2] = 1;
	G->arc[1][4] = 1;
	G->arc[1][8] = 1;
	G->arc[2][5] = 1;
	G->arc[2][6] = 1;
	G->arc[2][9] = 1;
	G->arc[3][2] = 1;
	G->arc[3][13] = 1;
	G->arc[4][7] = 1;
	G->arc[5][8] = 1;
	G->arc[5][12] = 1;
	G->arc[6][5] = 1;
	G->arc[8][7] = 1;
	G->arc[9][10] = 1;
	G->arc[9][11] = 1;
	G->arc[10][13] = 1;
	G->arc[12][9] = 1;
}

//邻接矩阵图转换为邻接表图
void CreateGraphAdjList(MGraph G,GraphAdjList *GL) {
	int i, j;
	EdgeNode *e;

	*GL = (GraphAdjList)malloc(sizeof(graphAdjList));
	(*GL)->numEdges = G.numEdge;
	(*GL)->numVertex = G.numVertex;
	for (i = 0; i < (*GL)->numVertex; i++) {
		(*GL)->adjList[i].in = 0;
		(*GL)->adjList[i].data = G.vex[i];
		(*GL)->adjList[i].firstedge = NULL;
	}

	//使用头插法建立边表
	for (i = 0; i < (*GL)->numVertex; i++) {
		for (j = 0; j < (*GL)->numVertex; j++) {
			if (G.arc[i][j] == 1) {
				e = (EdgeNode *)malloc(sizeof(EdgeNode));
				e->adjvex = j;
				e->next = (*GL)->adjList[i].firstedge;
				(*GL)->adjList[i].firstedge = e;
				(*GL)->adjList[j].in++;
			}
		}
	}
}

//拓扑排序，若GL无回路输出拓扑排序序列，否则返回错误
Status TopologicSort(GraphAdjList GL) {
	int *stack; //存储入度为0的顶点下标栈
	int i, j,k;
	int gettop;
	int count = 0;
	int top = 0;

	EdgeNode *e;

	stack = (int *)malloc(sizeof(int)*GL->numVertex);
	//入度为0的顶点入栈
	for (i = 0; i < GL->numVertex; i++) {
		if (GL->adjList[i].in==0) {
			stack[top++] = i;	
			printf("\nstack[%d]:%d",top-1,i);
		}
	}

	printf("\n\n");
	top--;
	while (top >= 0) {
		gettop = stack[top--];
		printf("%d->", GL->adjList[gettop].data);
		count++;
		
		for (e = GL->adjList[gettop].firstedge; e;e = e->next) {
			k = e->adjvex;
			if (!(--GL->adjList[k].in))  //将与i邻接的j顶点的入度减一，表示删除这条弧，如果j的入度为0，入栈
			{
				stack[++top] = k;
				printf("\ntop:%d  stack[top]: %d\n",top,k);
				//printf("\nk=%d,top=%d\n",k,top);
			}
		}
	}
	printf("\n");
	if (count < GL->numVertex)
		return ERROR;
	else
		return OK;
}

int main()
{
	MGraph G;
	GraphAdjList GL;
	CreateMGraph(&G);
	CreateGraphAdjList(G, &GL);
	TopologicSort(GL);

	getchar();
    return 0;
}

