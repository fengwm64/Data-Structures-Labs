#include "linkstack.h"
#include <iostream>
using namespace std;

// 初始化
Status InitStack(LinkStack& S)
{
	S = new StackNode;
	if (!S)
		exit(OVERFLOW);
	S->next = NULL;
	return OK;
}

// 销毁栈
Status DestoryStack(LinkStack& S)
{
	StackNode* p = S, * tp;
	while (p)
	{
		tp = p;
		p = p->next;
		delete tp;
	}
	S = NULL;
	return OK;
}

// 判断栈是否为空
Status StackEmpty(LinkStack S)
{
	if (!S->next)
		return OK;
	else
		return FALSE;
}

// 入栈
Status Push(LinkStack& S, ElemType e)
{
	StackNode* p = new StackNode;
	if (!p)
		return OVERFLOW;
	p->data = e;
	p->next = S->next;
	S->next = p;		
}

// 出栈
Status Pop(LinkStack& S, ElemType& e)
{
	if (!S->next)
	{
		cout << "栈空" << endl;
		return ERROR;
	}
	e = S->next->data;		
	StackNode* tp = S->next;
	S->next = S->next->next;	
	delete tp;			
	return OK;
}

// 获取栈顶元素
ElemType GetTop(LinkStack S)
{
	if (!S->next)
	{
		cout << "栈空" << endl;
		return ERROR;
	}
	return S->next->data;
}
