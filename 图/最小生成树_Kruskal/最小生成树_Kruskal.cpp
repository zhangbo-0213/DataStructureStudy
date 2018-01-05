// ��С������_Kruskal.cpp : �������̨Ӧ�ó������ڵ㡣
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

	for (i = 0; i < G->numVertexes; i++)/* ��ʼ��ͼ */
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

//������
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

//��Ȩֵ��������
void Sort(Edge edges[],MGraph *G) {
	int i, j;
	for (i = 0; i < G->numEdges; i++) {
		for (j = i + 1; j < G->numEdges; j++) {
			if (edges[i].weight > edges[j].weight) {
				Swapn(edges, i, j);
			}
		}
	}
	printf("Ȩֵ������ɺ�\n");
	for (i = 0; i < G->numEdges; i++) {
		printf("(%d--%d): %d\n",edges[i].begin,edges[i].end,edges[i].weight);
	}
}

//����ͨ·������±�,�ú�����ʱ�临�Ӷ� loge   
int Find(int *parent, int i) {
	while (parent[i] > 0)
		i = parent[i];
	return i;
}

void ShowParentArray(int *parent,MGraph G) {
	int i=0;
	printf("\nparent�� ");
	while (i < G.numVertexes) {
		printf("%d ", parent[i]);
		i++;
	}
	printf("\n");
}


//��С������Kruskal�㷨
//Kruskal�㷨�ӱ߿�ʼ������ѡ��Ȩֵ��С�ı���������С���������Ƚ���Ҫ��������          

//-���߰���Ȩֵ�������򣬴�Ȩֵ��С�ı߿�ʼ
//- ��鱻ѡ��ı��Ƿ񹹳ɻ�·����û�й��ɻ�·�����¼�ߵĶ����±꣬�������������
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
		//�ж��Ƿ񹹳��˻�·�����n=m�����γ��˻�·
		n = Find(parent,edges[i].begin);
		m = Find(parent,edges[i].end);
		if (n != m) {     
			parent[n] = m;
			printf("n=%d, m=%d\n",n,m);
			printf("ѡ��ıߣ�(%d--%d)  Ȩֵ:%d",edges[i].begin,edges[i].end,edges[i].weight);
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

