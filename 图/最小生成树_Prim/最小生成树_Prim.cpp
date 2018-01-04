// 最小生成树_Prim.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "io.h"
#include "math.h"
#include "time.h"

#define OK 1
#define ERROR -1
#define TRUE 1
#define FALSE 0

#define MAXEDGE 20
#define MAXVEX 20
#define INFINITY 65535

typedef int Status;

typedef struct {
	int arc[MAXVEX][MAXVEX];
	int numVex, numEdge;
}MGraph;

void CreatMGRaph(MGraph *G) {
	int i, j;
	G->numVex = 9;
	G->numEdge = 15;

	for (i = 0; i < G->numVex; ++i) {
		for (j = 0; j < G->numVex; ++j) {
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

	for (i = 0; i < G->numVex; i++)
	{
		for (j = i; j < G->numVex; j++)
		{
			G->arc[j][i] = G->arc[i][j];
		}
	}
}

void ShowArrayValue(int *arrayname) {
	int i = 0;
	while (i<9) {
		printf("%d ", arrayname[i]);
		i++;
	}
}

void MiniSpanTree(MGraph G) {
	int lowcost[MAXVEX];
	int adjvex[MAXVEX];

	int min, i, j, k;
	
	lowcost[0] = 0;
	adjvex[0] = 0;
	for (i = 1; i < G.numVex; ++i) {
		lowcost[i] = G.arc[0][i];
		adjvex[i] = 0;
	}
	for (i = 1; i < G.numVex; ++i) {
		min = INFINITY;
		k = 0;
		for (j = 1; j < G.numVex; ++j) {
			if (lowcost[j] != 0 && lowcost[j] < min) {
				min = lowcost[j];
				k = j;
			}
		}
		printf("\n\nlowcost: ");
		ShowArrayValue(lowcost);
		printf("\n当前顶点权值最小的边：%d---%d",adjvex[k],k);
	
		lowcost[k] = 0;
		for (j = 1; j < G.numVex; ++j) {
			if (lowcost[j] != 0 && G.arc[k][j] < lowcost[j]) {
				lowcost[j] = G.arc[k][j];
				adjvex[j] = k;
			}
		}
		printf("\nlowcost: ");
		ShowArrayValue(lowcost);
		printf("\nadjvex: ");
		ShowArrayValue(adjvex);
	}
}



int main()
{
	MGraph G;
	CreatMGRaph(&G);
	MiniSpanTree(G);

	getchar();

    return 0;
}

