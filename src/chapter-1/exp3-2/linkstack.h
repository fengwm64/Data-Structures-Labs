#pragma once

#include "StatusCode.h"

#define ElemType char

typedef struct StackNode
{
	ElemType data;
	struct StackNode *next;
} StackNode, *LinkStack;

Status InitStack(LinkStack &S);		   // ��ʼ��
Status StackEmpty(LinkStack S);		   // ջ�Ƿ�Ϊ��
Status Push(LinkStack &S, ElemType e); // ��ջ
Status Pop(LinkStack &S, ElemType &e); // ��ջ
ElemType GetTop(LinkStack S);		   // ��ȡջ��Ԫ��
Status DestoryStack(LinkStack &S);	   // ����