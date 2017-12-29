// ��_KMP.cpp : �������̨Ӧ�ó������ڵ㡣
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

typedef char String[MAXSIZE + 1];    //0�ŵ�Ԫ��Ŵ�����

Status StrAssign(String T, char *chars) {
	int i;
	if (strlen(chars) > MAXSIZE)
		return ERROR;
	else {
		T[0] = strlen(chars);
		for (i = 1; i <= T[0]; i++) {
			T[i] = *(chars + i - 1);
		}
		printf("�ַ����ĳ����ǣ�%d\n",T[0]);
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

//����ģʽƥ�䷨
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
		printf("S[0]��ֵΪ��%d i��ֵΪ��%d  T[0]��ֵΪ��%d\n",S[0], i, T[0]);
		return i - T[0];
	}
	else
		return 0;
}

//���㷵���Ӵ���NEXT����
void get_next(int *next,String T) {
	int i = 1;
	int j = 0;
	next[1] = 0;
	while (i < T[0]) {
		if (j == 0 || T[i] == T[j]) {  //T[i]Ϊ��׺�ĵ����ַ���T[j]Ϊǰ׺�ĵ����ַ�
			++i;
			++j;
			next[i] = j;
		}
		else
			j = next[j];    //����ַ�����ͬ��jֵ������
	}
}

//�����Ӵ�T������S��pos�ַ�֮���λ�ã���������ں�������ֵΪ0
int Index_KMP(String S, String T, int pos) {
	int i = pos;   //��¼������ǰ�±�ֵ
	int j = 1;		//��¼�Ӵ���ǰ�±�ֵ
	int next[255];
	get_next(next, T);  //����Ӵ�next����ֵ
	while (i <=S[0] && j <=T[0]) {
		if (j == 0 || T[j] == S[i]) {
			++i;
			++j;
		}
		else {
			j = next[j];    //��������ȣ�j�����ߵ�����λ�ã�i��ֵ����
		}
	}
	if (j > T[0]) {
		printf("S[0]��ֵΪ��%d i��ֵΪ��%d  T[0]��ֵΪ��%d\n", S[0], i, T[0]);
		return i - T[0];
	}
	else
		return 0;
}

//�Ľ���next����ֵ��
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
		printf("S[0]��ֵΪ��%d i��ֵΪ��%d  T[0]��ֵΪ��%d\n", S[0], i, T[0]);
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
	printf("�Ӵ�Ϊ: ");
	StrPrint(s1);
	i = StrLength(s1);
	p = (int*)malloc((i + 1) * sizeof(int));
	get_next( p,s1);
	printf("NextΪ: ");
	NextPrint(p, StrLength(s1));
	printf("\n");

	StrAssign(s1, "abcabx");
	printf("�Ӵ�Ϊ: ");
	StrPrint(s1);
	i = StrLength(s1);
	p = (int*)malloc((i + 1) * sizeof(int));
	get_next( p,s1);
	printf("NextΪ: ");
	NextPrint(p, StrLength(s1));
	printf("\n");

	StrAssign(s1, "ababaaaba");
	printf("�Ӵ�Ϊ: ");
	StrPrint(s1);
	i = StrLength(s1);
	p = (int*)malloc((i + 1) * sizeof(int));
	get_next(p,s1);
	printf("NextΪ: ");
	NextPrint(p, StrLength(s1));
	printf("\n");

	StrAssign(s1, "aaaaaaaab");
	printf("�Ӵ�Ϊ: ");
	StrPrint(s1);
	i = StrLength(s1);
	p = (int*)malloc((i + 1) * sizeof(int));
	get_next( p,s1);
	printf("NextΪ: ");
	NextPrint(p, StrLength(s1));
	printf("\n");

	StrAssign(s1, "ababaaaba");
	printf("   �Ӵ�Ϊ: ");
	StrPrint(s1);
	i = StrLength(s1);
	p = (int*)malloc((i + 1) * sizeof(int));
	get_next( p,s1);
	printf("   NextΪ: ");
	NextPrint(p, StrLength(s1));
	get_nextval(s1, p);
	printf("NextValΪ: ");
	NextPrint(p, StrLength(s1));
	printf("\n");

	StrAssign(s1, "aaaaaaaab");
	printf("   �Ӵ�Ϊ: ");
	StrPrint(s1);
	i = StrLength(s1);
	p = (int*)malloc((i + 1) * sizeof(int));
	get_next( p,s1);
	printf("   NextΪ: ");
	NextPrint(p, StrLength(s1));
	get_nextval(s1,p);
	printf("NextValΪ: ");
	NextPrint(p, StrLength(s1));

	printf("\n");

	StrAssign(s1, "000000000000000000000000000000100000001");
	printf("����Ϊ: ");
	StrPrint(s1);
	StrAssign(s2, "100000001");
	printf("�Ӵ�Ϊ: ");
	StrPrint(s2);
	printf("\n");
	printf("�������Ӵ��ڵ�%d���ַ����״�ƥ�䣨����ģʽƥ���㷨��\n", Index(s1, s2, 1));
	printf("�������Ӵ��ڵ�%d���ַ����״�ƥ�䣨KMP�㷨�� \n", Index_KMP(s1, s2, 1));
	printf("�������Ӵ��ڵ�%d���ַ����״�ƥ�䣨KMP�����㷨�� \n", Index_KMP1(s1, s2, 1));


	getchar();
    return 0;
}

