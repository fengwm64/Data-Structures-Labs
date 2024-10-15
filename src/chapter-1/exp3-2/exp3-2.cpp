/*
2、教材P118实验题2：实现链栈的各种基本运算的算法
编写一个程序linkstack.cpp，实现链栈（假设栈中元素类型ElemType为char）的各种基本运算，并在此基础上设计一个程序exp3-2.cpp完成以下功能。
（1）初始化栈s。
（2）判断栈s是否为空。
（3）依次进栈元素a、b、c、d、e。
（4）判断栈s是否非空。
（5）输出出栈序列。
（6）判断栈s是否非空。
（7）释放栈。
*/

#include "linkstack.h"
#include <iostream>
using namespace std;

int main()
{
	LinkStack s;
	ElemType e;

	cout << "1.初始化栈s" << endl;
	InitStack(s);

	cout << endl
		 << "2.判断栈s是否为空(1空/0非空)：" << StackEmpty(s) << endl;

	cout << endl
		 << "3.依次进栈元素a、b、c、d、e" << StackEmpty(s) << endl;
	ElemType elem[] = {'a', 'b', 'c', 'd', 'e'};
	for (int i = 1; i < 6; i++)
		Push(s, elem[i - 1]);

	cout << endl
		 << "4.判断栈s是否为空(1空/0非空)：" << StackEmpty(s) << endl;

	cout << endl
		 << "5.输出出栈序列：" << endl;
	while (!StackEmpty(s))
	{
		Pop(s, e);
		cout << "   " << e << endl;
	}

	cout << endl
		 << "6.判断栈s是否为空(1空/0非空)：" << StackEmpty(s) << endl;
	cout << endl
		 << "6.释放栈" << endl;
	DestoryStack(s);
	return 0;
}