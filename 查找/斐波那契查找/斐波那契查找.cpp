// 斐波那契查找.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdlib.h"
#include "math.h"

#define MAXSIZE 20

int Fibonacci_Search(int *ar, int n, int key) {
	int F[MAXSIZE];
	int i,k=0;
	F[0] = 0;
	F[1] = 1;
	for (i = 2; i <n; i++)
		F[i] = F[i - 1] + F[i - 2];
	i = 0;
	//得到数组长度n在Fibonacci数列中的位置
	while (n > F[i] - 1)
		i++;
	printf("\ni=%d,F[%d]=%d",i,i,F[i]);
	//补齐数组n后的到Fibonacci数组下一位对应的长度值之间的数，防止判断越界
	
	for (k = n; k< F[i] - 1; k++)
	{
		if (k < MAXSIZE) {
			ar[k] = ar[n];
			printf("\nk=%d,ar[%d]=%d", k, k, ar[k]);
		}
	}


	int low, point_fibo, high,count;
	low = 1;
	high = n;
	count = 0;
	while (low <= high) {
		count++;
		point_fibo = low + F[i - 1] - 1;
		if (key < ar[point_fibo]) {
			high = point_fibo- 1;
			i = i - 1;
		}
		else if (key > ar[point_fibo]) {
			low = point_fibo + 1;
			i = i - 2;   //右半区的数量   F[i]-F[i-1]=F[i-2]
		}
		else {    //key=ar[point_fibo] 有两种情况：界内和超出n的范围

			printf("\n查找次数:%d",count);
			if (point_fibo <= n)
				return point_fibo;
			else
				return n;
			
		}
	}
	return 0;
}


int main()
{
	int ar[MAXSIZE] = { 0,1,16,24,35,47,59,62,73,88,99 };
	printf("查找的有序表数组：\n");
	for (int i = 0; i < MAXSIZE; i++) {
		printf("%d  ", ar[i]);
	}
	printf("\n要查找的数据：%d", 35);
	Fibonacci_Search(ar, 11, 35);
   
	getchar();
	return 0;
}

