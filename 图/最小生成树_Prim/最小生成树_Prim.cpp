// 最小生成树_Prim.cpp : 定义控制台应用程序的入口点。
//

//Prim算法从某一顶点开始
//遍历该顶点与其他顶点的之间的边的权值，并存入权值数组
//并找出其中权值最小的边的对应顶点，记录下该顶点下标
//同时将最小权值的边的两个顶点做标记，避免重复检索
//将记录的顶点与其他顶点的权值与之前的权值数组比较
//更新权值数组，记录下两者中较小的权值，如果有更新将记录的顶点的下标存入对应位置的下标数组
//这样一轮检测完时，权值数组中储存的权值表示与当前权值最小的边的顶点有邻接关系的顶点对应的边的权值，
//下标数组中存储的是与当前权值最小的边的其中一个顶点邻接的未检索的其他顶点。对其他顶点重复进行上述操作，时间复杂度为0(n ^ 2)
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
	
	//从顶点0开始，将与顶点0邻接的顶点的边的权值存入权值数组，不存在邻接关系的顶点之间的边的权值为INFINTY
	//顶点下标数组全部标记为顶点0的下标
	lowcost[0] = 0;
	adjvex[0] = 0;
	for (i = 1; i < G.numVex; ++i) {
		lowcost[i] = G.arc[0][i];
		adjvex[i] = 0;
	}

	//遍历所有的顶点
	for (i = 1; i < G.numVex; ++i) {
		min = INFINITY;
		k = 0;
		for (j = 1; j < G.numVex; ++j) {
			if (lowcost[j] != 0 && lowcost[j] < min) {
				min = lowcost[j];
				k = j;
			}
		//找出顶点i与其他顶点之间的权值最小的边，并记下该边对应的顶点下标
		}
		printf("\n\nlowcost: ");
		ShowArrayValue(lowcost);
		printf("\n当前顶点权值最小的边：%d---%d",adjvex[k],k);
		//找出的顶点标记，避免重复检索
		lowcost[k] = 0;
		
		//将找出的顶点与其他顶点连接的边的权值与权值数组比较，并将较小的权值存入权值数组
		//这样权值数组存储的值为与之前找到的权值最小边的两个顶点相邻接的点
		//权值有更新的位置在下标数组中记录下找出的顶点的下标值
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

