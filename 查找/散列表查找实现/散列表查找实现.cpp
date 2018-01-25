// 散列表查找实现.cpp : 定义控制台应用程序的入口点。
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
	int *elem;  //数据元素存储基址
	int count;//当前数据元素个数
}HashTable;

int m = 0;    //散列表表长

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

//散列函数 
int Hash(int key) {
	return key%m; //除留余数法
}

//将关键字插入喊列表
void InsertHash(HashTable *H, int key) {
	int addr = Hash(key);
	while (H->elem[addr] != NULLKEY) {  //插入时不为空，说明地址被占用，出现冲突情况
		addr = (addr + 1) % m;   //开放地址法的线性探测
	}
	H->elem[addr] = key;
}

Status SearchHash(HashTable H, int key, int *addr) {
	*addr = Hash(key);
	while (H.elem[*addr] != key) {  //查找的时候出现地址冲突的情况
		*addr = (*addr + 1) % m;
		if (H.elem[*addr] == NULLKEY || *addr == Hash(key))  //判断的第二种情况是回到了原点
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
		printf("查找 %d 的地址为：%d \n", key, p);
	else
		printf("查找 %d 失败。\n", key);

	for (i = 0; i < m; i++) {
		key = arr[i];
		SearchHash(H,key,&p);
		printf("查找 %d 的地址为：%d\n",key,p);
	}

	getchar();
    return 0;
}

