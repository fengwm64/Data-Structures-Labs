//-------------------------btree.cpp-----------------------
#include <iostream>
#include <cstring>
#include "btree.h"
using namespace std;

// 初始化二叉树
void InitBiTree(BiTree &T)
{
	T = new BiTNode;
	T->lchild = NULL;
	T->rchild = NULL;
}

// 销毁二叉树
void DestroyBiTree(BiTree &T)
{
	// 本算法递归直到叶子节点
	// 然后删除叶子节点返回父节点

	if (!T) // 递归终止条件
		return;
	// 有孩子才继续递归深入，没有代表目前节点为叶子，直接释放
	if (T->lchild || T->rchild)
	{
		DestroyBiTree(T->lchild);
		DestroyBiTree(T->rchild);
	}
	delete T;
	T = NULL;
}

// 在树中查找
bool FindTNode(BiTree T, ElemType e)
{
	if (!T) // 递归终止条件
		return false;

	// 如果找到啦，就输出左右孩子然后返回真
	if (T->data == e)
	{
		cout << "     " << e << "节点的";
		if (!T->lchild)
			cout << "左孩子为空";
		else
			cout << "左孩子为 " << T->lchild->data;
		if (!T->rchild)
			cout << " , 右孩子为空";
		else
			cout << " , 右孩子为 " << T->rchild->data;
		return true;
	}
	// 如果没有找到，看看这个节点有没有孩子，只要有一个孩子就去它孩子里边找找看
	else if (T->lchild || T->rchild)
	{
		// 如果在左孩子里找到啦就返回true
		if (FindTNode(T->lchild, e))
			return true;
		// 如果在右孩子里找到啦就返回true
		else if (FindTNode(T->rchild, e))
			return true;
	}
	// 如果很不幸，在这个节点的左右孩子里都找不到~~只能返回失败了
	else
		return false;
}

// 获取二叉树高度
int BiTreeHeight(BiTree T)
{
	// 空节点高度为0
	if (!T)
		return 0;
	// 非叶子节点才继续深入（减少递归层次）
	if (T->lchild || T->rchild)
	{
		int LHeight = BiTreeHeight(T->lchild);
		int RHeight = BiTreeHeight(T->rchild);
		return max(LHeight, RHeight) + 1;
	}
	// 叶子节点高度为1
	else
		return 1;
}

// 创建二叉树(非递归)
void CreateBiTree(const char str[], BiTree &T)
{
	int i = 0;							   // 用于遍历字符串的变量
	int flag = 2;						   // tag=0,创建左孩子；tag=1，创建右孩子
	int len = strlen(str);				   // 求字符串的长度
	int top = -1;						   // 父栈栈顶位置
	BiTNode *s = T;						   // s是用来开拓空间的指针
	BiTNode *ParentStack[MaxHeight]{NULL}; // 用于保存孩子节点的父节点地址

	T->data = str[i++]; // 给根节点赋值

	for (; i < len; i++)
	{
		switch (str[i])
		{
		case '(':					// 扫描到（表示即将插入一个左孩子
			flag = 0;				// 设置标志
			ParentStack[++top] = s; // 刚刚新建的孩子要当父亲，将其入栈
			break;
		case ')':  // 扫描到）说明该父节点孩子已经建立完毕，父指针无用
			top--; //	栈顶--
			break;
		case ',':
			flag = 1;
			break;
		default: // 当扫描到字母
			// 创建孩子节点
			s = new BiTNode;
			s->data = str[i];
			s->lchild = NULL;
			s->rchild = NULL;

			if (flag == 0) // 插入左孩子
				ParentStack[top]->lchild = s;
			else // 插入右孩子
				ParentStack[top]->rchild = s;
			break;
		}
	}
}

// 打印二叉树(先序/广义表)
void PrintBiTree(BiTree T)
{
	if (!T) // 递归终止条件
		return;

	Visit(T);

	// 只有在左右孩子至少有一个存在时才访问
	if (T->lchild || T->rchild)
	{
		cout << "(";			// 要访问孩子时添加（
		PrintBiTree(T->lchild); // 递归调用
		cout << ",";			// 访问完毕左孩子要访问右孩子时添加，
		PrintBiTree(T->rchild); // 递归调用
		cout << ")";			// 访问完毕左右孩子添加）
	}
}

// 访问（打印）节点值
void Visit(BiTNode *node)
{
	if (!node)
		return;
	cout << node->data;
}
