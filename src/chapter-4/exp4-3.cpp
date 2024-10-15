#include <iostream>
using namespace std;

#define LEN 8

void PrintArray(int A[], int len, int pivot = -1)
{
	bool flag = 1;
	for (int i = 0; i < len; i++)
	{
		if (A[i] == pivot && flag)
		{
			cout << "[" << A[i] << "] ";
			flag = 0;
		}
		else
			cout << A[i] << " ";
	}
	cout << endl;
}

// 划分
int Partition(int A[], int low, int high)
{
	static int time = 1;
	cout << "第 " << time << " 趟排序结果：";
	time++;

	// 选取下标为low的元素作为划分枢纽
	int pivot = A[low];
	// 寻找枢纽的位置下标
	while (low < high)
	{
		// 在high部分找到一个不属于high的元素
		while (low < high && A[high] >= pivot)
			high--;
		// 然后将其替换到low部分去
		A[low] = A[high];
		// 同理，在low部分找到不属于的元素
		while (low < high && A[low] <= pivot)
			low++;
		// 替换到high部分去
		A[high] = A[low];
	}
	// 枢纽放入分界位置
	A[low] = pivot;
	// 打印结果
	PrintArray(A, LEN, pivot);
	// 返回
	return low;
}

// 快排函数（不断递归分区过程）
void QuickSort(int A[], int low, int high)
{
	// 递归终止条件
	if (low < high)
	{
		// 找到一个分界位置
		int pivot = Partition(A, low, high);
		// 递归分界左边
		QuickSort(A, low, pivot - 1);
		// 递归分界右边
		QuickSort(A, pivot + 1, high);
	}
}

int main()
{
	int A[LEN] = {49, 38, 65, 97, 76, 13, 27, 69};
	cout << "原数组为：";
	PrintArray(A, LEN);
	QuickSort(A, 0, LEN - 1);
	return 0;
}