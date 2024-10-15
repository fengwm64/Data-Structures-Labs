#include <iostream>
#include "bst.h"
using namespace std;

// 插入节点
void insertBST(BiNode *&bt, ElemType key)
{
	// 当树根为空时
	// 直接建立(子)树
	if (!bt)
	{
		bt = new BiNode;
		bt->elem = key;
		bt->lchild = NULL;
		bt->rchild = NULL;
	}
	// 如果树根不空，则递归往下，直到空
	else
	{
		if (key < bt->elem)
			insertBST(bt->lchild, key);
		else
			insertBST(bt->rchild, key);
	}
}
// 括号表示法输出
void bracketPrint(BiNode *T)
{
	if (!T) // 递归终止条件
		return;

	cout << T->elem;

	// 只有在左右孩子至少有一个存在时才访问
	if (T->lchild || T->rchild)
	{
		cout << "(";			 // 要访问孩子时添加（
		bracketPrint(T->lchild); // 递归调用
		cout << ",";			 // 访问完毕左孩子要访问右孩子时添加，
		bracketPrint(T->rchild); // 递归调用
		cout << ")";			 // 访问完毕左右孩子添加）
	}
}

int MIN = -111;
bool flag = true;
// 判断是否是二叉排序树
bool isBiSort(BiNode *T)
{
	if (!T->lchild && flag)
		isBiSort(T->lchild);
	if (T->elem < MIN)
		flag = false;
	MIN = T->elem;
	if (!T->rchild && flag)
		isBiSort(T->rchild);
	return flag;
}
// 建立二叉排序树
void BiSortTree(BiNode *&bt, ElemType elem[], int len)
{
	bt = NULL;
	for (int i = 0; i < len; i++)
		insertBST(bt, elem[i]);
}
// 搜索（递归）
BiNode *searchBST(BiNode *bt, ElemType key)
{
	if (!bt)
		return NULL;
	else
	{
		cout << bt->elem << " ";
		if (key == bt->elem)
		{
			cout << "找到了" << endl;
			return bt;
		}
		else if (key < bt->elem)
			return searchBST(bt->lchild, key);
		else
			return searchBST(bt->rchild, key);
	}
}
// 搜索（非递归）
BiNode *searchBST_NoR(BiNode *bt, ElemType key)
{
	BiNode *p = bt;
	while (p && p->elem != key)
	{
		cout << p->elem << " ";
		// key大走右
		if (key > p->elem)
			p = p->rchild;
		// key小走左
		else
			p = p->lchild;
	}
	if (!p)
		return NULL;
	else
	{
		cout << p->elem << " ";
		cout << "找到了" << endl;
		return p;
	}
}
// 删除节点
void deleteNode(BiNode *&bt)
{
	BiNode *p = NULL;
	BiNode *parent, *pre;

	// bt为叶子节点
	if (!bt->lchild && !bt->rchild)
	{
		p = bt;
		bt = NULL;
		delete p;
	}
	// 左子树
	else if (!bt->lchild)
	{
		p = bt;
		bt = bt->rchild;
		delete p;
	}
	// 右子树
	else if (!bt->rchild)
	{
		p = bt;
		bt = bt->lchild;
		delete p;
	}
	// 左右都不空
	else
	{
		// 初始化parent与pre
		parent = bt;
		pre = parent->lchild;
		// 当删除一个左右都不空的节点时
		// 为了可以仍然构成一棵排序树
		// 需要找到左子树中最大的节点替换被删除节点
		// 下面的while循环即为找到左子树中最大节点
		while (pre->rchild)
		{
			parent = pre;
			pre = pre->rchild;
		}
		// 找到后进行替换
		bt->elem = pre->elem;
		// 接上右子树
		if (parent != bt)
			parent->rchild = pre->lchild;
		// 接上左子树
		else
			parent->lchild = pre->lchild;
	}
}
// 删除值为key的节点
bool deleteBST(BiNode *&bt, ElemType key)
{
	if (!bt)
		return false;
	else
	{
		if (key == bt->elem)
			deleteNode(bt);
		else if (key < bt->elem)
			return deleteBST(bt->lchild, key);
		else
			return deleteBST(bt->rchild, key);
		return true;
	}
}