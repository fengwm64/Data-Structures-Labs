#include <iostream>
using namespace std;

// 2、教材P248实验题3：由遍历序列构造二叉树
// 编写一个程序exp7 - 3.cpp，实现由先序序列和中序序列以及由中序序列和后序序列构造一棵二叉树的功能（二叉树种的每个结点值为单个字符），
// 要求以括号表示和凹入表示法输出该二叉树，
// 并用先序遍历序列“ABDEHJKLMNCFGI”和中序遍历序列“DBJHLKMNEAFCGI”
// 以及由中序遍历序列“DBJHLKMNEAFCGI”和后序遍历序列“DJLNMKHEBFIGCA”进行验证

// 数据域元素类型
#define ElemType char

// 二叉树节点定义
typedef struct BiTNode
{
	ElemType data;					 // 数据域
	struct BiTNode *lchild, *rchild; // 左、右孩子指针
} BiTNode, *BiTree;

// 二叉树操作
void InitBiTree(BiTree &T);											 // 初始化二叉树
void DestroyBiTree(BiTree &T);										 // 销毁二叉树
BiTree Pre_InCreateBT(const char Pre[], const char In[], int len);	 // 先序、中序序列创建二叉树
BiTree In_PostCreateBT(const char Post[], const char In[], int len); // 后序、中序序列创建二叉树
void PrintBiTree(BiTree T);											 // 打印二叉树（括号表示法）
void PrintBiTree(BiTree T, int depth);								 // 打印二叉树（凹入表示法）

int main()
{
	int len = strlen("ABDEHJKLMNCFGI");
	cout << "用先序“ABDEHJKLMNCFGI”和中序“DBJHLKMNEAFCGI”构造二叉树b1" << endl;
	BiTree b1 = Pre_InCreateBT("ABDEHJKLMNCFGI", "DBJHLKMNEAFCGI", len);

	cout << endl
		 << "由中序“DBJHLKMNEAFCGI”和后序“DJLNMKHEBFIGCA“构造二叉树b2" << endl;
	BiTree b2 = In_PostCreateBT("ABDEHJKLMNCFGI", "DBJHLKMNEAFCGI", len);

	cout << endl
		 << "括号表示法表示b1" << endl;
	PrintBiTree(b1);
	cout << endl;
	cout << "凹入表示法表示b1" << endl;
	PrintBiTree(b1, 0);

	cout << endl
		 << "括号表示法表示b2" << endl;
	PrintBiTree(b2);
	cout << endl;
	cout << "凹入表示法表示b2" << endl;
	PrintBiTree(b2, 0);

	DestroyBiTree(b1);
	DestroyBiTree(b2);

	return 0;
}

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

// 先序、中序序列创建二叉树
BiTree Pre_InCreateBT(const char Pre[], const char In[], int len)
{
	// 递归终止条件
	if (len <= 0)
		return NULL;
	// 表示”根节点“在中序序列的位置
	int i = 0;
	// 在中序序列寻找”根节点“
	for (; i < len; i++)
		if (*Pre == In[i])
			break;
	// 创建节点空间，进行递归建立二叉树
	BiTree T = new BiTNode;
	T->data = *Pre;
	T->lchild = Pre_InCreateBT(Pre + 1, In, i);
	T->rchild = Pre_InCreateBT(Pre + 1 + i, In + i + 1, len - i - 1);
	return T;
}

// 后序、中序序列创建二叉树
BiTree In_PostCreateBT(const char Post[], const char In[], int len)
{
	// 递归终止条件
	if (len <= 0)
		return NULL;
	// 表示”根节点“在中序序列的位置
	int i = 0;
	// 在中序序列寻找”根节点“
	for (; i < len; i++)
		if (Post[len - 1] == In[i])
			break;
	// 创建节点空间，进行递归建立二叉树
	BiTree T = new BiTNode;
	T->data = Post[len - 1];
	T->lchild = Pre_InCreateBT(Post, In, i);
	T->rchild = Pre_InCreateBT(Post + i, In + i + 1, len - i - 1);
	return T;
}

// 打印二叉树(广义表表示法)
void PrintBiTree(BiTree T)
{
	if (!T) // 递归终止条件
		return;

	cout << T->data;

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

// 打印二叉树(凹入表示法)
void PrintBiTree(BiTree T, int depth)
{
	// 递归终止条件
	if (!T)
		return;
	// 打印凹入的符号，depth为凹入深度
	for (int i = 0; i < depth; i++)
		cout << "***";
	cout << T->data;
	cout << endl;
	// 非叶子节点才需要递归深入，减少递归深度
	if (T->lchild || T->rchild)
	{
		PrintBiTree(T->lchild, depth + 1);
		PrintBiTree(T->rchild, depth + 1);
	}
}
