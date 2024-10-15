// exp8-2.cpp
#include <iostream>
#include "travsal.h"
using namespace std;

int main()
{
	const GraphInfo Graph8_54[10] = {{0, 1, 5}, {1, 2, 4}, {3, 2, 5}, {4, 3, 5}, {5, 4, 1}, {5, 0, 3}, {2, 0, 8}, {0, 3, 7}, {3, 5, 6}, {2, 5, 9}};
	VertexType Vex[MaxVertex] = {0, 1, 2, 3, 4, 5}; // 顶点表
	cout << "（0）建立图，本程序实现邻接矩阵与邻接表的深度、广度优先遍历算法" << endl;
	MGraph MG(Vex, Graph8_54, 6, 10);	// 建立邻接矩阵图MG
	ALGraph ALG(Vex, Graph8_54, 6, 10); // 建立邻接表图ALG
	cout << "（1）输出如图的有向图G从顶点0开始的深度优先遍历序列（递归算法）" << endl;
	cout << "邻接矩阵：";
	MG.DFSTraverse();
	cout << endl
		 << "邻接表：";
	ALG.DFSTraverse();
	cout << endl;
	cout << endl
		 << "（2）输出如图的有向图G从顶点0开始的深度优先遍历序列（非递归算法）" << endl;
	cout << "邻接矩阵：";
	MG.DFSTraverse_NoRa(0);
	cout << endl
		 << "邻接表：";
	ALG.DFSTraverse_NoRa(0);
	cout << endl;
	cout << endl
		 << "（3）输出如图的有向图G从顶点0开始的广度优先遍历序列" << endl;
	cout << "邻接矩阵：";
	MG.BFSTraverse(0);
	cout << endl
		 << "邻接表：";
	ALG.BFSTraverse(0);
	return 0;
}