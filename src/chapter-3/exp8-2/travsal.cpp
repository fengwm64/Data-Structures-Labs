// travsal.cpp
#include "travsal.h"
#include <iostream>
using namespace std;

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////以下为图实现/////////////////////////////////////

// -------------- 邻接矩阵表示法 --------------
// 图邻接矩阵的构造函数
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
	// 根据输入图的边，构造邻接矩阵
	for (int j = 0; j < e; j++)
		this->Edge[GI[j].Vex1][GI[j].Vex2] = GI[j].Weight;
}
// 连通图（连通分量）的邻接矩阵的深度优先遍历	[递归]
void MGraph::DFS(int v)
{
	// 访问该顶点
	cout << Vex[v] << " ";
	// 标记为已访问
	Visited[v] = true;
	// 查看是否有邻接顶点没有访问的
	for (int i = 0; i < VexNum; i++)
	{
		// 如果存在邻接顶点i
		if (Edge[v][i] != INFINITY)
		{
			// 查看访问标记
			// 如果没有被访问过
			if (!Visited[i])
				DFS(i);
		}
	}
}
// 图的邻接矩阵的深度优先遍历(非连通图也可以)	[递归]
void MGraph::DFSTraverse()
{
	// 重置访问标记
	for (int i = 0; i < VexNum; i++)
		Visited[i] = false;
	// 深度优先遍历
	// 当访问标记数组存在false时一直调用DFS()
	// 这样可以保证每个图的每个连通分量都可以遍历到
	// 这里是从顶点0开始深度优先遍历
	for (int i = 0; i < VexNum; i++)
		if (!Visited[i])
			DFS(i);
}
// 图的邻接矩阵的深度优先遍历		[非递归]
void MGraph::DFSTraverse_NoRa(int v)
{
	// 初始化辅助栈
	LinkStack S;
	InitStack(S);
	// 重置访问标记
	for (int i = 0; i < VexNum; i++)
		Visited[i] = false;
	Push(S, v);
	Visited[v] = true;
	while (!StackEmpty(S))
	{
		// 出栈
		Pop(S, v);
		// 访问
		cout << Vex[v] << " ";
		// 寻找邻接顶点
		for (int i = 0; i < VexNum; i++)
		{
			// 如果是邻接顶点
			if (Edge[v][i] != INFINITY)
			{
				// 看看有没有被访问
				if (!Visited[i])
				{
					Push(S, i);
					Visited[i] = true;
				}
			}
		}
	}
	DestoryStack(S);
}
// 图的邻接矩阵的广度优先遍历
void MGraph::BFSTraverse(int v)
{
	// 初始化辅助队列
	SqQueue Q;
	InitQueue(Q);
	// 初始化访问标记数组
	for (int i = 0; i < VexNum; i++)
		Visited[i] = false;
	// 访问
	cout << Vex[v] << " ";
	Visited[v] = true;
	// 入队
	EnQueue(Q, v);
	// 当队列非空时
	while (!QueueEmpty(Q))
	{
		// 队头出队
		DeQueue(Q, v);
		// 找队头的第一个邻接点
		for (int i = 0; i < VexNum; i++)
		{
			// !=INFINITY说明有边
			if (Edge[v][i] != INFINITY)
			{
				// 没被访问过就访问一下
				if (!Visited[i])
				{
					cout << Vex[i] << " ";
					Visited[i] = true;
					// 入队
					// 等该“层”都入队了
					// 再通过队列访问下一层
					EnQueue(Q, i);
				}
			}
		}
	}
	DestroyQueue(Q);
}

