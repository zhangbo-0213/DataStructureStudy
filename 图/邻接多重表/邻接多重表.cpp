// �ڽӶ��ر�.cpp : �������̨Ӧ�ó������ڵ㡣
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

//������������

//��G�д��ڶ���u���򷵻ظö���������ͼ�е�λ�ã����򷵻�-1
int LocateVex(MultiAdjGraph G, VertexType u) {
	int i;
	for (int i = 0; i < G.ivexNum; ++i) {
		if (G.adjlist[i].data==u)
			return i;
	}
	return  ERROR;
}

//�����ڽӶ��ر�洢�ṹ����������ͼG
Status  CreateGraph(MultiAdjGraph &G) {
	int i, j, OverInfo, IncInfo;
	VertexType first, second; //�洢��EdgeType�е������±�
	
	printf("��������ͼG�Ķ����������������Ƿ�Ȩ����Ϣ(��:1����:0):");
	scanf_s("%d,%d,%d",&G.ivexNum,&G.iedgeNum,&OverInfo);
	G.MaxVertexNum = G.ivexNum;
	G.adjlist = new VertexNode[G.MaxVertexNum];
	printf("\n������%d����ı�ʶ��,�س�������������\n",G.ivexNum);

	for (int i = 0; i < G.ivexNum; ++i) {
		scanf_s("%d",&G.adjlist[i].data);
		G.adjlist[i].firstarc = NULL;
	}

	printf("�����������㹹�ɵı�%d���������±��ɿո�Ͽ���\n",G.iedgeNum);
	for (int k = 0; k < G.iedgeNum; ++k) {
		scanf_s("%d %d%*c",&first,&second);   //*c�Ե����з�
		//�жϱߵ���������ı�ʾ���Ƿ����ͼG��
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
		//�ж�Ȩֵ
		if (OverInfo) {
			printf("�ñ��Ƿ���Ȩֵ��1:�� 0���ޣ�");
			scanf_s("%d%*c",&IncInfo);
			if (IncInfo) {
				printf("������Ȩֵ��");
				scanf_s("%d",&pEdge->weight);
			}
		}
		else {
			pEdge->weight = 0;
		}
	}
	return OK;
}

//����v��ֵ
VertexType GetVexValue(MultiAdjGraph G, int v) {
	if (v >= G.ivexNum || v < 0)
		return ERROR;
	return G.adjlist[v].data;
}

//��v����ֵ
Status PutVex(MultiAdjGraph *G, VertexType v, VertexType value) {
	int i;
	i = LocateVex(*G, v);
	if (i)
		G->adjlist[i].data = value;
	return OK;
}

//���ص�һ���ڽӵ����ţ����û���ڽӵ㣬���ش���
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

//����v��(�����w��)��һ���ڽӶ�������,��w��v�����һ���ڽӵ㣬�򷵻�-1
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
		//�ڽӶ��ر��ڣ������б��ڵĶ���ָ��ı߽���ڴ洢���±���������
		if (e->ivex == i&&e->jvex != j)
			e = e->ilink;
		else if (e->jvex == i&&e->ivex != j)
			e = e->jlink;
		else//  ˵��v,w�Ѿ����ڽӵ�
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

//ͼ����Ӷ��㣬�������ö����йصıߣ�����InsertEdge��������
Status InsertVex(MultiAdjGraph *G, VertexType v) {
	if (G->MaxVertexNum == G->ivexNum)
	{
		printf("����������޷����");
		return ERROR;
	}
	if (LocateVex(*G, v) > 0) {
		printf("����Ѿ����ڣ��޷����");
		return ERROR;
	}
	G->adjlist[G->ivexNum].data = v;
	G->adjlist[G->ivexNum].firstarc = NULL;
	G->ivexNum++;
	return OK;
}     

//��G��ɾ���ߣ�v,w��
Status DeleteEdge(MultiAdjGraph *G, VertexType v, VertexType w) {
	int i, j;
	EdgeType *p=NULL, *q=NULL;

	i = LocateVex(*G, v);
	j = LocateVex(*G,w);
	if (i < 0 || j < 0)
		return ERROR;
	p = G->adjlist[i].firstarc;
	q = NULL;
	//�����һ���߼�Ϊ��ɾ����
	if (p&&p->jvex == j)
		G->adjlist[i].firstarc = p->ilink;
	else if (p&&p->ivex == j)
		G->adjlist[i].firstarc = p->jlink;
	//��һ���߲�Ϊ��ɾ���ߣ����ҵ���ɾ���ı�
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

	//����һ��㿪ʼ�����������ڽӶ��ر���ÿһ���߶�������ָ��ָ�����Ա��뽫����ָ�붼�����
	p = G->adjlist[j].firstarc;
	if (p->jvex == i) {    //����û����p�Ƿ���ڵ��жϣ���������һ���Ѿ����������ҳ����ˣ�����p�ش���
		G->adjlist[j].firstarc = p->ilink;
		printf("ɾ���ı�Ϊ��%d--%d\n", G->adjlist[p->ivex].data, G->adjlist[p->jvex].data);
		delete p;  //��ʱp�������Ѿ����
	}
	else if (p->ivex == i) {
		G->adjlist[j].firstarc = p->jlink;
		printf("ɾ���ı�Ϊ��%d--%d\n", G->adjlist[p->ivex].data, G->adjlist[p->jvex].data);
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
			printf("ɾ���ı�Ϊ��%d--%d\n", G->adjlist[p->ivex].data, G->adjlist[p->jvex].data);
			delete p;//p�����Ѿ����
		}
		else if (p->jvex == j&&p->ivex == i) {
			if (q->ivex == j)
				q->ilink = p->jlink;
			else
				q->jlink = p->jlink;
			printf("ɾ���ı�Ϊ��%d--%d\n", G->adjlist[p->ivex].data, G->adjlist[p->jvex].data);
			delete p;//p�����Ѿ����
		}
	}
	G->iedgeNum--;
	return OK;
}     

