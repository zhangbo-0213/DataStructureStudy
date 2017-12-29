// 静态链表.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ctype.h"

#include "stdio.h"
#include "io.h"
#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 1000

typedef int Status;   //Status为函数返回类型，其值时函数结果状态码，如OK等
typedef char ElemType; //ElemType根据实际数据的需求而定

Status visit(ElemType c)
{
	printf("%c", c);
	return OK;
}

//定义静态链表的存储结构
typedef struct {
	ElemType data;
	int cur;  //作为游标使用
} Component,StaticLinkList[MAXSIZE];   

Status InitList(StaticLinkList space) {
	int i;
	for (i = 0; i < MAXSIZE-1; i++)
		space[i].cur = i + 1;
	space[MAXSIZE - 1].cur= 0;   //初始化的静态链表为空，最后一个元素的游标指向0
	return OK;
}

//分配静态链表空间
int Malloc_SSL(StaticLinkList space) {
	int i = space[0].cur;
	if (space[0].cur) {
		space[0].cur = space[i].cur;    //返回当前备用链表的头索引，并将备用链表的下一个元素小标给space[0].cur
	}
	return i;
}

//释放回收静态链表的空闲节点
void Free_SSL(StaticLinkList space, int i) {
	space[i].cur = space[0].cur;
	space[0].cur = i;
	//i位置空出来作为最新的空闲节点，而space[0].cur始终指向最新的空闲节点，所以先将原有的space[0].cur赋给space[i].cur，而让space[0].cur指向space[i];
}

//取得链表有意义元素长度
int ListLength(StaticLinkList space) {
	int j = 0;
	int i = space[MAXSIZE - 1].cur;  //静态链表中最后一个元素的cur始终指向第一个有元素数据的单元
	while (i) {
		j++;
		i = space[i].cur;
	}
	return j;
}

//在链表中插入新数据元素
Status ListInsert(StaticLinkList space, int i, ElemType e) {
	int j, k, l;
	j = MAXSIZE - 1;
	if (i<1 || i>ListLength(space) + 1)
		return ERROR;
	k = Malloc_SSL(space);
	if (k) {
		space[k].data = e;
		for (l = 1; l <= i - 1; l++)
			j = space[j].cur;
		space[k].cur = space[j].cur;
		space[j].cur = k;
		return OK;
	}
	return ERROR;
}

//删除静态链表中的数据元素
	Status ListDelete(StaticLinkList space, int i) {
		int j, k;
		if (i<1 || i>ListLength(space) - 1)
			return ERROR;
		j = MAXSIZE - 1;
		for (k = 1; k <= i - 1; k++) 
			j = space[j].cur;
		k = space[j].cur;
		space[j].cur = space[k].cur;
		Free_SSL(space, k);
		return OK;
	}

//输出格式化函数
	Status ListTraverse(StaticLinkList space) {
		int j = 0;
		int i = space[MAXSIZE - 1].cur;
		while (i) {
			visit(space[i].data);
			i = space[i].cur;
			j++;
		}
		return j;
		printf("\n");
		return OK;
	}
int main()
{
	StaticLinkList L;
	Status i;
	i = InitList(L);
	printf("初始化后：L.length=%d\n",ListLength(L));

	i = ListInsert(L, 1, 'H');
	i = ListInsert(L, 2, 'E');
	i = ListInsert(L, 3, 'L');
	i = ListInsert(L, 4, 'L');
	i = ListInsert(L, 5, 'O');

	printf("\n在L的表头依次插入OLLEH后：\nL.data=");
	ListTraverse(L);

	i = ListInsert(L, 3, 'W');
	printf("\n在E和L之间插入W后：\n L.data=");
	ListTraverse(L);

	i = ListDelete(L, 1);
	printf("\n在删除H后：\nL.data=");
	ListTraverse(L);

	printf("\n");
	printf("按任意键继续……");
	getchar();
    return 0;
}

