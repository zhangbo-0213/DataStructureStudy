// 最小生成树_Kruskal.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "io.h"
#include "time.h"
#include "math.h"

#define ERROR -1
#define OK 1

typedef int Status;

#define MAXEDGE 20
#define MAXVEX 20
#define INFINITY 65535   

typedef struct {

	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

typedef struct {
	int begin;
	int end;
	int weight;
}Edge;

void CreateMGraph(MGraph *G)
{
	int i, j;

	G->numEdges = 15;
	G->numVertexes = 9;

	for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
	{
		for (j = 0; j < G->numVertexes; j++)
		{
			if (i == j)
				G->arc[i][j] = 0;
			else
				G->arc[i][j] = G->arc[j][i] = INFINITY;
		}
	}

	G->arc[0][1] = 10;
	G->arc[0][5] = 11;
	G->arc[1][2] = 18;
	G->arc[1][8] = 12;
	G->arc[1][6] = 16;
	G->arc[2][8] = 8;
	G->arc[2][3] = 22;
	G->arc[3][8] = 21;
	G->arc[3][6] = 24;
	G->arc[3][7] = 16;
	G->arc[3][4] = 20;
	G->arc[4][7] = 7;
	G->arc[4][5] = 26;
	G->arc[5][6] = 17;
	G->arc[6][7] = 19;

	for (i = 0; i < G->numVertexes; i++)
	{
		for (j = i; j < G->numVertexes; j++)
		{
			G->arc[j][i] = G->arc[i][j];
		}
	}
}

//交换边
void Swapn(Edge *edges,int i,int j) {
	int temp;
	temp = edges[i].begin;
	edges[i].begin = edges[j].begin;
	edges[j].begin = temp;
	temp = edges[i].end;
	edges[i].end= edges[j].end;
	edges[j].end = temp;
	temp = edges[i].weight;
	edges[i].weight = edges[j].weight;
	edges[j].weight = temp;
}

//对权值进行排序
void Sort(Edge edges[],MGraph *G) {
	int i, j;
	for (i = 0; i < G->numEdges; i++) {
		for (j = i + 1; j < G->numEdges; j++) {
			if (edges[i].weight > edges[j].weight) {
				Swapn(edges, i, j);
			}
		}
	}
	printf("权值排序完成后：\n");
	for (i = 0; i < G->numEdges; i++) {
		printf("(%d--%d): %d\n",edges[i].begin,edges[i].end,edges[i].weight);
	}
}

//查找通路顶点的下标,该函数的时间复杂度 loge   
int Find(int *parent, int i) {
	while (parent[i] > 0)
		i = parent[i];
	return i;
}

void ShowParentArray(int *parent,MGraph G) {
	int i=0;
	printf("\nparent： ");
	while (i < G.numVertexes) {
		printf("%d ", parent[i]);
		i++;
	}
	printf("\n");
}


//最小生成树Kruskal算法
//Kruskal算法从边开始，依次选择权值最小的边来构成最小生成树，比较重要的两步：          

//-将边按照权值进行排序，从权值最小的边开始
//- 检查被选择的边是否构成环路，如没有构成环路，则记录边的顶点下标，否则放弃这条边
void MiniSpanTree_Kruskal(MGraph G) {
	Edge edges[MAXEDGE];
	int i, j,k;
	k = 0;
	for (i = 0; i < G.numVertexes; i++) {
		for (j = i + 1; j < G.numVertexes; j++) {
			if (G.arc[i][j] != INFINITY) {
				edges[k].begin = i;
				edges[k].end = j;
				edges[k].weight = G.arc[i][j];
				k++;
			}
		}
		
	}
	Sort(edges,&G);

	int parent[MAXVEX];
	for (i = 0; i < G.numVertexes; i++)
		parent[i] = 0;

	int n, m;
	for (i = 0; i < G.numEdges; i++) {
		//判断是否构成了环路，如果n=m，则形成了环路
		n = Find(parent,edges[i].begin);
		m = Find(parent,edges[i].end);
		if (n != m) {     
			parent[n] = m;
			printf("n=%d, m=%d\n",n,m);
			printf("选择的边：(%d--%d)  权值:%d",edges[i].begin,edges[i].end,edges[i].weight);
			ShowParentArray(parent,G);
		}
	}
}
int main()
{
	MGraph G;
	CreateMGraph(&G);
	MiniSpanTree_Kruskal(G);
	getchar();
    return 0;
}

