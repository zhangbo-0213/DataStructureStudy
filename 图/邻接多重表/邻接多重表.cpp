// 邻接多重表.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdlib.h"
#include "stdio.h"  


#define ERROR -1
#define OK 1

typedef int Status;
typedef enum MarkedIf{unmarked,marked}MarkedIf;
typedef int VertexType;
typedef int QElemType;

typedef struct	EdgeType{
	int ivex, jvex;
	struct EdgeType *ilink, *jlink;
	MarkedIf mark;
	float weight;
}EdgeType;

typedef struct VertexNode {
	VertexType data;
	bool isVisited;
	EdgeType *firstarc;
}VertexNode;

typedef struct MultiAdjGraph {
	VertexNode *adjlist;
	int ivexNum, iedgeNum;
	int MaxVertexNum;
}MultiAdjGraph;

typedef struct QNode {
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct LinkQueue{
	QueuePtr front, rear;
}LinkQueue;

//基本操作函数

//若G中存在顶点u，则返回该顶点在无向图中的位置，否则返回-1
int LocateVex(MultiAdjGraph G, VertexType u) {
	int i;
	for (int i = 0; i < G.ivexNum; ++i) {
		if (G.adjlist[i].data==u)
			return i;
	}
	return  ERROR;
}

//采用邻接多重表存储结构，构造无向图G
Status  CreateGraph(MultiAdjGraph &G) {
	int i, j, OverInfo, IncInfo;
	VertexType first, second; //存储向EdgeType中的两个下标
	
	printf("输入无向图G的顶点数，边数，边是否含权重信息(是:1，否:0):");
	scanf_s("%d,%d,%d",&G.ivexNum,&G.iedgeNum,&OverInfo);
	G.MaxVertexNum = G.ivexNum;
	G.adjlist = new VertexNode[G.MaxVertexNum];
	printf("\n请输入%d顶点的标识号,回车结束单次输入\n",G.ivexNum);

	for (int i = 0; i < G.ivexNum; ++i) {
		scanf_s("%d",&G.adjlist[i].data);
		G.adjlist[i].firstarc = NULL;
	}

	printf("请输入由两点构成的边%d条（顶点下标由空格断开）\n",G.iedgeNum);
	for (int k = 0; k < G.iedgeNum; ++k) {
		scanf_s("%d %d%*c",&first,&second);   //*c吃掉换行符
		//判断边的两个顶点的标示符是否存在图G中
		i = LocateVex(G, first);
		j = LocateVex(G, second);
		if (i == ERROR || j == ERROR)
			return 0;
		EdgeType *pEdge = new EdgeType;
		pEdge->ivex = i;
		pEdge->jvex = j;
		pEdge->ilink = G.adjlist[i].firstarc;
		G.adjlist[i].firstarc = pEdge;
		pEdge->jlink = G.adjlist[j].firstarc;
		G.adjlist[j].firstarc = pEdge;    
		//判断权值
		if (OverInfo) {
			printf("该边是否有权值（1:有 0：无）");
			scanf_s("%d%*c",&IncInfo);
			if (IncInfo) {
				printf("请输入权值：");
				scanf_s("%d",&pEdge->weight);
			}
		}
		else {
			pEdge->weight = 0;
		}
	}
	return OK;
}

//返回v的值
VertexType GetVexValue(MultiAdjGraph G, int v) {
	if (v >= G.ivexNum || v < 0)
		return ERROR;
	return G.adjlist[v].data;
}

//对v赋新值
Status PutVex(MultiAdjGraph *G, VertexType v, VertexType value) {
	int i;
	i = LocateVex(*G, v);
	if (i)
		G->adjlist[i].data = value;
	return OK;
}

//返回第一个邻接点的序号，如果没有邻接点，返回错误
int FirstAdjVex(MultiAdjGraph G, VertexType v) {
	int i;
	i = LocateVex(G, v);
	if (i) {
		if (G.adjlist[i].firstarc) {
			if (G.adjlist[i].firstarc->ivex == i)
				return G.adjlist[i].firstarc->jvex;
			else
				return G.adjlist[i].firstarc->ivex;
		}
		else
			return ERROR;
	}
	else
		return ERROR;
}

//返回v的(相对于w的)下一个邻接定点的序号,若w是v的最后一个邻接点，则返回-1
int NextAdjVex(MultiAdjGraph G, VertexType v, VertexType w) {
	int i, j;
	EdgeType *e=NULL;
	i = LocateVex(G, v);
	j = LocateVex(G,w);    
	if (i < 0 || j < 0) {
		return ERROR;
	}
	e = G.adjlist[i].firstarc;
	while (e) {
		//邻接多重表内，顶点列表内的顶点指向的边结点内存储的下标分两种情况
		if (e->ivex == i&&e->jvex != j)
			e = e->ilink;
		else if (e->jvex == i&&e->ivex != j)
			e = e->jlink;
		else//  说明v,w已经是邻接点
			break;
	}
		if (e&&e->ivex == i&&e->jvex == j) {
			e = e->ilink;
			if (e&&e->ivex == i)
				return e->jvex;
			else if (e&&e->jvex == i)
				return e->ivex;
		}
		if (e&&e->jvex == i&&e->ivex == j) {
			e = e->jlink;
			if (e&&e->ivex == i)
				return e->jvex;
			else if (e&&e->jvex == i)
				return e->ivex;
		}

		return ERROR;
} 

//图中添加顶点，不添加与该顶点有关的边，交给InsertEdge函数处理
Status InsertVex(MultiAdjGraph *G, VertexType v) {
	if (G->MaxVertexNum == G->ivexNum)
	{
		printf("结点已满，无法添加");
		return ERROR;
	}
	if (LocateVex(*G, v) > 0) {
		printf("结点已经存在，无法添加");
		return ERROR;
	}
	G->adjlist[G->ivexNum].data = v;
	G->adjlist[G->ivexNum].firstarc = NULL;
	G->ivexNum++;
	return OK;
}     

//在G中删除边（v,w）
Status DeleteEdge(MultiAdjGraph *G, VertexType v, VertexType w) {
	int i, j;
	EdgeType *p=NULL, *q=NULL;

	i = LocateVex(*G, v);
	j = LocateVex(*G,w);
	if (i < 0 || j < 0)
		return ERROR;
	p = G->adjlist[i].firstarc;
	q = NULL;
	//假设第一条边即为待删除边
	if (p&&p->jvex == j)
		G->adjlist[i].firstarc = p->ilink;
	else if (p&&p->ivex == j)
		G->adjlist[i].firstarc = p->jlink;
	//第一条边不为待删除边，先找到待删除的边
	else {
		while (p) {
			if (p->ivex == i&&p->jvex != j) {
				q = p;
				p = p->ilink;
			}
			else if (p->jvex == i&&p->ivex != j) {
				q = p;
				p = p->jlink;
			}
			else
				break;
		}
		if (!p)
			return ERROR;
		if (p->ivex == i&&p->jvex == j) {
			if (q->ivex == i)
				q->ilink = p->ilink;
			else
				q->jlink = p->ilink;
		}
		else if (p->jvex == i&&p->ivex == j) {
			if (q->ivex == i)
				q->ilink = p->jlink;
			else
				q->jlink = p->jlink;
		}
	}

	//由另一起点开始搜索（由于邻接多重表中每一条边都有两个指针指向，所以必须将两条指针都清除）
	p = G->adjlist[j].firstarc;
	if (p->jvex == i) {    //这里没有做p是否存在的判断，是由于上一步已经将这条边找出来了，所以p必存在
		G->adjlist[j].firstarc = p->ilink;
		printf("删除的边为：%d--%d\n", G->adjlist[p->ivex].data, G->adjlist[p->jvex].data);
		delete p;  //此时p的作用已经完成
	}
	else if (p->ivex == i) {
		G->adjlist[j].firstarc = p->jlink;
		printf("删除的边为：%d--%d\n", G->adjlist[p->ivex].data, G->adjlist[p->jvex].data);
		delete p;
	}
	else {
		while (p) {
			if (p->ivex == j&&p->jvex != i) {
				q = p;
				p = p->ilink;
			}
			else if (p->jvex == j&&p->ivex != i) {
				q = p;
				p = p->jlink;
			}
			else
				break;		
		}
		if (p->ivex == j&&p->jvex == i) {
			if (q->ivex == j)
				q->ilink = p->ilink;
			else
				q->jlink = p->ilink;
			printf("删除的边为：%d--%d\n", G->adjlist[p->ivex].data, G->adjlist[p->jvex].data);
			delete p;//p任务已经完成
		}
		else if (p->jvex == j&&p->ivex == i) {
			if (q->ivex == j)
				q->ilink = p->jlink;
			else
				q->jlink = p->jlink;
			printf("删除的边为：%d--%d\n", G->adjlist[p->ivex].data, G->adjlist[p->jvex].data);
			delete p;//p任务已经完成
		}
	}
	G->iedgeNum--;
	return OK;
}     

//删除图中G的顶点v及其相关的边
Status DeletaVex(MultiAdjGraph *G, VertexType v) {
	int i,j;
	VertexType w;
	EdgeType *p=NULL;
	i = LocateVex(*G, v);
	if (i < 0)
		return ERROR;
	// 先处理相关的边
	for (j = 0; j < G->ivexNum; ++j) {
		if (j == i)
			continue;
		w = GetVexValue(*G, j);
		DeleteEdge(G, v, w);
	}
	//再将顶点覆盖
	for (j = i + 1; j < G->ivexNum; ++j) {
		G->adjlist[j - 1] = G->adjlist[j];
	}
	--G->ivexNum;
	//再将边界结点中存储的顶点下标进行更改（下标减一）
	for (j = i; j < G->ivexNum; ++j) {
		p = G->adjlist[j].firstarc;
		while (p) {
			if (p->ivex == j+1) {
				p->ivex--;
				p = p->ilink;
			}
			else {
				p->jvex--;
				p = p->jlink;
			}
		}
	}
	return OK;
}

//删除图，删除图中的顶点及相关的边，并释放顶点数组空间
Status DestroyGraph(MultiAdjGraph *G) {
	for (int i = 0; i < G->ivexNum; ++i)
		DeletaVex(G, G->adjlist[i].data);
	delete[](G->adjlist);
	return OK;
}

//搜索图中是否存在边
bool SearchEdge(MultiAdjGraph G, VertexType v, VertexType w) {
	int i, j;
	EdgeType *p=NULL;

	i = LocateVex(G, v);
	j = LocateVex(G, w);
	if (i < 0 || j < 0||i==j)
		return false;
	p = G.adjlist[i].firstarc;
	while (p) {
		if (p->ivex == i&&p->jvex == j)
			return true;
		else if (p->ivex == j&&p->jvex == i)
			return true;
		else if (p->ivex == i)
			p = p->ilink;
		else if (p->jvex == i)
			p = p->jlink;
	}
	return false;
}

Status InsertEdge(MultiAdjGraph *G,VertexType v,VertexType w) {
	int i, j;
	i = LocateVex(*G, v);
	j = LocateVex(*G,w);
	if (i < 0 || j < 0 || i == j)
		return ERROR;
	if (SearchEdge(*G, v, w)) {
		printf("该边已经存在图中");
		return ERROR;
	}
	EdgeType *p = new EdgeType;
	p->ivex = i;
	p->jvex = j;
	p->ilink = G->adjlist[i].firstarc;
	G->adjlist[i].firstarc = p;
	p->jlink = G->adjlist[j].firstarc;
	G->adjlist[j].firstarc = p;
	p->mark = unmarked;
	p->weight = 0;
	printf("\n新插入的边:%d--%d\n",G->adjlist[p->ivex].data,G->adjlist[p->jvex].data);
	G->iedgeNum++;
	return OK;
}

//寻找顶点v的邻接顶点，返回符合条件的顶点数目
int FindNextAdj(MultiAdjGraph G, VertexType v) {
	int i,j;
	EdgeType *p;
	i = LocateVex(G, v);
	if (i < 0)
		return ERROR;
	p = G.adjlist[i].firstarc;
	j = 0;
	if (p) {
		printf("顶点%d的邻接顶点为:", v);
		while (p) {
			if (p->ivex == i)
			{
				printf("%4d", G.adjlist[p->jvex].data);
				++j;
				p = p->ilink;
			}
			else {
				printf("%4d", G.adjlist[p->ivex].data);
				++j;
				p = p->jlink;
			}
		}
	}
	else
		printf("该顶点没有邻接顶点");
	return j;
}    

//设置边为未访问状态
void MarkUnVisited(MultiAdjGraph *G) {
	int i;
	EdgeType *p=NULL;
	for (i = 0; i < G->ivexNum; ++i) {
		p = G->adjlist[i].firstarc;
		while (p) {
			p->mark = unmarked;
			if (p->ivex == i)
				p = p->ilink;
			else
				p = p->jlink;
		}
	}
}

//输出图中的数据
Status ShowGraph(MultiAdjGraph G) {
	int i;
	EdgeType *p=NULL;

	MarkUnVisited(&G);
	printf("\n输出图：\n");
	printf("%d个顶点\n", G.ivexNum);
	for (i = 0; i < G.ivexNum; ++i)
		printf("%d  ",G.adjlist[i].data);
	printf("\n%d条边\n",G.iedgeNum);
	for (i = 0; i < G.ivexNum; ++i) {
		p = G.adjlist[i].firstarc;
		while (p) {
			if (p->ivex == i) {
				//做遍历输出确保该边只被输出一次
				if (p->mark == unmarked) {
					printf("%d--%d 权值：%.2f     ", G.adjlist[i].data, G.adjlist[p->jvex].data, p->weight);
					p->mark = marked;
				}
				p = p->ilink;
			}
			else {
				if (p->mark == unmarked) {
					printf("%d--%d, 权值：%.2f	     ", G.adjlist[i].data, G.adjlist[p->ivex].data, p->weight);
					p->mark = marked;
				}
				p = p->jlink;
			}
		}
		printf("\n");
	}
	return OK;
}

//深度优先搜索
void DFS(MultiAdjGraph G, int i) {
	EdgeType *e;
	e= G.adjlist[i].firstarc;
	printf("遍历的结点的值：%d\n",G.adjlist[i].data);
	G.adjlist[i].isVisited = true;
	while (e) {
		if (e->ivex == i) {
			if(!G.adjlist[e->jvex].isVisited)
				DFS(G,e->jvex);
			e = e->ilink;
		}
		else {
			if (!G.adjlist[e->ivex].isVisited)
				DFS(G,e->ivex);
			e = e->jlink;
		}
	}	
	}
Status DFSTraverse(MultiAdjGraph *G) {
	int i;
	for (i = 0; i < G->ivexNum; ++i) 
		G->adjlist[i].isVisited = false;
	for (i = 0; i < G->ivexNum; ++i)
		if(!G->adjlist[i].isVisited)
			DFS(*G,i);
	return OK;
}
int main()
{
	MultiAdjGraph *G=new MultiAdjGraph;
	VertexType v1 = 0, v2 = 0;
	int n;
	CreateGraph(*G);    
	ShowGraph(*G);      

	//修改结点的值
	printf("修改结点的值:结点原值 结点新值\n");
	scanf_s("%d %d",&v1,&v2);
	PutVex(G, v1, v2);
	ShowGraph(*G);

	//删除结点
	printf("删除节点，请输入要删除的结点的值:\n");
	scanf_s("%d",&v1);
	DeletaVex(G, v1);
	ShowGraph(*G);

	//插入新节点
	printf("\n插入新的结点，请输入节点的值:");
	scanf_s("%d",&v1);
	InsertVex(G,v1);
	printf("\n请输入与该结点相关的边数：");
	scanf_s("%d",&n);
	for (int i = 0; i < n; ++i) {
		printf("\n请输入与该结点连接的边的另一个结点的值：\n");
		scanf_s("%d", &v2);
		InsertEdge(G, v1, v2);
	}
	ShowGraph(*G);    

	printf("\n按照深度搜索的遍历结果：\n");
	DFSTraverse(G);

	getchar();
	getchar();
	getchar();
	getchar();
    return 0;
}

