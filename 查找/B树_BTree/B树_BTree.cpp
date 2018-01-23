// B树_BTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdlib.h"
#include "io.h"

#define OK 1
#define ERROR -1
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100

#define m  3    //B树的阶
#define N  17  //元素数据个数
#define MAX 5 //字符串最大长度

typedef int Status;

typedef struct BTNode {
	int keynum; //节点中关键字个数
	struct BTNode *parent; //指向双亲的指针
	struct Node {
		int key; //记录关键字
		int recptr; //
		BTNode *ptr;//指向子树的指针
	}node[m+1]; //第一个节点不记录关键字和recptr，记录指向子树的指针
}BTNode,*BTree;

//定义查询结果结构体
typedef struct Result {
	int tag;  //记录查询结果，成功为1，失败为0
	int i;  //在节点中的关键字序号
	BTNode *pt; //记录查询到的结点指针
};
 
//查询关键字在某一个节点中的位置，返回位置序号
int Search(BTree p, int K) {
	int i = 0, j;
	for (j = 1; j <= p->keynum; j++)
		if (p->node[j].key <= K)
			i = j;
	return i;
}

//在M阶的B树上查找关键字，返回结果(tag,i,pt)
//如果查获成功，tag=1,关键字在pt所指节点的第i个元素
//如果查找失败，tag=0,关键字在pt所指节点的第i个和第i+1个元素之间
Result SearchBTree(BTree T, int K) {
	BTree p = T, q = NULL;   //查找过程中，q指向双亲结点;
	Result r;
	int found = false;
	int i = 0;
	while (p && !found) {
		i = Search(p, K);
		if (i > 0 && p->node[i].key == K)
			found = TRUE;
		else {
			q = p;
			p = p->node[i].ptr;
		}
	}
	r.i = i;
	if (found) {
		r.tag = 1;
		r.pt = p;
	}
	else {
		r.tag = 0;
		r.pt = q;
	}
	return r;
}

//将关键字key，子树指针插入到p的[i+1]节点处
void Insert(BTree *p, int i, int key, BTree ap) {
	int j = 0;
	for (j = (*p)->keynum; j > i; j--) //空出i+1结点的位置
		(*p)->node[j + 1] = (*p)->node[j];
	(*p)->node[i + 1].key = key;
	(*p)->node[i + 1].recptr = key;
	(*p)->node[i + 1].ptr = ap;
	(*p)->keynum++;
}  

//将结点q分裂为两个节点，前一半保留，后一半移入新生结点ap中
void Split(BTree *q, BTree *ap) {
	int i, s = (m + 1) / 2;
	(*ap) = (BTree)malloc(sizeof(BTNode));  //生成新的结点
	(*ap)->node[0].ptr = (*q)->node[s].ptr;
	for (i = s + 1; i <= m; i++) {
		(*ap)->node[i - s] = (*q)->node[i];
		if ((*ap)->node[i - s].ptr)
			(*ap)->node[i - s].ptr->parent = *ap;
	}
	(*ap)->keynum = m - s;
	(*ap)->parent = (*q)->parent;
	(*q)->keynum = s - 1;
}

//生成新的根结点，包含信息(T,r,ap)，原T和ap为其子树指针
void NewRoot(BTree *T, int key, BTree ap) {
	printf("进行了一次生根操作\n");
	BTree p;
	p=(BTree)malloc(sizeof(BTNode));
	p->node[0].ptr=*T;
	*T=p;
	if((*T)->node[0].ptr)
		(*T)->node[0].ptr->parent=*T;
	(*T)->parent=NULL;
	(*T)->keynum=1;
	(*T)->node[1].key=key;
	(*T)->node[1].recptr=key;
	(*T)->node[1].ptr=ap;
	if((*T)->node[1].ptr)
		(*T)->node[1].ptr->parent=*T;
}   

//在m阶的B树T上结点*q的key[i]与key[i+1]之间插入关键字K的指针r
//如果结点过大，沿双亲链进行结点分裂调整，使T仍是m阶B树
void InsertBTree(BTree *T,int key,BTree q,int i) {
	BTree ap = NULL;
	Status finished = FALSE;
	int s;
	int rx;
	rx = key;
	while (q && !finished) {
		Insert(&q, i, rx, ap);
		if (q->keynum < m)
			finished = TRUE;
		else {  //分裂结点
			printf("\n结点分裂");
			s = (m + 1) / 2;
			rx = q->node[s].recptr;
			Split(&q, &ap);
			q = q->parent;
			if (q)
				i = Search(q, key);
		}
	}
	if (!finished)
		NewRoot(T,rx,ap);
	printf("\n完成插入，插入的结点地址为：%d",ap);
}

void print(BTNode c, int i)
{
	printf("(%d)", c.node[i].key);
}
int main()
{
	int r[N] = { 22,16,41,58,8,11,12,16,17,22,23,31,41,52,58,59,61 };
	BTree T = NULL;
	Result s;
	int i;
	for (i = 0; i < N; i++)
	{
		s = SearchBTree(T, r[i]);
		if (!s.tag)
			InsertBTree(&T, r[i], s.pt, s.i);
	}
	printf("\n请输入待查找记录的关键字: ");
	scanf_s("%d", &i);
	s = SearchBTree(T, i);
	if (s.tag)
		print(*(s.pt), s.i);
	else
		printf("没找到");
	printf("\n");

	getchar();
	getchar();
	return 0;
}
