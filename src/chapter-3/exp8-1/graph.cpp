// graph.cpp
#include "graph.h"
#include <iostream>
using namespace std;

// -------------- 邻接矩阵表示法 --------------
MGraph::MGraph(VertexType *V, int n, int e)
{
	int val1, val2, weight;
	// 根据V[]初始化顶点信息
	for (int j = 0; j < n; j++)
		this->Vex[j] = j;
	// 初始化图的顶点数和弧数
	this->VexNum = n;
	this->ArcNum = e;
	// 初始化图邻接矩阵
	for (int i = 0; i < n; i++)
		for (int k = 0; k < n; k++)
			this->Edge[i][k] = INFINITY;
	// 输入图的边，构造邻接矩阵
	cout << "请输入（格式如下，Tab分隔）：" << endl;
	cout << "顶点1\t顶点2\t权值" << endl;
	for (int j = 0; j < e; j++)
	{
		cin >> val1 >> val2 >> weight;
		this->Edge[val1][val2] = weight;
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

// -------------- 邻接表表示法 --------------
ALGraph::ALGraph(VertexType *Vex, int n, int e)
{
	int val1, val2, val3;
	this->ArcNum = e;
	this->VexNum = n;
	// 初始化邻接表
	for (int i = 0; i < n; i++)
	{
		this->vertices[i].data = Vex[i];
		this->vertices[i].first = NULL;
	}
	// 输入图的边，构造邻接表
	cout << "请输入（格式如下，Tab分隔）：" << endl;
	cout << "顶点1\t顶点2\t权值" << endl;
	for (int j = 0; j < e; j++)
	{
		cin >> val1 >> val2 >> val3;
		ArcNode *s = new ArcNode;
		s->adjvex = val2;
		s->weight = val3;
		// 前插法
		s->next = vertices[val1].first;
		vertices[val1].first = s;
	}
}
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
	cout << "销毁已完成！" << endl;
}
void ALGraph::PrintALG()
{
	ArcNode *p = NULL; // 工作指针
	cout << endl
		 << "输出图的邻接表如下：" << endl;
	for (int i = 0; i < VexNum; i++)
	{
		cout << vertices[i].data << "：";
		p = vertices[i].first;
		while (p)
		{
			cout << p->adjvex << "(" << p->weight << ")  ";
			p = p->next;
		}
		cout << endl;
	}
}