// 拆半查找.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdlib.h"
#include "math.h"

int Binary_Search(int *ar,int n,int key) {
	int low,mid,high;
	low = 1;                  //指定开始下标
	high = n;				//指定结束下标
	int count = 0;
	while (low <= high) {
		count++;
		mid = (low+high)/2;
		if (key < ar[mid])
			high = mid - 1;
		else if (key > ar[mid])
			low = mid + 1;
		else {
			printf("\n查找次数：%d", count);
			return mid;
		}
	}
	return 0;
}


int main()
{
	int ar[11] = {0,1,16,24,35,47,58,62,73,88,99};
	printf("查找的有序表数组：\n");
	for (int i = 0; i < 11; i++) {
		printf("%d  ",ar[i]);
	}

	printf("\n要查找的数据：%d",73);
	Binary_Search(ar, 10, 73);

	getchar();
    return 0;
}

