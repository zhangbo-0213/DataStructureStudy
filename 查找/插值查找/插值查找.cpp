// ��ֵ����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdlib.h"
#include "math.h"

int interpolation_Search(int *ar,int n,int key) {
	int low, high, mid;
	int count = 0;
	low = 1;
	high = n;
	while (low <= high) {
		mid = low + (high - low)*(key - ar[low]) / (ar[high] - ar[low]);
		printf("\nmid:%d", mid);
		count++;
		if (key <ar[mid])
			high = mid - 1;
		else if (key > ar[mid])
			low = mid + 1;
		else {
			printf("\n��ѯ������%d",count);
			return mid;
		}
	}
	return 0;
}


int main()
{
	int ar[11] = { 0,1,16,24,35,47,58,62,73,88,99 };
	printf("���ҵ���������飺\n");
	for (int i = 0; i < 11; i++) {
		printf("%d  ", ar[i]);
	}

	printf("\nҪ���ҵ����ݣ�%d", 73);
	interpolation_Search(ar, 10, 73);

	getchar();
    return 0;
}

