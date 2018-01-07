// 最短路径_Floyd.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "io.h"
#include "time.h"
#include "math.h"

#define ERROR -1
#define OK 1

#define MAXVEX 20
#define MAXSIZE 20  
#define INFINITY 65535

typedef struct {
	int arc[MAXVEX][MAXVEX];
	int numVertex, numEdges;
}MGraph;

typedef int Patharc[MAXVEX][MAXVEX];
typedef int ShortPathSum[MAXVEX][MAXVEX];

void CreateMGraph(MGraph *G) {
	int i, j;
	G->numVertex = 9;
	G->numEdges = 16;

	for (i = 0; i < G->numVertex; i++) {
		for (j = 0; j < G->numVertex; j++) {
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
		for (j = i + 1; j < G->numVertex; j++) {
			G->arc[j][i] = G->arc[i][j];
		}
	}
}

void ShortestPath_Floyd(MGraph G,Patharc *P,ShortPathSum *D) {
	int i, j, k;
	for (i = 0; i < G.numVertex; i++) {
		for (j = 0; j < G.numVertex; j++) {
			(*D)[i][j] = G.arc[i][j];  //初始化路径和数组
			(*P)[i][j] = j;               //初始化前驱下标数组
		}
	}

	for (k = 0; k < G.numVertex; k++) {//中间点遍历
		for (i = 0; i < G.numVertex; i++) {//起始点遍历
			for (j = 0; j < G.numVertex; j++) { //结束点遍历
				if ((*D)[i][k] + (*D)[k][j] < (*D)[i][j]) {
					(*D)[i][j] = (*D)[i][k] + (*D)[k][j];
					(*P)[i][j] = (*P)[i][k];
				}
			}
		}
	}  
}

int main()
{
	MGraph G;
	CreateMGraph(&G);
	Patharc P;
	ShortPathSum D;

	ShortestPath_Floyd(G, &P, &D);

	int i, j, k;
	printf("最短路径如下：\n");
	for (i = 0; i < G.numVertex; i++) {
		for (j = i + 1; j < G.numVertex; j++) {
			printf("%d---%d，权值: %d\n", i, j, D[i][j]);
			printf("路径为：%d",i);  //打印起点
			k = P[i][j];
			while (k != j) {
				printf("--%d",k);
				k = P[k][j];
			}
			printf("--%d\n",j);//打印终点
		}
		printf("\n");
	}

	printf("最短路径数组D：\n");
	for (i = 0; i < G.numVertex; i++) {
		for (j = 0; j < G.numVertex; j++) {
			printf("%d\t",D[i][j]);
		}
		printf("\n");
	}


	printf("前驱下标数组P：\n");
	for (i = 0; i < G.numVertex; i++) {
		for (j = 0; j < G.numVertex; j++) {
			printf("%d  ", P[i][j]);
		}
		printf("\n");
	}
	getchar();
    return 0;
}

