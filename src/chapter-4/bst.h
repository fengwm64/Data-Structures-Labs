#pragma once
#define ElemType int

struct BiNode
{
	ElemType elem;
	BiNode *lchild, *rchild;
};

void insertBST(BiNode *&bt, ElemType key);				// 插入节点
void bracketPrint(BiNode *T);							// 括号表示法输出
bool isBiSort(BiNode *T);								// 判断是否是二叉排序树
void BiSortTree(BiNode *&bt, ElemType elem[], int len); // 建立二叉排序树
BiNode *searchBST(BiNode *bt, ElemType key);			// 搜索（递归）
BiNode *searchBST_NoR(BiNode *bt, ElemType key);		// 搜索（非递归）
void deleteNode(BiNode *&bt);							// 删除节点
bool deleteBST(BiNode *&bt, ElemType key);				// 删除值为key的节点