#include <iostream>
#include <fstream>
using namespace std;

// 5、教材P249实验题9：用二叉树表示家谱关系并实现各种查找功能
// 编写一个程序exp7 - 9.cpp，采用一棵二叉树表示一个家谱关系（由若干家谱记录构成，每个家谱记录由父亲、母亲和儿子的姓名构成，其中姓名是关键字），要求程序具有以下功能。
// （1）	文件操作功能：家谱记录的输入，家谱记录的输出，清除全部文件记录和将家谱记录存盘。要求在输入家谱记录时按从祖先到子孙的顺序输入，第一个家谱记录的父亲域为所有人的祖先。
// （2）	家谱操作功能：用括号表示法输出家谱二叉树，查找某人的所有儿子，查找某人的所有祖先（这里的祖先是指所设计的二叉树结构中某结点的所有祖先结点）。

// 数据域元素类型
#define ElemType string

// 二叉树节点定义
typedef struct GenNode
{
	ElemType data;					 // 数据域
	struct GenNode *lchild, *rchild; // 左、右孩子指针
} GenNode, *GenTree;

// 全局变量(文件读写)
ifstream ifs;
ofstream ofs;
string p1, p2, p3;

// 显示菜单
void ShowMainMenu()
{
	cout << "**********************" << endl;
	cout << "******二叉树家谱******" << endl;
	cout << "**********************" << endl;
	cout << "** (1)文件操作功能  **" << endl;
	cout << "** (2)家谱操作功能  **" << endl;
	cout << "**********************" << endl;
	cout << "请输入：";
}
void ShowFMenu()
{
	cout << "1.家谱记录的输入" << endl;
	cout << "2.家谱记录的输出" << endl;
	cout << "3.清除全部文件记录" << endl;
	cout << "4.将家谱记录存盘" << endl;
	cout << "请输入：";
}
void ShowSMenu()
{
	cout << "1.括号表示法输出家谱" << endl;
	cout << "2.查找某人的所有儿子" << endl;
	cout << "3.查找某人的所有祖先" << endl;
	cout << "请输入：";
}

// 输出家谱
void PrintGen(GenTree Gen)
{
	if (!Gen)
	{
		cout << "空！" << endl;
		return;
	}
	// 有妻子
	if (Gen->lchild != NULL)
	{
		cout << Gen->data << '\t';
		GenNode *p = Gen->lchild; // 妻子
		while (p)
		{
			cout << p->data << '\t';
			p = p->rchild; // 孩子
		}
	}
	cout << endl;
	// 孩子当家作主，递归
	if (!Gen->lchild)
		return;
	GenNode *q = Gen->lchild->rchild;
	while (q)
	{
		PrintGen(q);
		q = q->rchild;
	}
}

// 查找
GenNode *Find(GenTree Gen, string name)
{
	if (!Gen) // 递归终止条件
		return NULL;

	if (Gen->data == name)
		return Gen;

	// 只有在左右孩子至少有一个存在时才访问
	if (Gen->lchild || Gen->rchild)
	{
		Find(Gen->lchild, name); // 递归调用
		Find(Gen->rchild, name); // 递归调用
	}
}

// 创建家庭
void CreateFamliy(GenNode *&F)
{
	// 父、母、孩子
	// 父左子为妻子；右子为孩子
	cout << "输入父母、孩子名字，空格分隔：";
	cin >> p1 >> p2 >> p3;
	GenTree father = new GenNode;
	GenNode *mother = new GenNode;
	GenNode *child = new GenNode;
	father->data = p1;
	mother->data = p2;
	child->data = p3;
	father->lchild = mother;
	father->rchild = NULL;
	mother->lchild = NULL;
	mother->rchild = child;
	child->lchild = NULL;
	child->rchild = NULL;
	F = father;
}

// 创建族谱
void CreateGen(GenTree Gen)
{
	// 祖先结点，父结点
	GenNode *famliy, *father;
	CreateFamliy(famliy);
	father = Find(Gen, famliy->data);
	// 没有找到
	if (!father)
	{
		cout << "没有祖先~" << endl;
		return;
	}
	// 如果没有左孩子，说明是没有老婆孩子
	// 下面添加老婆孩子
	if (!father->lchild)
		father->lchild = famliy->lchild;
	// 有老婆孩子，加二胎
	else
	{
		GenNode *p = father->lchild; // 妻子结点
		while (p->rchild)
			p = p->rchild;					// 一直找孩子
		p->rchild = famliy->lchild->rchild; // 孩子
	}
}

