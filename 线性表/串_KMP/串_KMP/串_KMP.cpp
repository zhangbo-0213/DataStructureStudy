// 串_KMP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "io.h"
#include "math.h"
#include "time.h"
#include "string.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100

typedef int Status;
typedef int Elemtype;

typedef char String[MAXSIZE + 1];    //0号单元存放串长度

Status StrAssign(String T, char *chars) {
	int i;
	if (strlen(chars) > MAXSIZE)
		return ERROR;
	else {
		T[0] = strlen(chars);
		for (i = 1; i <= T[0]; i++) {
			T[i] = *(chars + i - 1);
		}
		printf("字符串的长度是：%d\n",T[0]);
		return OK;
	}
}

Status ClearString(String S) {
	S[0] = 0;
	return OK;
}

void StrPrint(String S) {
	int i;
	for (i = 1; i <= S[0]; i++) {
		printf("%c",S[i]);
	}
	printf("\n");
}

void NextPrint(int next[],int length) {
	int i;
	for (i = 1; i <= length; i++) {
		printf("%d",next[i]);
	}
	printf("\n");
}

int StrLength(String S) {
	return  S[0];
}

//朴素模式匹配法
int Index(String S, String T,int pos) {
	int i, j;
	i = pos;
	j = 1;
	while (i <= S[0] && j <= T[0]) {
		if (S[i] == T[j]) {
			++i;
			++j;
		}
		else {
			i = i - j + 2;
			j = 1;
		}
	}
	if (j > T[0]) {
		printf("S[0]的值为：%d i的值为：%d  T[0]的值为：%d\n",S[0], i, T[0]);
		return i - T[0];
	}
	else
		return 0;
}

//计算返回子串的NEXT数组
void get_next(int *next,String T) {
	int i = 1;
	int j = 0;
	next[1] = 0;
	while (i < T[0]) {
		if (j == 0 || T[i] == T[j]) {  //T[i]为后缀的单个字符，T[j]为前缀的单个字符
			++i;
			++j;
			next[i] = j;
		}
		else
			j = next[j];    //如果字符不相同，j值往回走
	}
}

//返回子串T在主串S的pos字符之后的位置，如果不存在函数返回值为0
int Index_KMP(String S, String T, int pos) {
	int i = pos;   //记录主串当前下标值
	int j = 1;		//记录子串当前下标值
	int next[255];
	get_next(next, T);  //获得子串next数组值
	while (i <=S[0] && j <=T[0]) {
		if (j == 0 || T[j] == S[i]) {
			++i;
			++j;
		}
		else {
			j = next[j];    //若果不相等，j往回走到合适位置，i的值不变
		}
	}
	if (j > T[0]) {
		printf("S[0]的值为：%d i的值为：%d  T[0]的值为：%d\n", S[0], i, T[0]);
		return i - T[0];
	}
	else
		return 0;
}

//改进的next数组值求法
void get_nextval(String T, int *nextval) {
	int i = 1;
	int j = 0;
	nextval[1] = 0;
	while (i<T[0]) {
		if (j == 0 || T[j] == T[i]) {
			++i;
			++j;
			if (T[i] != T[j])
				nextval[i] = j;
			else
				nextval[i] = nextval[j];
		}
		else
			j = nextval[j];
	}
}

int Index_KMP1(String S, String T, int pos) {
	int i = pos;
	int j = 1;
	int nextval[255];
	get_nextval(T, nextval);
	while (i <=S[0] && j <=T[0]) {
		if (j == 0 || S[i] == T[j]) {
			++i;
			++j;
		}
		else
			j = nextval[j];
	}
	if (j > T[0]) {
		printf("S[0]的值为：%d i的值为：%d  T[0]的值为：%d\n", S[0], i, T[0]);
		return i - T[0];
	}	
	else
		return 0;
}
int main()
{
	int i, *p;
	String s1, s2;

	StrAssign(s1, "abcdex");
	printf("子串为: ");
	StrPrint(s1);
	i = StrLength(s1);
	p = (int*)malloc((i + 1) * sizeof(int));
	get_next( p,s1);
	printf("Next为: ");
	NextPrint(p, StrLength(s1));
	printf("\n");

	StrAssign(s1, "abcabx");
	printf("子串为: ");
	StrPrint(s1);
	i = StrLength(s1);
	p = (int*)malloc((i + 1) * sizeof(int));
	get_next( p,s1);
	printf("Next为: ");
	NextPrint(p, StrLength(s1));
	printf("\n");

	StrAssign(s1, "ababaaaba");
	printf("子串为: ");
	StrPrint(s1);
	i = StrLength(s1);
	p = (int*)malloc((i + 1) * sizeof(int));
	get_next(p,s1);
	printf("Next为: ");
	NextPrint(p, StrLength(s1));
	printf("\n");

	StrAssign(s1, "aaaaaaaab");
	printf("子串为: ");
	StrPrint(s1);
	i = StrLength(s1);
	p = (int*)malloc((i + 1) * sizeof(int));
	get_next( p,s1);
	printf("Next为: ");
	NextPrint(p, StrLength(s1));
	printf("\n");

	StrAssign(s1, "ababaaaba");
	printf("   子串为: ");
	StrPrint(s1);
	i = StrLength(s1);
	p = (int*)malloc((i + 1) * sizeof(int));
	get_next( p,s1);
	printf("   Next为: ");
	NextPrint(p, StrLength(s1));
	get_nextval(s1, p);
	printf("NextVal为: ");
	NextPrint(p, StrLength(s1));
	printf("\n");

	StrAssign(s1, "aaaaaaaab");
	printf("   子串为: ");
	StrPrint(s1);
	i = StrLength(s1);
	p = (int*)malloc((i + 1) * sizeof(int));
	get_next( p,s1);
	printf("   Next为: ");
	NextPrint(p, StrLength(s1));
	get_nextval(s1,p);
	printf("NextVal为: ");
	NextPrint(p, StrLength(s1));

	printf("\n");

	StrAssign(s1, "000000000000000000000000000000100000001");
	printf("主串为: ");
	StrPrint(s1);
	StrAssign(s2, "100000001");
	printf("子串为: ");
	StrPrint(s2);
	printf("\n");
	printf("主串和子串在第%d个字符处首次匹配（朴素模式匹配算法）\n", Index(s1, s2, 1));
	printf("主串和子串在第%d个字符处首次匹配（KMP算法） \n", Index_KMP(s1, s2, 1));
	printf("主串和子串在第%d个字符处首次匹配（KMP改良算法） \n", Index_KMP1(s1, s2, 1));


	getchar();
    return 0;
}

