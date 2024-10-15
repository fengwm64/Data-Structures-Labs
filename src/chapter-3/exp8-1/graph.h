// graph.h
#define MaxVertex 100		// 顶点数目的最大值
#define INFINITY 2147483647 // 无穷
typedef int VertexType;		// 顶点的数据类型
typedef int EdgeType;		// 带权图边权值的数据类型

// -------------- 邻接矩阵表示法 --------------
class MGraph
{
public:
	MGraph(VertexType *Vex, int n, int e);
	void PrintMGraph();

private:
	VertexType Vex[MaxVertex];			 // 顶点表
	EdgeType Edge[MaxVertex][MaxVertex]; // 邻接矩阵，边表
	int VexNum;							 // 当前顶点数
	int ArcNum;							 // 当前弧数
};

// -------------- 邻接表表示法 --------------
// 边表结点
typedef struct ArcNode
{
	int adjvex;			  // 邻接点域
	EdgeType weight;	  // 边的权重
	struct ArcNode *next; // 指针域
} ArcNode;
// 顶点表结点
typedef struct VertxNode
{
	VertexType data; // 顶点域
	ArcNode *first;	 // 边表的头指针
} VNode, AdjList[MaxVertex];
// 邻接表储存的图
class ALGraph
{
public:
	ALGraph(VertexType *Vex, int n, int e);
	~ALGraph();
	void PrintALG();

private:
	AdjList vertices; // 邻接表
	int VexNum;		  // 当前顶点数
	int ArcNum;		  // 当前弧数
};