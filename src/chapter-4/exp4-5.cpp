#include <iostream>
using namespace std;

#define LEN 7

// 打印数组
void PrintArray(int A[], int len)
{
	for (int i = 0; i < len; i++)
		cout << A[i] << " ";
	cout << endl;
}

// 创建辅助数组B
int B[LEN] = {};

// 将以mid分界的两有序序列进行归并
void Merge(int A[], int low, int mid, int high)
{
	// for循环变量
	int i, j, k;
	// 将A中所有元素复制到B中
	for (k = low; k <= high; k++)
		B[k] = A[k];
	// 下面开始归并
	// i辅助数组B左边指针，j辅助数组B右边指针
	// k原数组指针
	for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k++)
	{
		if (B[i] <= B[j])
		{
			A[k] = B[i];
			i++;
		}
		else
		{
			A[k] = B[j];
			j++;
		}
	}
	// 左边指针没有移动到尾部
	while (i <= mid)
	{
		A[k] = B[i];
		k++;
		i++;
	}
	// 右边指针没有移动到尾部
	while (j <= high)
	{
		A[k] = B[j];
		k++;
		j++;
	}
}

// 归并排序
void MergeSort(int A[], int low, int high)
{
	// 递归终止条件
	if (low < high)
	{
		// 从中间划分
		int mid = (low + high) / 2;
		// 归并左边
		MergeSort(A, low, mid);
		// 归并右边
		MergeSort(A, mid + 1, high);
		// 将划分到最细的low、mid、high进行归并
		Merge(A, low, mid, high);
	}
}

int main()
{
	int A[] = {49, 38, 65, 97, 76, 13, 27};
	cout << "原数组：";
	PrintArray(A, LEN);
	MergeSort(A, 0, LEN - 1);
	cout << "排序后：";
	PrintArray(A, LEN);
	return 0;
}