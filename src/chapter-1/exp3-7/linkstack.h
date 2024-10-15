#pragma once

#include "StatusCode.h"

#define ElemType int

typedef struct StackNode
{
	ElemType data;
	struct StackNode* next;
}StackNode, * LinkStack;

Status InitStack(LinkStack& S);			// 初始化
Status DestoryStack(LinkStack& S);	// 销毁
Status StackEmpty(LinkStack S);	// 栈是否为空
Status Push(LinkStack& S, ElemType e);	// 入栈
Status Pop(LinkStack& S, ElemType& e);	// 出栈
ElemType GetTop(LinkStack S);	// 获取栈顶元素