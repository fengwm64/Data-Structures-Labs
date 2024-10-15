#include "sqqueue.h"
#include <iostream>
using namespace std;

// 初始化队列
Status InitQueue(SqQueue &Q)
{
	Q.base = new ElemType[MaxSize]; // 分配动态空间
	// 如果base指针为NULL，代表空间分配失败
	if (!Q.base)
	{
		cout << "队列初始化失败！" << endl;
		return OVERFLOW;
	}
	Q.front = Q.rear = 0; // 空间分配成功，初始化队头与队尾指针
	return OK;
}
// 销毁队列
Status DestroyQueue(SqQueue &Q)
{
	delete Q.base;		  // 释放动态分配的空间
	Q.base = NULL;		  // 数组指针置空
	Q.front = Q.rear = 0; // 头尾置0，队列空
	return OK;
}
// 清空队列
Status ClearQueue(SqQueue &Q)
{
	Q.front = Q.rear = 0; // 头尾置0，队列空
	return OK;
}
// 队列判空
Status QueueEmpty(SqQueue Q)
{
	if (Q.front == Q.rear)
		return TRUE;
	else
		return FALSE;
}
// 队列求长
Status QueueLength(SqQueue Q)
{
	return (Q.rear - Q.front + MaxSize) % MaxSize;
}
// 获取队头
Status GetHead(SqQueue Q, ElemType &e)
{
	// 队列非空才可以获取队头
	if (Q.front != Q.rear)
	{
		e = Q.base[Q.front];
		return OK;
	}
	else
		return ERROR;
}
// 入队
Status EnQueue(SqQueue &Q, ElemType e)
{
	// 判断队是否已满，满则返回错误
	if ((Q.rear + 1) % MaxSize == Q.front)
	{
		cout << "队满！！！" << endl;
		return ERROR;
	}
	Q.base[Q.rear] = e;				 // 元素e入队尾
	Q.rear = (Q.rear + 1) % MaxSize; // 根据循环队列逻辑，使尾指针逻辑后移
	return OK;
}
// 出队
Status DeQueue(SqQueue &Q, ElemType &e)
{
	// 判断队是否已空，空则返回错误
	if (Q.front == Q.rear)
	{
		cout << "队空！！！" << endl;
		return ERROR;
	}
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MaxSize; // 根据循环队列逻辑，使头指针逻辑后移
	return OK;
}