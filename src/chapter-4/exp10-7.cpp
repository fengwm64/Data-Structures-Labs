#include <iostream>
using namespace std;

#define LEN 9

// 打印数组
void PrintArray(int A[], int len)
{
	for (int i = 1; i < len; i++)
		cout << A[i] << " ";
	cout << endl;
}

// 讲以k为根的子树调整为大根堆
void HeadAdjust(int A[], int k, int len)
{
	// 利用数组[0]的位置暂存根节点A[k]
	A[0] = A[k];
	// 沿值更加大的子节点向下筛选
	// i->当前节点k的左孩子
	for (int i = 2 * k; i <= len; i *= 2)
	{
		// A[i] < A[i + 1]看左右孩子谁更大
		// i<len保证当前节点i有右兄弟
		if (i < len && A[i] < A[i + 1])
			i++; // i指向更大的孩子
		if (A[0] >= A[i])
			break;
		else
		{
			// 将A[i]调整到双亲节点上
			A[k] = A[i];
			// 修改k值，使其可以继续向下筛选
			k = i;
		}
	}
	// 放入最终位置
	A[k] = A[0];
}

// 建立大根堆
void BuildMaxHeap(int A[], int len)
{
	// len/2是为了找到二叉树中最底层的分支
	// 从底层往上层调整
	for (int i = len / 2; i > 0; i--)
		HeadAdjust(A, i, len);
}

// 堆排序
void HeapSort(int A[], int len)
{
	// 建立大根堆
	BuildMaxHeap(A, len);
	cout << "建立大根堆后数组：";
	PrintArray(A, len + 1);
	for (int i = len; i > 1; i--)
	{
		// 把大根放入数组尾
		swap(A[i], A[1]);
		// 整理剩下待排序元素
		// 保持大根堆样式
		HeadAdjust(A, 1, i - 1);
		cout << "第 " << len - i + 1 << " 趟排序后：";
		PrintArray(A, len + 1);
	}
}

int main()
{
	int A[LEN] = {0, 53, 17, 78, 9, 45, 65, 87, 32};
	cout << "原始数组：";
	PrintArray(A, LEN);
	HeapSort(A, LEN - 1);
	return 0;
}