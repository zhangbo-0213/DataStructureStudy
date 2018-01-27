// 冒泡排序.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdlib.h"
#include "io.h"

#define TRUE 1
#define FALSE 0
#define ERROR -1
#define OK 1

#define N 9
#define MAXSIZE 100
typedef int Status;

typedef struct {
	int arr[MAXSIZE+1];
	int length;
}Sqlist;

void Swap(Sqlist *L, int i, int j) {
	int temp = L->arr[i];
	L->arr[i] = L->arr[j];
	L->arr[j] = temp;
}

void print(Sqlist L) {
	int i;
	for (i = 1; i <=L.length; i++)
		printf("%d  ",L.arr[i]);
	printf("\n");
}

//对顺序表做冒泡排序
void BubbleSort(Sqlist *L) {
	int i, j;
	Status flag = TRUE;
	for (i = 1; i < L->length&&flag; i++) {
		flag = FALSE;
		for (j = L->length -1; j >= i; j--) {
			if (L->arr[j] > L->arr[j + 1]) {
				Swap(L, j, j + 1);
				flag = TRUE;
			}
		}
	}
}

//对顺序表做选择排序
void SelectSort(Sqlist *L) {
	int i, j, min;
	for (i = 1; i < L->length; i++) {   //每次循环找出最小的
		min = i;
		for (j = i + 1; j <= L->length; j++)
			if (L->arr[min] > L->arr[j])
				min = j;
		if (min != i)  //如果在后续的记录中找到了，就交换
			Swap(L, i, min);
	}
}   

//插入排序    
void InsertSort(Sqlist *L) {
	int i, j;
	for (i = 2; i <= L->length; i++) {
		if (L->arr[i] < L->arr[i - 1])  //出现需要插入到前面的记录
		{
			L->arr[0] = L->arr[i];
			for (j = i - 1; L->arr[j] > L->arr[0]; j--) {    //L->arr[j] > L->arr[0] 判断挪位的终止位置
				L->arr[j + 1] = L->arr[j];    //依次后挪腾位置
			}
			L->arr[j + 1] = L->arr[0];
		}
	}
}         
//希尔排序      
//希尔排序主要是将待排序序列分块完成大致有序，再将块缩小逐步完成排序
//希尔排序的关键不是随便分组后各自排序，而是在分组时就应经在排序，将相隔的某个增量的记录组成一个子序列
//实现跳跃式移动，使得排序效率增高
void  ShellSort(Sqlist *L) {
	int i, j;
	int increment = L->length;
	do {
		increment = increment / 3 + 1;
		for (i = increment + 1; i <= L->length; i++) {
			if (L->arr[i] < L->arr[i - increment])
				L->arr[0] = L->arr[i];
			for (j = i - increment; j > 0 && L->arr[j] > L->arr[0]; j -= increment)
				L->arr[j + increment] = L->arr[j];
			L->arr[j + increment] = L->arr[0];
		}
	} while (increment > 1);
}

//堆排序  
//将待排序的序列构造成一个大顶堆。整个序列的最大值就是堆顶的根结点。
//将其移走（将其与对数组的末尾元素交换，此时末尾元素就是最大值），
//然后将剩余的n-1个序列重新构造成一个堆，这样就会得到n个元素中次大值，反复进行，直到得到最终有序序列。         
void HeapAdjust(Sqlist *L, int s, int m) {
	int temp = L->arr[s];
	int i;
	for (i = 2 * s; i < m; i *= 2) {
		if (L->arr[i] < L->arr[i + 1])
			++i;
		if (temp > L->arr[i])
			break;
		L->arr[s] = L->arr[i];
		s = i;
	}
	L->arr[s] = temp;
}

void HeapSort(Sqlist *L) {
	int i;
	for (i = L->length / 2; i > 0; i--)  //从有孩子的结点自下而上进行构建
		HeapAdjust(L, i, L->length);

	for (i = L->length; i > 1; i--) {
		Swap(L, 1, i);
		HeapAdjust(L, 1, i - 1);
	}
}

int main()
{
	int d[N] = { 50,10,90,30,70,40,80,60,20 };
	Sqlist L0,L1,L2,L3,L4;
	int i;
	for (i = 0; i < N; i++) {
		L0.arr[i + 1] = d[i];
	}
	L0.length = N;  
	L4=L3=L2=L1 = L0;
	printf("冒泡排序:\n");
	BubbleSort(&L0);
	print(L0);


	printf("选择排序:\n");
	BubbleSort(&L1);
	print(L1);

	printf("插入排序:\n");
	BubbleSort(&L2);
	print(L2);

	printf("希尔排序:\n");
	BubbleSort(&L3);
	print(L3);

	printf("堆排序:\n");
	BubbleSort(&L4);
	print(L4);
	getchar();
    return 0;
}

