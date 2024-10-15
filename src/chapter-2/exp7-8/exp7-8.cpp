#include <iostream>
using namespace std;

// 4、教材P248实验题8：简单算术表达式二叉树的构建和求值
// 编写一个程序exp7 - 8.cpp，先用二叉树来表示一个简单算术表达式，树的每一个结点包括一个运算符或运算数。
// 在简单算术表达式中只包含 + 、 - 、 * 、 / 和一位正整数且格式正确（不包括括号），并且要按照先乘除后加减的原则构造二叉树，
// 图7.34所示为“1 + 2 * 3 - 4 / 5”代数表达式对应的二叉树，然后由对应的二叉树计算该表达式的值。

// 数据域元素类型
#define ElemType char

// 二叉树节点定义
typedef struct BiTNode
{
	ElemType data;					 // 数据域
	struct BiTNode *lchild, *rchild; // 左、右孩子指针
} BiTNode, *BiTree;

// 二叉树操作
BiTree CreateBiTree(string str);	   // 创建二叉树
void DestroyBiTree(BiTree &T);		   // 销毁二叉树
void PrintBiTree(BiTree T, int depth); // 打印二叉树(凹入表示法)
double CalculareBiTree(BiTree T);	   // 计算

int main()
{
	string s = "1+2*3-4/5";
	BiTree B;
	cout << "1.根据" << s << "构造二叉树" << endl;
	B = CreateBiTree(s);
	cout << endl
		 << "2.凹入表示法输出二叉树" << endl;
	PrintBiTree(B, 0);
	cout << endl
		 << "3.根据二叉树计算表达式值为：" << CalculareBiTree(B) << endl;
	DestroyBiTree(B);
	return 0;
}

// 创建二叉树
BiTree CreateBiTree(string str)
{
	// 申请新建结点空间
	BiTNode *b = new BiTNode;
	// 确定表达式长度（最大循环次数）
	int len = str.length();
	// 表达式空，返回NULL
	if (!len)
		return NULL;

	/*
	Tips1：从表达式尾部开始查找
		观察题目给出的图可以知道，表达式后面的符号在树的上层
		建树是从根往下建立，所以从表达式尾部开始查找

	Tips2：先找+-
		因为计算树表达式时利用先序遍历，首先访问根，然后左、右
		根据递归原理，递归到最深才返回
		运算法则先* / 再+-，所以* /在最深，+-在上层
	*/

	// 先从字符串尾部开始往回寻找+ -
	for (int i = len - 1; i >= 0; i--)
	{
		if (str[i] == '+' || str[i] == '-')
		{
			// 符号作为根结点
			b->data = str[i];
			// 符号左边表达式进入递归继续创建
			b->lchild = CreateBiTree(str.substr(0, i));
			// 符号右边表达式进入递归继续创建
			b->rchild = CreateBiTree(str.substr(i + 1));
			return b;
		}
	}
	// 如果没有找到+-；就字符串尾部开始往回寻找* /
	for (int i = len - 1; i >= 0; i--)
	{
		if (str[i] == '*' || str[i] == '/')
		{
			// 符号作为根结点
			b->data = str[i];
			// 符号左边表达式进入递归继续创建
			b->lchild = CreateBiTree(str.substr(0, i));
			// 符号右边表达式进入递归继续创建
			b->rchild = CreateBiTree(str.substr(i + 1));
			return b;
		}
	}
	// 最后如果+-/*都没有找到，只剩下数字了
	// 数字作为叶子结点，直接赋值返回
	b->data = str[0];
	b->lchild = NULL;
	b->rchild = NULL;
	return b;
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

// 打印二叉树(凹入表示法)
void PrintBiTree(BiTree T, int depth)
{
	// 递归终止条件
	if (!T)
		return;
	// 打印凹入的符号，depth为凹入深度
	for (int i = 0; i < depth; i++)
		cout << "###";
	cout << T->data;
	cout << endl;
	// 非叶子节点才需要递归深入，减少递归深度
	if (T->lchild || T->rchild)
	{
		PrintBiTree(T->lchild, depth + 1);
		PrintBiTree(T->rchild, depth + 1);
	}
}

// 计算
double CalculareBiTree(BiTree T)
{
	if (!T)
		return -1;
	switch (T->data)
	{
	case '+':
		return CalculareBiTree(T->lchild) + CalculareBiTree(T->rchild);
	case '-':
		return CalculareBiTree(T->lchild) - CalculareBiTree(T->rchild);
	case '*':
		return CalculareBiTree(T->lchild) * CalculareBiTree(T->rchild);
	case '/':
		return CalculareBiTree(T->lchild) / CalculareBiTree(T->rchild);
	default:
		return T->data - '0';
	}
}