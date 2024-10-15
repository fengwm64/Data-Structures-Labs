#include <iostream>
#include "linkstack.h"
using namespace std;

#define MaxSize 100
/*
5、教材P119实验题7：求解栈元素排序问题
编写一个程序exp3-7.cpp，按升序对一个字符栈进行排序，即最小元素位于栈顶，
最多只能使用一个额外的栈存放临时数据，并输出栈排序过程。
*/

int main()
{
	int len = 0;
	char str[MaxSize];
	LinkStack S, Stemp; // 字符栈,辅助栈
	ElemType e, temp;	// 出栈元素，对应字符栈,辅助栈
	// 初始化两个栈
	InitStack(S);
	InitStack(Stemp);

	// 输入一个字符串然后全部入栈
	cout << "求解栈元素排序问题" << endl;
	cout << "请输入：";
	cin >> str;
	len = strlen(str);
	for (int i = 0; i < len; i++)
		Push(S, int(str[i] - '0'));

	// 开始栈排序
	while (!StackEmpty(S)) // 栈S不空一直循环
	{
		Pop(S, e); // 出栈元素e
		cout << "栈S出栈" << e << "，";
		while (!StackEmpty(Stemp))
		{
			temp = GetTop(Stemp);
			cout << "栈Stemp栈顶" << temp << endl;
			if (temp > e)
			{
				cout << "因为" << temp << ">" << e;
				cout << "，" << temp << "出栈Stemp,入栈S" << endl;
				Pop(Stemp, temp);
				Push(S, temp);
			}
			else
			{
				cout << "因为" << temp << "<" << e << "，Stemp出栈循环结束" << endl;
				break;
			}
		}
		// 辅助栈空直接入栈
		Push(Stemp, e);
		cout << e << "进栈Stemp" << endl;
	}

	cout << endl;
	cout << "排序后：";

	// 将排序好的元素从辅助栈压回原栈
	while (!StackEmpty(Stemp))
	{
		Pop(Stemp, e);
		Push(S, e);
	}
	// 从原栈出栈输出
	while (!StackEmpty(S))
	{
		Pop(S, e);
		cout << e;
	}
	// 程序结束，销毁两个栈
	DestoryStack(S);
	DestoryStack(Stemp);

	return 0;
}