// 清空
void DestoryGen(GenTree Gen)
{
	if (!Gen)
		return;
	DestoryGen(Gen->lchild);
	DestoryGen(Gen->rchild);
	delete Gen;
	Gen = NULL;
}

// 文件保存
void SaveGen(GenTree Gen)
{
	if (!Gen)
	{
		ofs << "*" << " ";
		return;
	}
	ofs.open("data.txt", ios::app);
	if (!ofs.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}
	ofs << Gen->data << " ";
	ofs.close();
	SaveGen(Gen->lchild);
	SaveGen(Gen->rchild);
}

// 括号表示法打印
void BraPrintGen(GenTree Gen)
{
	if (!Gen) // 递归终止条件
		return;

	cout << Gen->data;

	// 只有在左右孩子至少有一个存在时才访问
	if (Gen->lchild || Gen->rchild)
	{
		cout << "(";			  // 要访问孩子时添加（
		BraPrintGen(Gen->lchild); // 递归调用
		cout << ",";			  // 访问完毕左孩子要访问右孩子时添加，
		BraPrintGen(Gen->rchild); // 递归调用
		cout << ")";			  // 访问完毕左右孩子添加）
	}
}

// 找到所有的孩子
bool ShowALLSon(GenTree Gen, string name)
{
	GenNode *q;
	GenNode *p = Find(Gen, name);
	if (!p)
	{
		cout << "查无此人" << endl;
		return false;
	}
	// 母亲
	if (!Gen->lchild)
	{
		q = p->rchild;
		cout << Gen->data << "母亲孩子是：";
		while (q)
		{
			cout << q->data << " ";
			q = q->rchild;
		}
		return true;
	}
	// 父亲
	p = p->lchild->rchild;
	cout << Gen->data << "父亲孩子是：";
	while (p)
	{
		cout << p->data << " ";
		p = p->rchild;
	}
	return true;
}

// 找到孩子所有祖先
bool ShowALLFather(GenTree Gen, string name)
{
	// 家谱空
	if (!Gen)
		return false;
	// 递归终止，这个路径递归找到了这个孩子
	if (Gen->data == name)
		return true;
	// 证明这个路径上的所有结点都是其祖先
	if (ShowALLFather(Gen->lchild, name) || ShowALLFather(Gen->rchild, name))
	{
		cout << Gen->data << " ";
		return true;
	}
	return false;
}

int main()
{
	string name;
	GenTree Gen = NULL; // 总家谱
	int flag = -1;
	int val1, val2, val3;
	while (true)
	{
		cout << endl;
		ShowMainMenu();
		cin >> val1;
		switch (val1)
		{
		case 1:
			ShowFMenu();
			cin >> val2;
			switch (val2)
			{
			// 家谱记录的输入
			case 1:
				if (flag == -1)
				{
					CreateFamliy(Gen);
					flag = 1;
				}
				else
					CreateGen(Gen);
				break;

			// 家谱记录的输出
			case 2:
				PrintGen(Gen);
				break;

			// 清除全部文件记录
			case 3:
				DestoryGen(Gen);
				break;

			// 将家谱记录存盘
			case 4:
				SaveGen(Gen);
				break;
			default:
				break;
			}
			break;
		case 2:
			ShowSMenu();
			cin >> val3;
			switch (val3)
			{
			// 括号表示法输出家谱
			case 1:
				BraPrintGen(Gen);
				break;
			// 查找某人的所有儿子
			case 2:
				cout << endl
					 << "请输入查找人姓名：";
				cin >> name;
				ShowALLSon(Gen, name);
				break;

			case 3:
				cout << endl
					 << "请输入查找人姓名：";
				cin >> name;
				ShowALLFather(Gen, name);
				break;
			}
			break;
		default:
			return 0;
		}
	}

	return 0;
}