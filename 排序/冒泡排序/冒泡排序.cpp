// ð������.cpp : �������̨Ӧ�ó������ڵ㡣
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

//��˳�����ð������
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

//��˳�����ѡ������
void SelectSort(Sqlist *L) {
	int i, j, min;
	for (i = 1; i < L->length; i++) {   //ÿ��ѭ���ҳ���С��
		min = i;
		for (j = i + 1; j <= L->length; j++)
			if (L->arr[min] > L->arr[j])
				min = j;
		if (min != i)  //����ں����ļ�¼���ҵ��ˣ��ͽ���
			Swap(L, i, min);
	}
}   

//��������    
void InsertSort(Sqlist *L) {
	int i, j;
	for (i = 2; i <= L->length; i++) {
		if (L->arr[i] < L->arr[i - 1])  //������Ҫ���뵽ǰ��ļ�¼
		{
			L->arr[0] = L->arr[i];
			for (j = i - 1; L->arr[j] > L->arr[0]; j--) {    //L->arr[j] > L->arr[0] �ж�Ųλ����ֹλ��
				L->arr[j + 1] = L->arr[j];    //���κ�Ų��λ��
			}
			L->arr[j + 1] = L->arr[0];
		}
	}
}         
//ϣ������      
//ϣ��������Ҫ�ǽ����������зֿ���ɴ��������ٽ�����С���������
//ϣ������Ĺؼ������������������򣬶����ڷ���ʱ��Ӧ�������򣬽������ĳ�������ļ�¼���һ��������
//ʵ����Ծʽ�ƶ���ʹ������Ч������
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

//������  
//������������й����һ���󶥶ѡ��������е����ֵ���ǶѶ��ĸ���㡣
//�������ߣ�������������ĩβԪ�ؽ�������ʱĩβԪ�ؾ������ֵ����
//Ȼ��ʣ���n-1���������¹����һ���ѣ������ͻ�õ�n��Ԫ���дδ�ֵ���������У�ֱ���õ������������С�         
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
	for (i = L->length / 2; i > 0; i--)  //���к��ӵĽ�����¶��Ͻ��й���
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
	printf("ð������:\n");
	BubbleSort(&L0);
	print(L0);


	printf("ѡ������:\n");
	BubbleSort(&L1);
	print(L1);

	printf("��������:\n");
	BubbleSort(&L2);
	print(L2);

	printf("ϣ������:\n");
	BubbleSort(&L3);
	print(L3);

	printf("������:\n");
	BubbleSort(&L4);
	print(L4);
	getchar();
    return 0;
}

