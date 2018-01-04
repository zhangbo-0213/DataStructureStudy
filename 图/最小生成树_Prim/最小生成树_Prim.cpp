// ��С������_Prim.cpp : �������̨Ӧ�ó������ڵ㡣
//

//Prim�㷨��ĳһ���㿪ʼ
//�����ö��������������֮��ıߵ�Ȩֵ��������Ȩֵ����
//���ҳ�����Ȩֵ��С�ıߵĶ�Ӧ���㣬��¼�¸ö����±�
//ͬʱ����СȨֵ�ıߵ�������������ǣ������ظ�����
//����¼�Ķ��������������Ȩֵ��֮ǰ��Ȩֵ����Ƚ�
//����Ȩֵ���飬��¼�������н�С��Ȩֵ������и��½���¼�Ķ�����±�����Ӧλ�õ��±�����
//����һ�ּ����ʱ��Ȩֵ�����д����Ȩֵ��ʾ�뵱ǰȨֵ��С�ıߵĶ������ڽӹ�ϵ�Ķ����Ӧ�ıߵ�Ȩֵ��
//�±������д洢�����뵱ǰȨֵ��С�ıߵ�����һ�������ڽӵ�δ�������������㡣�����������ظ���������������ʱ�临�Ӷ�Ϊ0(n ^ 2)
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
	
	//�Ӷ���0��ʼ�����붥��0�ڽӵĶ���ıߵ�Ȩֵ����Ȩֵ���飬�������ڽӹ�ϵ�Ķ���֮��ıߵ�ȨֵΪINFINTY
	//�����±�����ȫ�����Ϊ����0���±�
	lowcost[0] = 0;
	adjvex[0] = 0;
	for (i = 1; i < G.numVex; ++i) {
		lowcost[i] = G.arc[0][i];
		adjvex[i] = 0;
	}

	//�������еĶ���
	for (i = 1; i < G.numVex; ++i) {
		min = INFINITY;
		k = 0;
		for (j = 1; j < G.numVex; ++j) {
			if (lowcost[j] != 0 && lowcost[j] < min) {
				min = lowcost[j];
				k = j;
			}
		//�ҳ�����i����������֮���Ȩֵ��С�ıߣ������¸ñ߶�Ӧ�Ķ����±�
		}
		printf("\n\nlowcost: ");
		ShowArrayValue(lowcost);
		printf("\n��ǰ����Ȩֵ��С�ıߣ�%d---%d",adjvex[k],k);
		//�ҳ��Ķ����ǣ������ظ�����
		lowcost[k] = 0;
		
		//���ҳ��Ķ����������������ӵıߵ�Ȩֵ��Ȩֵ����Ƚϣ�������С��Ȩֵ����Ȩֵ����
		//����Ȩֵ����洢��ֵΪ��֮ǰ�ҵ���Ȩֵ��С�ߵ������������ڽӵĵ�
		//Ȩֵ�и��µ�λ�����±������м�¼���ҳ��Ķ�����±�ֵ
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