//ɾ��ͼ��G�Ķ���v������صı�
Status DeletaVex(MultiAdjGraph *G, VertexType v) {
	int i,j;
	VertexType w;
	EdgeType *p=NULL;
	i = LocateVex(*G, v);
	if (i < 0)
		return ERROR;
	// �ȴ�����صı�
	for (j = 0; j < G->ivexNum; ++j) {
		if (j == i)
			continue;
		w = GetVexValue(*G, j);
		DeleteEdge(G, v, w);
	}
	//�ٽ����㸲��
	for (j = i + 1; j < G->ivexNum; ++j) {
		G->adjlist[j - 1] = G->adjlist[j];
	}
	--G->ivexNum;
	//�ٽ��߽����д洢�Ķ����±���и��ģ��±��һ��
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

//ɾ��ͼ��ɾ��ͼ�еĶ��㼰��صıߣ����ͷŶ�������ռ�
Status DestroyGraph(MultiAdjGraph *G) {
	for (int i = 0; i < G->ivexNum; ++i)
		DeletaVex(G, G->adjlist[i].data);
	delete[](G->adjlist);
	return OK;
}

//����ͼ���Ƿ���ڱ�
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
		printf("�ñ��Ѿ�����ͼ��");
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
	printf("\n�²���ı�:%d--%d\n",G->adjlist[p->ivex].data,G->adjlist[p->jvex].data);
	G->iedgeNum++;
	return OK;
}

//Ѱ�Ҷ���v���ڽӶ��㣬���ط��������Ķ�����Ŀ
int FindNextAdj(MultiAdjGraph G, VertexType v) {
	int i,j;
	EdgeType *p;
	i = LocateVex(G, v);
	if (i < 0)
		return ERROR;
	p = G.adjlist[i].firstarc;
	j = 0;
	if (p) {
		printf("����%d���ڽӶ���Ϊ:", v);
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
		printf("�ö���û���ڽӶ���");
	return j;
}    

//���ñ�Ϊδ����״̬
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

//���ͼ�е�����
Status ShowGraph(MultiAdjGraph G) {
	int i;
	EdgeType *p=NULL;

	MarkUnVisited(&G);
	printf("\n���ͼ��\n");
	printf("%d������\n", G.ivexNum);
	for (i = 0; i < G.ivexNum; ++i)
		printf("%d  ",G.adjlist[i].data);
	printf("\n%d����\n",G.iedgeNum);
	for (i = 0; i < G.ivexNum; ++i) {
		p = G.adjlist[i].firstarc;
		while (p) {
			if (p->ivex == i) {
				//���������ȷ���ñ�ֻ�����һ��
				if (p->mark == unmarked) {
					printf("%d--%d Ȩֵ��%.2f     ", G.adjlist[i].data, G.adjlist[p->jvex].data, p->weight);
					p->mark = marked;
				}
				p = p->ilink;
			}
			else {
				if (p->mark == unmarked) {
					printf("%d--%d, Ȩֵ��%.2f	     ", G.adjlist[i].data, G.adjlist[p->ivex].data, p->weight);
					p->mark = marked;
				}
				p = p->jlink;
			}
		}
		printf("\n");
	}
	return OK;
}

//�����������
void DFS(MultiAdjGraph G, int i) {
	EdgeType *e;
	e= G.adjlist[i].firstarc;
	printf("�����Ľ���ֵ��%d\n",G.adjlist[i].data);
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

	//�޸Ľ���ֵ
	printf("�޸Ľ���ֵ:���ԭֵ �����ֵ\n");
	scanf_s("%d %d",&v1,&v2);
	PutVex(G, v1, v2);
	ShowGraph(*G);

	//ɾ�����
	printf("ɾ���ڵ㣬������Ҫɾ���Ľ���ֵ:\n");
	scanf_s("%d",&v1);
	DeletaVex(G, v1);
	ShowGraph(*G);

	//�����½ڵ�
	printf("\n�����µĽ�㣬������ڵ��ֵ:");
	scanf_s("%d",&v1);
	InsertVex(G,v1);
	printf("\n��������ý����صı�����");
	scanf_s("%d",&n);
	for (int i = 0; i < n; ++i) {
		printf("\n��������ý�����ӵıߵ���һ������ֵ��\n");
		scanf_s("%d", &v2);
		InsertEdge(G, v1, v2);
	}
	ShowGraph(*G);    

	printf("\n������������ı��������\n");
	DFSTraverse(G);

	getchar();
	getchar();
	getchar();
	getchar();
    return 0;
}

