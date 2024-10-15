//-------------------------exp7-1.cpp-----------------------

// 1、教材P247实验题1：实现二叉树的各种基本运算的算法
// 编写一个程序btree.cpp，实现二叉树的基本运算，并在此基础上设计一个程序exp7 - 1.cpp完成以下功能。
// （1）由图7.33所示的二叉树创建对应的二叉链存储结构b，该二叉树的括号表示串为“A(B(D, E(H(J, K(L, M(, N))))), C(F, G(, i)))”。
// （2）输出二叉树b。
// （3）输出‘H’结点的左、右孩子结点值。
// （4）输出二叉树b的高度。
// （5）释放二叉树b。

#include <iostream>
#include "btree.h"
using namespace std;

int main()
{
	BiTree b;
	InitBiTree(b);
	cout << "（1）由图7.33所示的二叉树创建对应的二叉链存储结构b" << endl;
	CreateBiTree("A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))", b);

	cout << endl
		 << "（2）输出二叉树b" << endl;
	cout << "     ";
	PrintBiTree(b);

	cout << endl;
	cout << endl
		 << "（3）输出‘H’结点的左、右孩子结点值" << endl;
	FindTNode(b, 'H');
	cout << endl;

	cout << endl
		 << "（4）输出二叉树b的高度：" << BiTreeHeight(b) << endl;
	cout << endl
		 << "（5）释放二叉树b" << endl;
	DestroyBiTree(b);

	return 0;
}