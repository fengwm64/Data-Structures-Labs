// travsal.h
//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////以下为图内容/////////////////////////////////////
// 为精简报告长度，栈、队列具体实现不添加进报告（因为非主要内容）
// 在程序源代码中提供

#pragma once
#include <iostream>
#include "linkstack.h"
#include "sqqueue.h"
using namespace std;

#define MaxVertex 10		// 顶点数目的最大值
#define INFINITY 2147483647 // 无穷
typedef int VertexType;		// 顶点的数据类型
typedef int EdgeType;		// 带权图边权值的数据类型

// 为了便捷使用，定义一个结构体来输入图
struct GraphInfo
{
	int Vex1;	// 起点
	int Vex2;	// 终点
	int Weight; // 权值
};

// -------------- 邻接矩阵表示法 --------------
class MGraph
{
public:
	MGraph(VertexType *V, const GraphInfo *GI, int n, int e);
	void DFS(int v);
	void DFSTraverse();
	void DFSTraverse_NoRa(int v);
	void BFSTraverse(int v);

private:
	VertexType Vex[MaxVertex];			 // 顶点表
	EdgeType Edge[MaxVertex][MaxVertex]; // 邻接矩阵，边表
	bool Visited[MaxVertex];			 // 访问标记数组
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
	ALGraph(VertexType *Vex, const GraphInfo *GI, int n, int e);
	~ALGraph();
	void DFS(int v);
	void DFSTraverse();
	void DFSTraverse_NoRa(int v);
	void BFSTraverse(int v);

private:
	AdjList vertices;		 // 邻接表
	bool Visited[MaxVertex]; // 访问标记数组
	int VexNum;				 // 当前顶点数
	int ArcNum;				 // 当前弧数
};