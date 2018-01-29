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
			if (L->arr[i] < L->arr[i - increment]) {
				L->arr[0] = L->arr[i];
				for (j = i - increment; j > 0 && L->arr[j] > L->arr[0]; j -= increment)
					L->arr[j + increment] = L->arr[j];
				L->arr[j + increment] = L->arr[0];
			}	
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
	for (i = 2 * s; i <=m; i *= 2) {
		if (i<m&&L->arr[i] < L->arr[i + 1])
			++i;
		if (temp >= L->arr[i])
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

//归并排序    
//利用归并的思想实现排序的方法。其原理是：假设初始含有n个记录，则可以看成是n个有序的子序列，
//每个子序列的长度为1，然后两两归并，得到[n/2]个长度为2或1的有序子序列，再两两归并，
//如此重复，直至得到一个长度为n的有序序列为止，这种排序方法称为2路归并排序。    

//归并排序的递归实现  
void Merge(int SR[], int TR[], int i, int m, int n) {
	int j, k, l;
	for (j = m + 1, k = i; i <= m&&j <= n; k++) {
		//在前后两段中挑选较小的放入排序后的数组中
		if (SR[i] < SR[j])
			TR[k] = SR[i++];
		else
			TR[k] = SR[j++];
	}
	if (i <= m)//前半段有剩余
	{
		for (l = 0; l <= m - i; l++)
			TR[k + l] = SR[i+l];
	}
	if (j <= n) //后半段有剩余
	{
		for (l = 0; l<= n-j; l++)
			TR[k + l] = SR[j+l];
	}
}

void MSort(int SR[], int TR1[], int s, int t) {
	int m;
	int TR2[MAXSIZE + 1];
	if (s == t)
		TR1[s] = SR[s];
	else {
		m = (s + t) / 2;
		//将上一层的数组分成两部分,每一部分实现有序，存入TR2
		MSort(SR,TR2,s,m);
		MSort(SR,TR2,m+1,t);
		//将TR2[s..m]和TR2[m+1..t]完成有序归并到TR1
		Merge(TR2, TR1, s, m, t);
	}
}
void MergeSort(Sqlist *L) {
	MSort(L->arr, L->arr, 1, L->length);
}


//归并排序的非递归实现
//将长度为s的子序列两两归并到TR中
void MergePass(int SR[], int TR[], int s, int n) {
	int i = 1;
	int j;
	while (i <= n - 2 * s + 1) {
		Merge(SR, TR, i, i + s - 1, i + 2 * s - 1);  //调用Merge 将长度为s的子序列两两归并
		i += 2 * s;
	}
	if (i <= n - s + 1)  //归并最后两个子序列
		Merge(SR, TR, i, i + s - 1, n);
	else                      //剩下最后的单个子序列
		for (j = i; j <= n; j++)
			TR[j] = SR[j];
}

void MergeSort2(Sqlist *L) {
	int TR[MAXSIZE];
	int k = 1;
	while (k < L->length) {
		MergePass(L->arr, TR, k, L->length);
		k = 2 * k;
		MergePass(TR, L->arr, k, L->length);
		k = 2 * k;
	}
}
int main()
{
	int d[N] = { 50,10,90,30,70,40,80,60,20 };
	Sqlist L0,L1,L2,L3,L4,L5,L6;
	int i;
	for (i = 0; i < N; i++) {
		L0.arr[i + 1] = d[i];
	}
	L0.length = N;  
	L6=L5=L4=L3=L2=L1 = L0;
	printf("冒泡排序:\n");
	BubbleSort(&L0);
	print(L0);


	printf("选择排序:\n");
	SelectSort(&L1);
	print(L1);

	printf("插入排序:\n");
	InsertSort(&L2);
	print(L2);

	printf("希尔排序:\n");
	ShellSort(&L3);
	print(L3);

	printf("堆排序:\n");
	HeapSort(&L4);
	print(L4);

	printf("归并排序递归实现:\n");
	MergeSort(&L5);
	print(L5);

	printf("归并排序非递归实现:\n");
	MergeSort2(&L6);
	print(L6);

	getchar();
    return 0;
}

