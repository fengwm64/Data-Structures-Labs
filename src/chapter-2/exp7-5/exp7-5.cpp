#include <iostream>
using namespace std;

// 3、教材P248实验题5：构造哈夫曼树生成哈夫曼编码
// 编写一个程序exp7 - 5.cpp，构造一棵哈夫曼树，输出对应的哈夫曼编码和平均查找长度，并对下表（表7.8）所示的数据进行验证。

#pragma warning(disable : 4996)

// 哈夫曼树数据域字符长度
#define StrLen 5

// 哈夫曼树定义
typedef struct
{
	char data[StrLen];			// 数据域
	int weight;					// 结点权值
	int parent, lchild, rchild; // 结点的父结点、左孩子、右孩子下标
} HTNode, *HuffmanTree;

// 所用接口声明
void CreateHT(HuffmanTree HT, int Weight[], int n);		 // 构造哈夫曼树
void PrintHT(HuffmanTree HT, int n);					 // 打印哈夫曼树数组
void HFCodeing(HuffmanTree HT, char *HFCode[], int n);	 // 生成哈夫曼编码
void PrintHTCode(char *HFCode[], HuffmanTree HT, int n); // 打印哈夫曼编码
int NodeWPL(HuffmanTree HT, int i);						 // 求该结点的带权路径值，权*根结点到该结点路径长
int GetWPL(HuffmanTree HT, int n);						 // 求哈夫曼树的平均查找长度WPL

int main()
{
	int n = 15;
	char **HFCode = new char *[n];
	int Weight[] = {1192, 677, 541, 518, 462, 450, 242, 195, 190, 181, 174, 157, 138, 124, 123};
	const char *data[15] = {"The", "of", "a", "to", "and", "in", "that", "he", "is", "at", "on", "for", "His", "are", "be"};
	// 申请哈夫曼树的空间
	HuffmanTree HT = new HTNode[2 * n - 1];
	// 结点数据域赋值
	for (int i = 0; i < n; i++)
		strcpy_s(HT[i].data, data[i]);

	cout << "1.根据表格数据构造哈夫曼树如下：" << endl;
	CreateHT(HT, Weight, n);
	PrintHT(HT, n);

	cout << "2.输出对应的哈夫曼编码如下：" << endl;
	HFCodeing(HT, HFCode, n);
	PrintHTCode(HFCode, HT, n);

	cout << endl
		 << "3.输出平均查找长度：" << GetWPL(HT, n) << endl;
	return 0;
}

// 构造哈夫曼树
// 哈夫曼树、权值、节点数量
void CreateHT(HuffmanTree HT, int Weight[], int n)
{
	int i1, i2;		// i1,i2表示最小权值的两个结点下标
	int min1, min2; // min1,min2表示两个最小权值
	// 初始化哈夫曼树
	for (int i = 0; i < 2 * n - 1; i++)
	{
		HT[i].lchild = -1;
		HT[i].rchild = -1;
		HT[i].parent = -1;
	}

	// 初始结点按给定权值赋值
	for (int i = 0; i < n; i++)
		HT[i].weight = Weight[i];

	// k实际上为选取两个节点组成新树的根储存在数组的下标
	for (int k = n; k < 2 * n - 1; k++)
	{
		// 寻找没有父结点的两个权值最小的结点下标
		// 每次查找重置下标；min1=min2=int类型下最大值
		i1 = i2 = 0;
		min1 = min2 = 2147483647;
		// i是一个遍历哈夫曼数组的下标变量，此循环中k-1为循环次数
		for (int i = 0; i < k; i++)
		{
			// 先判断是否有父结点
			if (HT[i].parent == -1)
			{
				if (HT[i].weight < min1)
				{
					swap(min1, min2);
					swap(i1, i2);
					min1 = HT[i].weight;
					i1 = i;
				}
				else if (HT[i].weight < min2)
				{
					min2 = HT[i].weight;
					i2 = i;
				}
			}
		}
		// 找到两个最小下标后，组成新树
		// 新树的权值=两最小结点权值和
		HT[k].weight = min1 + min2;
		//-------父亲有了孩子~~-------
		HT[k].lchild = i1;
		HT[k].rchild = i2;
		//-------孩子有了父亲~~-------
		HT[i1].parent = k;
		HT[i2].parent = k;
	}
}

// 打印哈夫曼树数组
void PrintHT(HuffmanTree HT, int n)
{
	cout << "weight" << '\t';
	cout << "parent" << '\t' << "lchild" << '\t' << "rchild" << '\t' << "data" << endl;
	for (int i = 0; i < 2 * n - 1; i++)
	{
		cout << HT[i].weight << '\t';
		cout << HT[i].parent << '\t';
		cout << HT[i].lchild << '\t';
		cout << HT[i].rchild << '\t';
		if (i < n)
			cout << HT[i].data << endl;
		else
			cout << "空" << endl;
	}
	cout << endl;
}

// 生成哈夫曼编码
void HFCodeing(HuffmanTree HT, char *HFCode[], int n)
{
	// 用于从叶子向上查找
	// 当前位置，父结点位置
	int pos, parent;

	// 哈夫曼编码临时空间
	// 最深叶子结点到根结点边数=n
	char *temp = new char[n];
	temp[n - 1] = '\0';

	// 哈夫曼编码临时空间工作下标
	int start;

	// 遍历哈夫曼树数组
	for (int i = 0; i < n; i++)
	{
		// 因为从叶子到根，所以编码录入也得倒着来
		start = n - 1;
		// 初始化两个工作指针
		parent = HT[i].parent;
		pos = i;
		// 直到找到根
		while (parent != -1)
		{
			// 判断pos是parent左子树还是右子树
			if (HT[parent].lchild == pos)
				temp[--start] = '0';
			else
				temp[--start] = '1';
			// 树指针向上移动
			pos = parent;
			parent = HT[parent].parent;
		}
		// 第i个结点编码完毕
		// n-start为编码长度
		HFCode[i] = new char[n - start];
		// 从临时工作空间里拷贝
		strcpy(HFCode[i], &temp[start]);
	}
	delete[] temp;
}

// 打印哈夫曼编码
void PrintHTCode(char *HFCode[], HuffmanTree HT, int n)
{
	for (int i = 0; i < n; i++)
		cout << HT[i].data << '\t' << HFCode[i] << endl;
}

// 求该结点的带权路径值，权*根结点到该结点路径长
int NodeWPL(HuffmanTree HT, int i)
{
	HTNode *Node = &HT[i];
	int depth = 0;
	// 用于从叶子向上查找
	// 当前位置，父结点位置
	int pos = i;
	int parent = HT[pos].parent;

	// 遍历哈夫曼树数组
	while (parent != -1)
	{
		pos = parent;
		parent = HT[parent].parent;
		depth++;
	}
	return depth * Node->weight;
}

// 求哈夫曼树的平均查找长度WPL
int GetWPL(HuffmanTree HT, int n)
{
	int wpl = 0;
	for (int i = 0; i < n; i++)
		wpl += NodeWPL(HT, i);
	return wpl;
}