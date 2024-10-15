#include <iostream>
using namespace std;

#define MaxVertex 10	// 顶点数目的最大值
#define INFINITY 21474	// 无穷
typedef int VertexType; // 顶点的数据类型
typedef int EdgeType;	// 带权图边权值的数据类型

/////////////////////////以下为结构体定义/////////////////////////

// 为了便捷使用，定义一个结构体来输入图
struct GraphInfo
{
	int Vex1;		// 起点
	int Vex2;		// 终点
	int Weight = 1; // 权值
};
// 最小生成树的辅助数组结构
struct ShortEdge
{
	int lowcost; // 边的权值
	int adjvex;	 // 邻接顶点
};
//  邻接矩阵表示法
class MGraph
{
public:
	MGraph(VertexType *V, const GraphInfo *GI, int n, int e);
	void PrintMGraph();
	void EmptyVisited();
	void FindPath(int start, int end, int depth = -1);
	void FindLenPath(int start, int end, int len, int depth = -1);
	void Floyd(int start, int end);

private:
	VertexType Vex[MaxVertex];			 // 顶点表
	EdgeType Edge[MaxVertex][MaxVertex]; // 邻接矩阵，边表
	bool Visited[MaxVertex];			 // 访问标记数组
	int VexNum;							 // 当前顶点数
	int ArcNum;							 // 当前弧数
};

/////////////////////////以下为函数实现/////////////////////////

// 构造
MGraph::MGraph(VertexType *V, const GraphInfo *GI, int n, int e)
{
	// 根据V[]初始化顶点信息与访问标记数组
	for (int j = 0; j < n; j++)
	{
		this->Vex[j] = j;
		this->Visited[j] = false;
	}
	// 初始化图的顶点数和弧数
	this->VexNum = n;
	this->ArcNum = e;
	// 初始化图邻接矩阵
	for (int i = 0; i < n; i++)
		for (int k = 0; k < n; k++)
			this->Edge[i][k] = INFINITY;
	// 根据输入图的边，构造无向图邻接矩阵
	for (int j = 0; j < e; j++)
		this->Edge[GI[j].Vex1][GI[j].Vex2] = GI[j].Weight;
}
void MGraph::PrintMGraph()
{
	for (int i = 0; i < this->VexNum; i++)
	{
		for (int k = 0; k < this->VexNum; k++)
		{
			if (this->Edge[i][k] == INFINITY)
				cout << "∞\t";
			else
				cout << this->Edge[i][k] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}
void MGraph::EmptyVisited()
{
	for (int j = 0; j < VexNum; j++)
		this->Visited[j] = false;
}
void MGraph::FindPath(int start, int end, int depth)
{
	static int path[MaxVertex] = {};
	depth++;
	// 访问start
	path[depth] = start;
	Visited[start] = true;
	// 采用深度优先遍历，递归
	// 递归终止条件
	if (start == end)
	{
		// 输出路径
		for (int i = 0; i < depth + 1; i++)
		{
			cout << path[i];
			if (i != depth)
				cout << " -> ";
			else
				cout << endl;
		}
		Visited[start] = false;
		return;
	}
	// 查看start有没有邻接顶点
	for (int i = 0; i < VexNum; i++)
	{
		if (Edge[start][i] != INFINITY)
		{
			if (!Visited[i])
				FindPath(i, end, depth);
		}
	}
	// 回溯的时候消除start访问标记
	Visited[start] = false;
}
void MGraph::FindLenPath(int start, int end, int len, int depth)
{
	static int path[MaxVertex] = {};
	depth++;
	// 访问start
	path[depth] = start;
	Visited[start] = true;
	// 采用深度优先遍历，递归
	// 递归终止条件，递归深度=长度-1
	if (depth > len - 1)
	{
		Visited[start] = false;
		return;
	}
	// start=end找到了
	if (start == end)
	{
		// 输出路径
		for (int i = 0; i < depth + 1; i++)
		{
			cout << path[i];
			if (i != depth)
				cout << " -> ";
			else
				cout << endl;
		}
		// 找到了
		// 回溯的时候消除start访问标记
		Visited[start] = false;
		return;
	}
	// 查看start有没有邻接顶点
	for (int i = 0; i < VexNum; i++)
	{
		if (Edge[start][i] != INFINITY)
		{
			if (!Visited[i])
				FindLenPath(i, end, len, depth);
		}
	}
	// 这里是找完这个顶点的所有路径了，要回溯了
	// 回溯的时候消除start访问标记
	Visited[start] = false;
}
void MGraph::Floyd(int start, int end)
{
	// 存储两个点之间最短路径的长度信息
	VertexType A[MaxVertex][MaxVertex];
	// 存储两个点之间最短路径的信息（经谁中转）
	VertexType path[MaxVertex][MaxVertex];
	// 初始化path和数组A
	for (int i = 0; i < VexNum; i++)
	{
		for (int k = 0; k < VexNum; k++)
		{
			A[i][k] = Edge[i][k];
			path[i][k] = -1;
		}
	}
	// 外层循环表示添加一个顶点Vi作为中转
	for (int i = 0; i < VexNum; i++)
	{
		// 内层双循环用来遍历整个矩阵
		for (int j = 0; j < VexNum; j++)
		{
			for (int k = 0; k < VexNum; k++)
			{
				// 当A里的值已经不是最短路径时
				// 更新为通过中转点Vi的路径长
				// ！！！这里体现的是迭代的思想
				// A里的值永远保持最优（这里和最小生成树的算法非常像）
				if (A[j][k] > Edge[j][i] + Edge[i][k])
				{
					// 更新A[][]~
					A[j][k] = Edge[j][i] + Edge[i][k];
					// 在path里说明是通过谁中转的
					path[j][k] = i;
				}
			}
		}
	}
	cout << start << " -> ";
	if (path[start][end] != -1)
		cout << path[start][end] << " -> ";
	cout << end << endl;
}

/////////////////////////////main///////////////////////////////
int main()
{
	const GraphInfo Graph8_56[12] = {{0, 1}, {1, 2}, {3, 2}, {4, 3}, {5, 4}, {5, 0}, {2, 0}, {0, 3}, {3, 5}, {2, 5}, {5, 1}, {5, 3}};
	VertexType Vex[MaxVertex] = {0, 1, 2, 3, 4, 5}; // 顶点表
	MGraph G(Vex, Graph8_56, 6, 12);				// 建立邻接矩阵图G
	cout << "（0）输出图8.56的邻接矩阵" << endl;
	G.PrintMGraph();
	cout << "（1）输出如图8.56的有向图G从顶点5到顶点2的所有简单路径" << endl;
	G.FindPath(5, 2);
	cout << endl
		 << "（2）输出如图8.56的有向图G从顶点5到顶点2的所有长度为3的简单路径" << endl;
	G.FindLenPath(5, 2, 3);
	cout << endl
		 << "（3）输出如图8.56的有向图G从顶点5到顶点2的最短路径" << endl;
	G.Floyd(5, 2);
	return 0;
}