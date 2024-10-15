#include <iostream>
#include "bst.h"
using namespace std;

#define LEN 10

int main()
{
	BiNode *root = NULL;
	int A[LEN] = {4, 9, 0, 1, 8, 6, 3, 5, 2, 7};
	cout << "（1）由关键字序列（4，9，0，1，8，6，3，5，2，7）创建一棵二叉排序" << endl;
	BiSortTree(root, A, 10);
	cout << "     以括号表示法输出：";
	bracketPrint(root);
	cout << endl
		 << endl;
	cout << "（2）判断bt是否为一棵二叉排序树:";
	cout << isBiSort(root) << endl;
	cout << endl;
	cout << "（3）采用递归和非递归两种方法查找关键字为6的结点，并输出其查找路径。" << endl;
	cout << "     递归：";
	searchBST(root, 6);
	cout << "     非递归：";
	searchBST_NoR(root, 6);
	cout << endl;
	cout << "（4）删除bt中关键字为4和5的结点" << endl;
	cout << "     删除bt中关键字4：";
	deleteBST(root, 4);
	bracketPrint(root);
	cout << endl;
	cout << "     删除bt中关键字5：";
	deleteBST(root, 5);
	bracketPrint(root);
	cout << endl;

	return 0;
}