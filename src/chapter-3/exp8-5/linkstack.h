//  linkstack
//////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////以下为链栈内容//////////////////////////////////
#pragma once

#include "StatusCode.h"
#include <iostream>
using namespace std;

#define ElemType int // 栈元素的数据类型

typedef struct StackNode
{
	ElemType data;
	struct StackNode *next;
} StackNode, *LinkStack;

Status InitStack(LinkStack &S);		   // 初始化
Status StackEmpty(LinkStack S);		   // 栈是否为空
Status Push(LinkStack &S, ElemType e); // 入栈
Status Pop(LinkStack &S, ElemType &e); // 出栈
Status DestoryStack(LinkStack &S);	   // 销毁