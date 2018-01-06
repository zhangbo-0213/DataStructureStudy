// 最短路径_Dijkstra.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "io.h"
#include "time.h"
#include "math.h"

#define OK 1
#define ERROR -1

#define INFINITY 65535
#define MAXSIZE 20
#define MAXVEX 20

typedef struct {
	int arc[MAXVEX][MAXVEX];
	int numVertex, numEdges;
}MGraph;

typedef int ShortPathSum[MAXVEX]; //存储到各顶点的最小路径的权值和
typedef int Patharc[MAXSIZE]; //存储对应路径的前驱下标

void ShowArrayValue(int *P,MGraph G) {
	int i = 0;
	while (i < G.numVertex) {
		printf("%d  ", P[i]);
		i++;
	}
}

void CreatGraph(MGraph *G) {
	int i,j;
	G->numVertex = 9;
	G->numEdges = 16;
	for (int i = 0; i < G->numVertex; ++i) {
		for (j = 0; j < G->numVertex; ++j) {
			if (i == j)
				G->arc[i][j] = 0;
			else
				G->arc[i][j] = G->arc[j][i] = INFINITY;
		}
	}
	G->arc[0][1] = 1;
	G->arc[0][2] = 5;
	G->arc[1][2] = 3;
	G->arc[1][3] = 7;
	G->arc[1][4] = 5;

	G->arc[2][4] = 1;
	G->arc[2][5] = 7;
	G->arc[3][4] = 2;
	G->arc[3][6] = 3;
	G->arc[4][5] = 3;

	G->arc[4][6] = 6;
	G->arc[4][7] = 9;
	G->arc[5][7] = 5;
	G->arc[6][7] = 2;
	G->arc[6][8] = 7;

	G->arc[7][8] = 4;

	for (i = 0; i < G->numVertex; i++) {
		for (j = i; j < G->numVertex; j++) {
			G->arc[j][i] = G->arc[i][j] ;
		}
	}
}

void ShortestPath_Dijkstra(MGraph G,int v0,Patharc *P,ShortPathSum *D) {
	int i,j,k,min;
	int final[MAXVEX];  //用来记录是否确定到对应顶点的最短路径;
	for (i = 0; i < G.numVertex; ++i) {
		final[i] = 0;
		(*P)[i] = 0;
		(*D)[i] = G.arc[v0][i];
	}

	final[v0] = 1;  //v0到v0点自身不需要路径
	(*D)[v0] = 0;  //自身到自身点的路径和为0

	printf("\n final: ");
	ShowArrayValue(final, G);
	printf("\n P: ");
	ShowArrayValue(*P, G);
	printf("\n D: ");
	ShowArrayValue(*D, G);

	for (i = 1; i < G.numVertex; i++) {
		min = INFINITY;
		for (j = 0; j < G.numVertex; j++) {
			if (!final[j] &&  (*D)[j]<min) {
				min = (*D)[j];
				k = j;
			}
		}
		final[k] = 1; //找到离v0路径最短的边
		printf("\nmin:%d\n",min);
		//查看从k点出发的路径中是否有比之前已经记录的到某一点的路径更短的路径
		for (j= 0; j < G.numVertex; j++) {
			//如果找到这条更短的路径就更新更新路径权值数组和记录路径前驱的数组
			if (!final[j] && min+G.arc[k][j]<(*D)[j]) {
				(*D)[j] =min+ G.arc[k][j];
				(*P)[j] = k;
			}
		}
		ShowArrayValue(final, G);
		printf("\n P: ");
		ShowArrayValue(*P, G);
		printf("\n D: ");
		ShowArrayValue(*D, G);
	}
	
}

int main()
{
	MGraph G;
	CreatGraph(&G);
	Patharc P[MAXVEX];
	ShortPathSum D[MAXVEX];
	ShortestPath_Dijkstra(G,0,P,D);
	getchar();
    return 0;
}

