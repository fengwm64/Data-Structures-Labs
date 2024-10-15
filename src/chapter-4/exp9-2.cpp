#include <iostream>
using namespace std;

#define ElemType int

typedef struct
{
	ElemType *elem;
	int tableLen;
} SSTable;

void initSSTable(SSTable &s, int len)
{
	s.tableLen = len;
	s.elem = new ElemType[s.tableLen];
	for (int i = 0; i < s.tableLen; i++)
		s.elem[i] = i + 1;
}
int BinarySearch(SSTable L, ElemType key)
{
	// 初始化下标指针
	int low = 0, high = L.tableLen - 1, mid = -1;
	cout << "折半查找算法开始" << endl;
	cout << "目前low为" << low << "，high为" << high << endl;
	while (low <= high)
	{
		mid = (low + high) / 2;
		cout << "目前mid为" << mid << endl;
		if (key == L.elem[mid])
		{
			cout << "在位置" << mid << "找到" << key << "，算法结束" << endl;
			return mid;
		}
		else if (key > L.elem[mid])
		{
			cout << "在中间位置" << mid << "没有找到，且查找元素" << key << ">" << L.elem[mid];
			low = mid + 1;
			cout << "，更新low为" << low << endl;
		}
		else
		{
			cout << "在中间位置" << mid << "没有找到，且查找元素" << key << "<" << L.elem[mid];
			high = mid - 1;
			cout << "，更新high为" << high << endl;
		}
	}
	// 没找到
	return -1;
}

int main()
{
	// 初始化顺序表
	SSTable s;
	initSSTable(s, 10);
	BinarySearch(s, 9);
	return 0;
}