// ɢ�б����ʵ��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdlib.h"
#include "io.h"

#define OK 1
#define ERROR -1
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100
#define SUCCESS 1
#define UNSUCCESS 0
#define HASHSIZE 12 
#define NULLKEY -32768    

typedef int Status;
typedef struct {
	int *elem;  //����Ԫ�ش洢��ַ
	int count;//��ǰ����Ԫ�ظ���
}HashTable;

int m = 0;    //ɢ�б��

Status InitHashTable(HashTable *H) {
	int i;
	m = HASHSIZE;
	H->count = m;
	H->elem = (int *)malloc(m * sizeof(int));
	for (i = 0; i < m; i++) {
		H->elem[i] = NULLKEY;
	}
	return OK;
}

//ɢ�к��� 
int Hash(int key) {
	return key%m; //����������
}

//���ؼ��ֲ��뺰�б�
void InsertHash(HashTable *H, int key) {
	int addr = Hash(key);
	while (H->elem[addr] != NULLKEY) {  //����ʱ��Ϊ�գ�˵����ַ��ռ�ã����ֳ�ͻ���
		addr = (addr + 1) % m;   //���ŵ�ַ��������̽��
	}
	H->elem[addr] = key;
}

Status SearchHash(HashTable H, int key, int *addr) {
	*addr = Hash(key);
	while (H.elem[*addr] != key) {  //���ҵ�ʱ����ֵ�ַ��ͻ�����
		*addr = (*addr + 1) % m;
		if (H.elem[*addr] == NULLKEY || *addr == Hash(key))  //�жϵĵڶ�������ǻص���ԭ��
			return UNSUCCESS;
	}
	return SUCCESS;
}
int main()
{
	int arr[HASHSIZE] = { 12,67,56,16,25,37,22,29,15,47,48,34 };
	int i, p, key, result;
	HashTable H;

	key = 39;
	InitHashTable(&H);
	for (i = 0; i < m; i++)
		InsertHash(&H, arr[i]);
	result=SearchHash(H, key, &p);
	if (result)
		printf("���� %d �ĵ�ַΪ��%d \n", key, p);
	else
		printf("���� %d ʧ�ܡ�\n", key);

	for (i = 0; i < m; i++) {
		key = arr[i];
		SearchHash(H,key,&p);
		printf("���� %d �ĵ�ַΪ��%d\n",key,p);
	}

	getchar();
    return 0;
}

