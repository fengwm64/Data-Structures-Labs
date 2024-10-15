#include <iostream>
using namespace std;

#define MaxVertex 10		// 顶点数目的最大值
#define INFINITY 2147483647 // 无穷
typedef int VertexType;		// 顶点的数据类型
typedef int EdgeType;		// 带权图边权值的数据类型

/////////////////////////以下为结构体定义/////////////////////////

// 为了便捷使用，定义一个结构体来输入图
struct GraphInfo
{
	int Vex1;	// 起点
	int Vex2;	// 终点
	int Weight; // 权值
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
	int MiniEdge(ShortEdge *SE);
	void OutputSMT(ShortEdge *SE, int k);
	void Prim(int start);

private:
	VertexType Vex[MaxVertex];			 // 顶点表
	EdgeType Edge[MaxVertex][MaxVertex]; // 邻接矩阵，边表
	int VexNum;							 // 当前顶点数
	int ArcNum;							 // 当前弧数
};

/////////////////////////以下为函数实现/////////////////////////

// 构造
MGraph::MGraph(VertexType *V, const GraphInfo *GI, int n, int e)
{
	// 根据V[]初始化顶点信息与访问标记数组
	for (int j = 0; j < n; j++)
		this->Vex[j] = j;
	// 初始化图的顶点数和弧数
	this->VexNum = n;
	this->ArcNum = e;
	// 初始化图邻接矩阵
	for (int i = 0; i < n; i++)
		for (int k = 0; k < n; k++)
			this->Edge[i][k] = INFINITY;
	// 根据输入图的边，构造无向图邻接矩阵
	for (int j = 0; j < e; j++)
	{
		this->Edge[GI[j].Vex1][GI[j].Vex2] = GI[j].Weight;
		this->Edge[GI[j].Vex2][GI[j].Vex1] = GI[j].Weight;
	}
}
void MGraph::PrintMGraph()
{
	cout << endl
		 << "输出图的邻接矩阵如下：" << endl;
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
}
// 在辅助数组内寻找最小权值的边
int MGraph::MiniEdge(ShortEdge *SE)
{
	int min = -1;
	int mincost = INFINITY;
	for (int i = 0; i < this->VexNum; i++)
	{
		// 节点没有加入U且有边
		if (SE[i].lowcost != 0 && SE[i].lowcost != INFINITY)
		{
			if (mincost > SE[i].lowcost)
			{
				// 更新最小值
				mincost = SE[i].lowcost;
				// 记录下标
				min = i;
			}
		}
	}
	return min;
}
// 输出上函数中找到的最小边
void MGraph::OutputSMT(ShortEdge *SE, int k)
{
	cout << "(" << SE[k].adjvex << "," << k << ") " << SE[k].lowcost << endl;
}
// Prim算法求最小生成树
void MGraph::Prim(int start)
{
	int k = -1;
	// 初始化辅助数组SE
	ShortEdge *SE = new ShortEdge[VexNum];
	for (int i = 0; i < VexNum; i++)
	{
		SE[i].adjvex = start;
		SE[i].lowcost = Edge[start][i];
	}
	// 起点srtart加入集合U
	// ！！！加入集合U标志为lowcost=0
	SE[start].lowcost = 0;
	for (int i = 0; i < VexNum - 1; i++)
	{
		// 在U与V-U之间查找权值最小的边，k为边所连接顶点
		k = MiniEdge(SE);
		// 打印输出这一条边
		OutputSMT(SE, k);
		// 把顶点加入集合U
		SE[k].lowcost = 0;
		// 接下来在在U与V-U之间查找权值最小的边
		// 需要同时考虑在U里的所有结点与U-V结点的关系
		// 假设现在lowcost初始化后无改动
		// 将现在的SE数组里的lowcost与新加入节点k所有邻接边权值比较
		// 将较小的权值替换到SE数组的lowcost中去
		// 这样下一次循环只要MiniEdge(SE)就可以找到U内最小权值的新边k
		// 每次循环都这样做，将k与lowcost比较替换
		for (int j = 0; j < VexNum; j++)
		{
			if (SE[j].lowcost > Edge[k][j])
			{
				// 更改邻接顶点域
				// 表示是集合U内顶点到k这个顶点的最小权值
				SE[j].adjvex = k;
				// 将较小的权值替换到SE数组的lowcost
				SE[j].lowcost = Edge[k][j];
			}
		}
	}
}

/////////////////////////////main///////////////////////////////
int main()
{
	const GraphInfo Graph8_55[10] = {{0, 1, 5}, {1, 2, 4}, {3, 2, 5}, {4, 3, 5}, {5, 4, 1}, {5, 0, 3}, {2, 0, 8}, {0, 3, 7}, {3, 5, 6}, {2, 5, 9}};
	VertexType Vex[MaxVertex] = {0, 1, 2, 3, 4, 5}; // 顶点表
	cout << "采用Prim算法求图8.5.5从顶点0开始的最小生成树" << endl;
	MGraph MG(Vex, Graph8_55, 6, 10); // 建立邻接矩阵图MG
	MG.PrintMGraph();
	cout << endl
		 << "最小生成树：" << endl;
	MG.Prim(0);
	return 0;
}
