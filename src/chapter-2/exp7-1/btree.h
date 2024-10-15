//-------------------------btree.h-----------------------
#pragma once

#include <iostream>

// 数据域元素类型
#define ElemType char
// 用广义表创建二叉树最大高度
#define MaxHeight 10

// 二叉树节点定义
typedef struct BiTNode
{
	ElemType data;					 // 数据域
	struct BiTNode *lchild, *rchild; // 左、右孩子指针
} BiTNode, *BiTree;

// 二叉树操作
void InitBiTree(BiTree &T);						// 初始化二叉树
void DestroyBiTree(BiTree &T);					// 销毁二叉树
void PrintBiTree(BiTree T);						// 打印二叉树
void Visit(BiTNode *);							// 访问（打印）节点值
int BiTreeHeight(BiTree T);						// 获取二叉树高度
bool FindTNode(BiTree T, ElemType e);			// 在树中查找
void CreateBiTree(const char str[], BiTree &T); // 创建二叉树