// -------------- 邻接表表示法 --------------
// 图邻接表的构造函数
ALGraph::ALGraph(VertexType *Vex, const GraphInfo *GI, int n, int e)
{
	this->ArcNum = e;
	this->VexNum = n;
	// 初始化邻接表与访问标记数组
	for (int i = 0; i < n; i++)
	{
		this->vertices[i].data = Vex[i];
		this->vertices[i].first = NULL;
		this->Visited[i] = false;
	}
	// 根据输入图的边，构造邻接表
	for (int j = 0; j < e; j++)
	{
		ArcNode *s = new ArcNode;
		s->adjvex = GI[j].Vex2;
		s->weight = GI[j].Weight;
		// 前插法
		s->next = vertices[GI[j].Vex1].first;
		vertices[GI[j].Vex1].first = s;
	}
}
// 图邻接表的析构函数
ALGraph::~ALGraph()
{
	ArcNode *q = NULL; // 前驱工作指针
	ArcNode *p = NULL; // 后驱工作指针
	for (int i = 0; i < VexNum; i++)
	{
		p = q = vertices[i].first;
		while (p)
		{
			q = p;
			p = p->next;
			delete q;
		}
		vertices[i].data = -1;
	}
	VexNum = 0;
	ArcNum = 0;
	cout << endl
		 << endl
		 << "邻接表销毁已完成！" << endl;
}
// 连通图（连通分量）的邻接表的深度优先遍历
void ALGraph::DFS(int v)
{
	ArcNode *p = NULL;
	// 访问该顶点
	cout << vertices[v].data << " ";
	// 标记为已访问
	Visited[v] = true;
	// 查看邻接顶点
	p = vertices[v].first;
	while (p)
	{
		// 如果存在邻接顶点p->adjvex
		// 查看访问标记
		// 如果没有被访问过,就递归访问
		if (!Visited[p->adjvex])
			DFS(p->adjvex);
		p = p->next;
	}
}
// 图的邻接表的深度优先遍历（非连通图也可以）
void ALGraph::DFSTraverse()
{
	// 重置访问标记
	for (int i = 0; i < VexNum; i++)
		Visited[i] = false;
	// 深度优先遍历
	// 当访问标记数组存在false时一直调用DFS()
	// 这样可以保证每个图的每个连通分量都可以遍历到
	// 这里是从顶点0开始深度优先遍历
	for (int i = 0; i < VexNum; i++)
		if (!Visited[i])
			DFS(i);
}
// 图的邻接表的深度优先遍历		[非递归]
void ALGraph::DFSTraverse_NoRa(int v)
{
	// 工作指针
	ArcNode *p = NULL;
	// 初始化辅助栈
	LinkStack S;
	InitStack(S);
	// 重置访问标记
	for (int i = 0; i < VexNum; i++)
		Visited[i] = false;
	Push(S, v);
	Visited[v] = true;
	while (!StackEmpty(S))
	{
		// 出栈
		Pop(S, v);
		// 访问
		cout << vertices[v].data << " ";
		// 寻找邻接顶点
		p = vertices[v].first;
		while (p)
		{
			// 看看有没有被访问
			if (!Visited[p->adjvex])
			{
				Push(S, p->adjvex);
				Visited[p->adjvex] = true;
			}
			p = p->next;
		}
	}
	DestoryStack(S);
}
// 图的邻接表的广度优先遍历
void ALGraph::BFSTraverse(int v)
{
	// 工作指针
	ArcNode *p = NULL;
	// 初始化辅助队列
	SqQueue Q;
	InitQueue(Q);
	// 初始化访问标记数组
	for (int i = 0; i < VexNum; i++)
		Visited[i] = false;
	// 访问
	cout << vertices[v].data << " ";
	Visited[v] = true;
	// 入队
	EnQueue(Q, v);
	// 当队列非空时
	while (!QueueEmpty(Q))
	{
		// 队头出队
		DeQueue(Q, v);
		// 找队头的第一个邻接点
		p = vertices[v].first;
		while (p)
		{
			// 如果没有访问过
			if (!Visited[p->adjvex])
			{
				// 访问
				cout << vertices[p->adjvex].data << " ";
				Visited[p->adjvex] = true;
				// 入队
				EnQueue(Q, p->adjvex);
			}
			p = p->next;
		}
	}
	DestroyQueue(Q);
}