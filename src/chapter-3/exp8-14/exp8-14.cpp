#include <iostream>
using namespace std;

#define M 6						  // 迷宫矩阵行数
#define N 6						  // 迷宫矩阵列数
#define MaxSize (M - 2) * (N - 2) // 顶点数目的最大值

bool Visited[MaxSize] = {}; // 访问标记数组

// 点坐标表示
struct Point
{
	int row = -1;	 // 行号
	int column = -1; // 列号
};
// 边表结点
typedef struct ArcNode
{
	int adjvex;			  // 邻接点坐标域
	struct ArcNode *next; // 指针域
} ArcNode;
// 顶点表结点
typedef struct VertxNode
{
	Point data;		// 顶点坐标域
	ArcNode *first; // 边表的头指针
} VNode, AdjList[MaxSize];
// 邻接表储存的图
class ALGraph
{
public:
	ALGraph(const int mz[M][N]);
	~ALGraph();
	void PrintALG();
	bool IsNeighbour(const int mz[M][N], Point &p, int direct);
	int FindPoint(const int mz[M][N], Point p);
	void AddArc(int count, int arc);
	void FindPath(int start, int end, int depth = -1);

private:
	AdjList vertices; // 邻接表
	int VexNum;		  // 当前顶点数
};

// 由迷宫矩阵构造图的邻接表
ALGraph::ALGraph(const int mz[M][N])
{
	Point temp;
	// 邻接表的下标
	int count = 0;
	// 初始化邻接表
	// 实际上就是在给可以走的点编号
	for (int i = 0; i < MaxSize; i++)
		vertices[i].first = NULL;

	for (int i = 1; i < M - 1; i++)
		for (int j = 1; j < N - 1; j++)
			if (mz[i][j] == 0)
			{
				// 邻接表顶点信息记录迷宫矩阵坐标
				vertices[count].data.row = i;
				vertices[count++].data.column = j;
			}

	VexNum = count;
	count = 0;
	// 遍历迷宫矩阵生成
	// i行j列进行矩阵遍历
	for (int i = 1; i < M - 1; i++)
	{
		for (int j = 1; j < N - 1; j++)
		{
			// 如果路可以走
			if (mz[i][j] == 0)
			{
				// 开始建立边表
				// 在一个迷宫中一个顶点最多有4条边，分别是上下左右
				// 搜索上下左右
				for (int k = 0; k < 4; k++)
				{
					temp.row = i;
					temp.column = j;
					// 可达就添加边表
					if (IsNeighbour(mz, temp, k))
						AddArc(count, FindPoint(mz, temp));
				}
				count++;
			}
		}
	}
}
// 图邻接表的析构函数
ALGraph::~ALGraph()
{
	ArcNode *q = NULL; // 前驱工作指针
	ArcNode *p = NULL; // 后驱工作指针
	for (int i = 0; i < VexNum; i++)
	{
		Point temp = {-1, -1};
		p = q = vertices[i].first;
		while (p)
		{
			q = p;
			p = p->next;
			delete q;
		}
		vertices[i].data = temp;
	}
	VexNum = 0;
}
// 打印邻接表
void ALGraph::PrintALG()
{
	ArcNode *p = NULL; // 工作指针
	cout << "输出图的邻接表如下：" << endl;
	for (int i = 0; i < VexNum; i++)
	{
		cout << "[" << i << "] ";
		cout << "(" << vertices[i].data.row << " ,";
		cout << vertices[i].data.column << ")：";
		p = vertices[i].first;
		while (p)
		{
			cout << "(" << vertices[p->adjvex].data.row << ", ";
			cout << vertices[p->adjvex].data.column << ") ";
			p = p->next;
		}
		cout << endl;
	}
}
// 根据迷宫坐标查找邻接表的下标
int ALGraph::FindPoint(const int mz[M][N], Point p)
{
	for (int j = 0; j < MaxSize; j++)
		if (vertices[j].data.row == p.row && vertices[j].data.column == p.column)
			return j;
}
// 在编号为count的邻接表中添加一条到arc的边
void ALGraph::AddArc(int count, int arc)
{
	ArcNode *s = new ArcNode;
	s->adjvex = arc;
	s->next = vertices[count].first;
	vertices[count].first = s;
}
// 查找在坐标p的上下左右是否可达
// direct：0右，1下，2左，3上
bool ALGraph::IsNeighbour(const int mz[M][N], Point &p, int direct)
{
	switch (direct)
	{
	case 0: // 右
		p.column += 1;
		break;
	case 1: // 下
		p.row += 1;
		break;
	case 2: // 左
		p.column -= 1;
		break;
	case 3: // 上
		p.row -= 1;
		break;
	}
	if (!mz[p.row][p.column])
		return true;
	else
		return false;
}
// 连通图（连通分量）的邻接表的深度优先遍历
void ALGraph::FindPath(int start, int end, int depth)
{
	ArcNode *p = NULL;
	static Point path[MaxSize] = {};
	depth++;
	// 访问start
	path[depth] = vertices[start].data;
	Visited[start] = true;
	// 采用深度优先遍历，递归
	// 递归终止条件
	if (start == end)
	{
		// 输出路径
		for (int i = 0; i < depth + 1; i++)
		{
			cout << "(" << path[i].row << ", ";
			cout << path[i].column << ")";
			if (i != depth)
				cout << "->";
			else
				cout << endl;
		}
		Visited[start] = false;
		return;
	}
	// 查看start有没有邻接顶点
	p = vertices[start].first;
	while (p)
	{
		if (!Visited[p->adjvex])
			FindPath(p->adjvex, end, depth);
		p = p->next;
	}
	// 回溯的时候消除start访问标记
	Visited[start] = false;
}

int main()
{
	// 迷宫矩阵
	// 1表示障碍物，0反之
	Point startPoint = {1, 1};
	Point endPoint = {M - 2, N - 2};
	const int maze[M][N] = {
		{1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1, 1},
		{1, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 1, 1},
		{1, 1, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1}};

	ALGraph MZGraph(maze);
	cout << "（1）建立一个迷宫对应的邻接表表示" << endl;
	MZGraph.PrintALG();
	int start = MZGraph.FindPoint(maze, startPoint);
	int end = MZGraph.FindPoint(maze, endPoint);
	cout << endl
		 << "（2）采用深度优先遍历算法输出从入口（1，1）到出口（M,N）的所有迷宫路径。\n";
	MZGraph.FindPath(start, end);
	return 0;
}
