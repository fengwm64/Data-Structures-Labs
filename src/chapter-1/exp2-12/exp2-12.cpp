#include <iostream>
#include "linklist.h"

using namespace std;
#define MaxSize 100
/*
4、教材P77实验题12：用单链表实现两个大整数的相加运算
编写一个程序exp2-12.cpp完成以下功能。
（1）将用户输入的十进制整数字符串转化为带头结点的单链表，每个结点存放一个整数位。
（2）求两个整数单链表相加的结果单链表。
（3）求结果单链表的中间位，如123的中间位为2，1234的中间位为2。
*/
void BigIntAdd(LinkList &opL, LinkList &opR, LinkList &result);
void GetMid(LinkList &result, ElemType &e);

int main()
{
	int len;
	ElemType e;
	LinkList opL, opR, result;
	InitList(opL);
	InitList(opR);
	InitList(result);

	char *str = new char[MaxSize];
	cout << "单链表实现两个大整数的相加运算" << endl;

	cout << "请输入左操作数：";
	cin >> str;
	len = strlen(str);
	opL->data = len; // 利用头节点存储链表长度信息
	for (int i = 0; i < len; i++)
		CreateList_Head(opL, int(str[i] - '0'));

	cout << "请输入右操作数：";
	cin >> str;
	len = strlen(str);
	opR->data = len; // 利用头节点存储链表长度信息
	for (int i = 0; i < len; i++)
		CreateList_Head(opR, int(str[i] - '0'));

	BigIntAdd(opL, opR, result);
	GetMid(result, e);

	cout << "结果单链表的中间位为：" << e << endl;

	Destroy(opL);
	Destroy(opR);
	Destroy(result);
	return 0;
}

void BigIntAdd(LinkList &opL, LinkList &opR, LinkList &result)
{
	int n = min(opR->data, opL->data);
	int out = 0; // 进位
	int temp = 0;
	// 分别建立左右操作数、结果链表的工作指针
	LNode *pL = opL->next;
	LNode *pR = opR->next;

	for (int i = 0; i < n; i++)
	{
		temp = pL->data + pR->data + out;
		out = temp >= 10 ? 1 : 0;
		CreateList_Head(result, temp % 10);
		pL = pL->next;
		pR = pR->next;
	}
	pL = pL ? pL : pR;
	while (pL)
	{
		temp = pL->data + out;
		out = temp >= 10 ? 1 : 0;
		CreateList_Head(result, temp % 10);
		pL = pL->next;
	}
	if (out)
		CreateList_Head(result, out);
	cout << "结果为：";
	PrintList(result);
	cout << endl;
}
void GetMid(LinkList &result, ElemType &e)
{
	int len = ListLength(result);
	GetElem(result, len / 2, e);
}